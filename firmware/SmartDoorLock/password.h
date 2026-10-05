#ifndef PASSWORD_H
#define PASSWORD_H

#include "hardware.h"
extern String doorPassword;
void drawIdleScreen();
void setupPassword();
void loopPassword();
bool handlePasswordMode();
String loadPassword();
void savePassword(String pass);
void firebaseUpdateState();
#endif
