#include "config.local.h"
#include "hardware.h"

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Fingerprint
HardwareSerial mySerial(2);
Adafruit_Fingerprint finger(&mySerial);

// Servo
Servo myservo;

// Password
bool enteringPassword = false;
String inputPass = "";
String password = DOOR_DEFAULT_PASSWORD;

bool doorOpen = false; 
void openDoorSystem() {
  doorOpen = true;
  // điều khiển servo / relay cửa
}
void closeDoorSystem() {
  doorOpen = false;
}
// Pins
const int BUZZER = 2;
const int RELAY  = 4;
const int SERVO_PIN = 23;
const int RADAR_OUT = 5;

// Keypad
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {32, 33, 25, 26};
byte colPins[COLS] = {27, 14, 12, 13};

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void beepOK() {
  digitalWrite(BUZZER, HIGH); delay(100);
  digitalWrite(BUZZER, LOW);
}

void beepError() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(BUZZER, HIGH); delay(80);
    digitalWrite(BUZZER, LOW); delay(80);
  }
}

void printStars(int n) {
  for (int i = 0; i < n; i++) lcd.print("*");
}

void openDoor() {
  beepOK();
  myservo.write(90);
  delay(3000);
  myservo.write(0);
  delay(1200);
}


void handleRadar() {
  int state = digitalRead(RADAR_OUT);

  if (state == HIGH) {
    // Phát hiện người
    digitalWrite(RELAY, HIGH);   // bật relay
     // 16 ký tự -> đủ để ghi
  } else {
    // Không có người
    digitalWrite(RELAY, LOW);    // tắt relay
    
  }
}

void setupHardware() {
  Serial.begin(115200);
  EEPROM.begin(64);

  pinMode(BUZZER, OUTPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);

  pinMode(RADAR_OUT, INPUT);
  digitalWrite(RADAR_OUT, LOW);

  myservo.attach(SERVO_PIN);
  myservo.write(0);

  Wire.begin(18,19);
  lcd.init(); 
  lcd.backlight();
}
void softDelay(unsigned long ms) {
  unsigned long start = millis();
  while (millis() - start < ms) {
    keypad.getKeys();   // giữ keypad responsive
    delay(1);           // nhường CPU
  }
}
