/*
  Button.h - Library for handling button input.
*/
#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button
{
  public:
    Button(int pin, int shortTime, int longTime, int debounceTime);
    Button(int pin) {
      Button(pin, 50, 1000, 50);
    }
    void
      tick();
    bool
      shortPress(),
      longPress();
  private:
    bool
      _lastState,
      _shortPress,
      _longPress,
      _longPressLatch;
    int
      _pin,
      _shortTime,
      _longTime,
      _debouceTime;
    unsigned long
      _lastChange,
      _changeToHigh;
};

#endif //BUTTON_H
