// ArduinoProtoThread
// examples/OneComplexAsyncFlashingLED/OneComplexAsyncFlashingLED.ino
//
// Flashes one LED at two different blink rates.
//
// https://github.com/gregkrsak/ArduinoProtoThread
//
// Copyright 2018, 2019, 2022 Greg M. Krsak <greg.krsak@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//


// ArduinoProtoThread class
#include "ArduinoProtoThread.hpp"
// Required for the state machine enums
#include "ArduinoProtoThreadStateMachine.hpp"
// Hardware pins
#include "pins.h"


// Flashes the LED
class LedFlasher : public ArduinoProtoThreadEventHandler
{
  public:
    LedFlasher(int pin)
    {
      this->outputPin = pin;
    }
    ~LedFlasher() { }

    void onStart()
    {
      pinMode(this->outputPin, OUTPUT);
    }
    void onRunning()
    {
      // Flip-flop the LED state
      this->ledState ^= HIGH;
      // Send the state to hardware
      digitalWrite(this->outputPin, this->ledState);
    }
    void onKill()
    {
      return;
    }

  protected:
    bool ledState = LOW;
    int outputPin;
};


// Changes the flash period of the LED
class LedFlashPeriodShifter : public ArduinoProtoThreadEventHandler
{
  public:
    LedFlashPeriodShifter(ArduinoProtoThread *flasherThread, int interval1, int interval2)
    {
      this->targetFlasherThread = flasherThread;
      this->firstInterval = interval1;
      this->secondInterval = interval2;
    }
    ~LedFlashPeriodShifter() { }

    void onStart()
    {
      return;
    }
    void onRunning()
    {
      if (this->flipFlopState == LOW)
      {
        this->targetFlasherThread->setExecutionIntervalTo(this->firstInterval);
      }
      else
      {
        this->targetFlasherThread->setExecutionIntervalTo(this->secondInterval);
      }
      // Flip-flop the shifter state
      this->flipFlopState ^= HIGH;
    }
    void onKill()
    {
      return;
    }

  protected:
    bool flipFlopState = LOW;
    int firstInterval = 0;
    int secondInterval = 0;
    ArduinoProtoThread *targetFlasherThread;
};


// Main protothread instances
ArduinoProtoThread *protoThreadA;
ArduinoProtoThread *protoThreadB;
// Protothread delegate for LED flasher
LedFlasher *flasherA;
// Protothread delegate for LED period changer
LedFlashPeriodShifter *shifterA;


//////////////////////////////////////////////////////////////////////////////////////////////////
// RUN ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  int interval1 = 500;
  int interval2 = 125;
  
  // Initialize flasher
  flasherA = new LedFlasher(OUTPUT_PIN_LED_A);
  protoThreadA = new ArduinoProtoThread();
  protoThreadA->setEventHandlerTo(flasherA);
  protoThreadA->setExecutionIntervalTo(interval1);  
  protoThreadA->changeStateTo(Start);

  // Initialize shifter
  shifterA = new LedFlashPeriodShifter(protoThreadA, interval1, interval2);
  protoThreadB = new ArduinoProtoThread();
  protoThreadB->setEventHandlerTo(shifterA);
  protoThreadB->setExecutionIntervalTo(5000);
  protoThreadB->changeStateTo(Start);
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// INFINITE LOOP
//////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  protoThreadA->timeSlice();
  protoThreadB->timeSlice();
}

// End of OneComplexAsyncFlashingLED.ino
