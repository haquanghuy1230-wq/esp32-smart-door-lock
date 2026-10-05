#include "config.local.h"
#include <WiFi.h>
#include <WebServer.h>
#include <FirebaseESP32.h>

#include "hardware.h"
#include "fingerprint.h"
#include "password.h"
#include "index.h"

// =================================================
// ================= WIFI ==========================
// =================================================
const char* ssid         = WIFI_SSID;
const char* passwordWiFi = WIFI_PASSWORD;
const String adminWebPass = WEB_ADMIN_PASSWORD;

// =================================================
// ================= WEBSERVER =====================
// =================================================
WebServer server(80);

// =================================================
// ================= FIREBASE ======================
// =================================================
#define FIREBASE_HOST FIREBASE_DATABASE_URL
#define FIREBASE_AUTH FIREBASE_LEGACY_TOKEN

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// =================================================
// ================= USER ==========================
// =================================================
String adminMail = WEB_ADMIN_EMAIL;
String clientMail[] = {
  "client1@example.com",
  "client2@example.com",
  "client3@example.com"
};
const int totalClient = 3;

// =================================================
// ================= FLAGS =========================
// =================================================
bool addFpMode      = false;
bool changePassMode = false;
bool relayManual    = false;

// =================================================
// ================= SYSTEM STATE ==================
// =================================================
bool doorState  = false;
bool lightState = false;

// ======== THÊM: lưu trạng thái cũ của cửa ========
bool lastDoorState = false;

// =================================================
// ================= FINGERPRINT STATE =============
// =================================================
int fingerprintCount  = 0;
int lastFingerprintID = -1;

// =================================================
// ================= TIMER =========================
// =================================================
unsigned long lastFirebaseUpdate = 0;
const unsigned long FIREBASE_INTERVAL = 1000;

// =================================================
// ================= FIREBASE HELPERS ===============
// =================================================
void firebaseUpdateFingerprint() {
  Firebase.setInt(fbdo, "/fingerprint/count", fingerprintCount);
  Firebase.setInt(fbdo, "/fingerprint/last_id", lastFingerprintID);
}

void firebaseUpdateState() {
  Firebase.setString(fbdo, "/door/state",  doorState  ? "OPEN" : "CLOSED");
  Firebase.setString(fbdo, "/light/state", lightState ? "ON"   : "OFF");
}

// ======== THÊM: cập nhật cửa khi thay đổi ========
void firebaseUpdateDoorIfChanged() {
  if (doorState != lastDoorState) {
    Firebase.setString(fbdo,
                       "/door/state",
                       doorState ? "OPEN" : "CLOSED");
    lastDoorState = doorState;
  }
}

// =================================================
// ================= WEB HANDLERS ==================
// =================================================
void handleRoot() {
  server.send(200, "text/html", index_html);
}

// ---------- LOGIN ----------
void handleLogin() {
  if (!server.hasArg("email") || !server.hasArg("pass")) {
    server.send(400, "text/plain", "missing");
    return;
  }

  String email = server.arg("email");
  String pass  = server.arg("pass");

  if (email == adminMail) {
    server.send(pass == adminWebPass ? 200 : 401,
                "text/plain",
                pass == adminWebPass ? "admin" : "wrongpass");
    return;
  }

  for (int i = 0; i < totalClient; i++) {
    if (email == clientMail[i]) {
      server.send(200, "text/plain", "client");
      return;
    }
  }

  server.send(401, "text/plain", "invalid");
}

// ---------- DOOR ----------
void handleOpen() {
  Firebase.setString(fbdo, "/door/state", "OPEN");
  openDoor();
  doorState = true;
  server.send(200, "text/plain", "OPEN");
  doorState = false;
  server.send(200, "text/plain", "CLOSED");
  Firebase.setString(fbdo, "/door/state", "CLOSED");
}

void handleClose() {
  Firebase.setString(fbdo, "/door/state", "CLOSED");
  doorState = false;
  server.send(200, "text/plain", "CLOSED");
}

void handleDoorState() {
  server.send(200, "text/plain", doorState ? "OPEN" : "CLOSED");
}

// ---------- LIGHT ----------
void handleLight() {
  if (!server.hasArg("state")) {
    server.send(400, "text/plain", "missing");
    return;
  }

  if (server.arg("state") == "on") {
    relayManual = true;
    digitalWrite(RELAY, HIGH);
    lightState = true;
  } else {
    relayManual = false;
    digitalWrite(RELAY, LOW);
    lightState = false;
  }

  server.send(200, "text/plain", "OK");
}

void handleLEDState() {
  server.send(200, "text/plain", lightState ? "ON" : "OFF");
}

// =================================================
// ================= SETUP =========================
// =================================================
void setup() {
  Serial.begin(115200);

  setupHardware();
  setupFingerprint();
  setupPassword();

  fingerprintCount = getFingerprintCount();
  Firebase.setInt(fbdo, "/fingerprint/count", fingerprintCount);
  Firebase.setInt(fbdo, "/fingerprint/last_id", -1);

  // ----- WIFI -----
  WiFi.begin(ssid, passwordWiFi);
  lcd.clear();
  lcd.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    lcd.print(".");
  }

  lcd.clear();
  lcd.print("WiFi OK");
  delay(500);

  lcd.clear();
  lcd.print(WiFi.localIP());
  Serial.println(WiFi.localIP());

  // ----- FIREBASE -----
  config.database_url = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // ----- INIT FINGERPRINT STATE -----
  fingerprintCount  = getFingerprintCount();
  lastFingerprintID = -1;
  firebaseUpdateFingerprint();

  // ----- WEB ROUTES -----
  server.on("/", handleRoot);
  server.on("/login", handleLogin);

  server.on("/open", handleOpen);
  server.on("/close", handleClose);
  server.on("/doorstate", handleDoorState);

  server.on("/light", handleLight);
  server.on("/ledstate", handleLEDState);

  server.on("/addfp", []() {
    addFpMode = true;
    server.send(200, "text/plain", "OK");
  });

  server.on("/deletefp", []() {
    deleteFingerprint();
    delay(300);

    fingerprintCount = getFingerprintCount();
    Firebase.setInt(fbdo, "/fingerprint/count", fingerprintCount);

    server.send(200, "text/plain", "OK");
  });

  server.on("/changepass", []() {
    changePassMode = true;
    server.send(200, "text/plain", "OK");
  });

  server.begin();

  lcd.clear();
  lcd.print("System Ready");
}

// =================================================
// ================= LOOP ==========================
// =================================================
void loop() {
  server.handleClient();

  loopPassword();
  loopFingerprint();

  // ----- AUTO LIGHT -----
  if (!relayManual) {
    handleRadar();
    lightState = digitalRead(RELAY);
  }

  // ======== THÊM: cập nhật cửa ngay khi thay đổi ========
  firebaseUpdateDoorIfChanged();

  // ----- ADD FINGERPRINT -----
  if (addFpMode) {
    lcd.clear();
    lcd.print("Add Finger...");

    addFingerprint();
    delay(300);

    fingerprintCount = getFingerprintCount();
    Firebase.setInt(fbdo, "/fingerprint/count", fingerprintCount);

    addFpMode = false;
  }

  // ----- CHANGE PASSWORD -----
  if (changePassMode) {
    lcd.clear();
    lcd.print("New Password:");
    inputPass = "";
    enteringPassword = true;
    changePassMode = false;
  }

  // ----- FIREBASE STATE SYNC -----
  if (millis() - lastFirebaseUpdate >= FIREBASE_INTERVAL) {
    lastFirebaseUpdate = millis();
    firebaseUpdateState();
  }
}
