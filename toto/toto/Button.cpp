/*
  Button.cpp - Library for handling button input.

  shortPress() returns true when a button released after a time longer
  than shortTime and shorter than longTime.

  longPress() returns true when the button is pressed longer than longTime
*/

#include "Button.h"

Button::Button(int pin, int shortTime, int longTime, int debounceTime) {
  pinMode(pin, INPUT);
  _pin = pin;
  _shortTime = shortTime;
  _longTime = longTime;
  _debouceTime = debounceTime;
  _shortPress = false;
  _longPress = false;
  _longPressLatch = false;
  _lastChange = 0;
  _changeToHigh = 0;
  _lastState = LOW;
}

void Button::tick() {
  int state = digitalRead(_pin);
  unsigned long currentTime = millis();
  if (_lastState != state) {
    _lastChange = currentTime;

    // do nothing if debouncing
    if ((currentTime - _lastChange) < _debouceTime) {
      return;
    }

    if (state == HIGH) {
      _changeToHigh = currentTime;
    } else {
      bool pastShort = (currentTime - _changeToHigh) >= _shortTime;
      bool beforeLong = (currentTime - _changeToHigh) < _longTime;
      if (pastShort && beforeLong) {
        _shortPress = true;
      }
      _longPressLatch = false;
    }

    _lastState = state;
    return;
  }

  // are we holding down the button?
  if (state == HIGH) {
    if ((millis() - _changeToHigh) >= _longTime && !_longPressLatch) {
      _longPressLatch = true;
      _longPress = true;
    }
  }
}

bool Button::shortPress() {
  if (_shortPress) {
    _shortPress = false;
    return true;
  }
  return _shortPress;
}

bool Button::longPress() {
  if (_longPress) {
    _longPress = false;
    return true;
  }
  return _longPress;
}

