#ifndef FINGERPRINT_H
#define FINGERPRINT_H

#include "hardware.h"
int getFingerprintCount();
void firebaseUpdateState();
void setupFingerprint();
void loopFingerprint();
int getIDFromKeypad();
void addFingerprint();
void deleteFingerprint();
void firebaseUpdateDoorIfChanged();
#endif
