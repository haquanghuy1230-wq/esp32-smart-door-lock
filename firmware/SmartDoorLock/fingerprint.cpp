#include "fingerprint.h"

void setupFingerprint() {
  mySerial.begin(57600, SERIAL_8N1, 21, 22);
  finger.begin(57600);
}

void loopFingerprint() {
  if (enteringPassword) return;

  uint8_t p = finger.getImage();

  if (p == FINGERPRINT_NOFINGER) {
    lcd.noBacklight();
    return;
  }

  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Processing...");

  if (p != FINGERPRINT_OK) return;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) {
    beepError();
    lcd.setCursor(0,1); lcd.print("Img Error");
    softDelay(500); lcd.clear();
    return;
  }

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) {
    beepError();
    lcd.setCursor(0,1); 
    lcd.print("Unknown Finger");
    softDelay(1000); lcd.clear();
    return;
  }

  lcd.setCursor(0,1);
  lcd.print("ID: ");
  lcd.print(finger.fingerID);
  lcd.print(" OK");
  
  firebaseUpdateDoorIfChanged();
  firebaseUpdateState();
  openDoor();

  lcd.clear();
}

void addFingerprint() {
  int id = getIDFromKeypad();
  if (id < 0) return; // Người dùng bấm *

  lcd.clear();
  lcd.print("Place Finger");

  while (finger.getImage() != FINGERPRINT_OK) {
    keypad.getKeys();     // cho keypad sống
    softDelay(10);            // nhường CPU
  }


  finger.image2Tz(1);
  lcd.clear(); lcd.print("Remove...");
  softDelay(1500);

  lcd.clear(); lcd.print("Again...");
  while (finger.getImage() != FINGERPRINT_OK);
  finger.image2Tz(2);

  if (finger.createModel() == FINGERPRINT_OK) {
    if (finger.storeModel(id) == FINGERPRINT_OK) {
      lcd.clear();
      lcd.print("Added ID ");
      lcd.print(id);
      beepOK();
      softDelay(1500);
      return;
    }
  }

  lcd.clear();
  lcd.print("Add Fail");
  beepError();
  softDelay(1500);
}


void deleteFingerprint() {
  int id = getIDFromKeypad();
  if (id < 0) return;

  if (finger.deleteModel(id) == FINGERPRINT_OK) {
    lcd.clear();
    lcd.print("Deleted ID ");
    lcd.print(id);
    beepOK();
    softDelay(1500);
  } else {
    lcd.clear();
    lcd.print("Delete Fail");
    beepError();
    softDelay(1500);
  }
}



int getIDFromKeypad() {
  lcd.clear();
  lcd.print("Enter ID:");
  lcd.setCursor(0,1);
  String idStr = "";

  while (true) {
    keypad.getKeys();

    for (int i = 0; i < LIST_MAX; i++) {
      if (keypad.key[i].stateChanged && keypad.key[i].kstate == PRESSED) {
        char key = keypad.key[i].kchar;

        // Thoát khi nhấn *
        if (key == '*') {
          lcd.clear();
          lcd.print("Cancel");
          softDelay(800);
          return -1;
        }

        // Nhập số
        if (key >= '0' && key <= '9') {
          if (idStr.length() < 3) {     // ID tối đa 127
            idStr += key;
            lcd.print(key);
          }
        }

        // Xác nhận khi nhấn #
        if (key == '#') {
          if (idStr.length() == 0) return -1;
          int id = idStr.toInt();
          if (id < 1 || id > 127) {     // Giới hạn ID
            lcd.clear();
            lcd.print("ID 1-127 only");
            softDelay(1000);
            lcd.clear();
            lcd.print("Enter ID:");
            lcd.setCursor(0,1);
            idStr = "";
          } else {
            return id;
          }
        }
        softDelay(180);
      }
    }
  }
}
int getFingerprintCount() {
  finger.getTemplateCount();
  return finger.templateCount;
}
