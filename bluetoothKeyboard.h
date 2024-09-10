#define USE_NIMBLE
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

#define MN_UP 15
#define MN_DOWN 12
#define MN_LEFT 19
#define MN_RIGHT 21
#define MN_CENTER 22
#define MN_ZOOMIN 14
#define MN_ZOOMOUT 13
#define MN_ROTATE 23


bool keyStates[8] = {false, false, false, false, false, false, false, false};
int keyPins[8] = {MN_UP, MN_DOWN, MN_LEFT, MN_RIGHT, MN_CENTER, MN_ZOOMIN, MN_ZOOMOUT, MN_ROTATE};
uint8_t keyCodes[8] = {KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, KEY_RIGHT_ARROW, 'c', '+', '-', 'r'};

void setup() {
  Serial.begin(115200);
  Serial.println("Code running...");
  setInputs();
  bleKeyboard.begin();
}

bool connectNotificationSent = false;

void loop() {
  int counter;
  if (bleKeyboard.isConnected()) {
    if (!connectNotificationSent) {
      Serial.println("Code connected...");
      connectNotificationSent = true;
    }
    for (counter = 0; counter < 8; counter ++) {
      handleButton(counter);
    }
  }
}

void setInputs() {
  pinMode(MN_UP, INPUT_PULLUP);
  pinMode(MN_DOWN, INPUT_PULLUP);
  pinMode(MN_LEFT, INPUT_PULLUP);
  pinMode(MN_RIGHT, INPUT_PULLUP);
  pinMode(MN_CENTER, INPUT_PULLUP);
  pinMode(MN_ZOOMIN, INPUT_PULLUP);
  pinMode(MN_ZOOMOUT, INPUT_PULLUP);
  pinMode(MN_ROTATE, INPUT_PULLUP);
}
void handleButton(int keyIndex) {
  // handle the button press
  if (!digitalRead(keyPins[keyIndex])) {
    // button pressed
    if (!keyStates[keyIndex]) {
      // key not currently pressed
      keyStates[keyIndex] = true;
      bleKeyboard.press(keyCodes[keyIndex]);
    }
  }
  else {
    // button not pressed
    if (keyStates[keyIndex]) {
      // key currently pressed
      keyStates[keyIndex] = false;
      bleKeyboard.release(keyCodes[keyIndex]);
    }
  }
}