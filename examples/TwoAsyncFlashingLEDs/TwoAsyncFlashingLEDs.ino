// ArduinoProtoThread
// examples/TwoAsyncFlashingLEDs/TwoAsyncFlashingLEDs.ino
//
// Flashes two LEDs at different blink rates.
//
// https://github.com/gregkrsak/ArduinoProtoThread
//
// Copyright 2018, 2019 Greg M. Krsak <greg.krsak@gmail.com>
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


// Sample delegate object
class LedFlasher : public ArduinoProtoThreadDelegate
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


// Main protothread instances
ArduinoProtoThread *protoThreadA;
ArduinoProtoThread *protoThreadB;
// Protothread delegates for LED flashers
LedFlasher *flasherA;
LedFlasher *flasherB;


//////////////////////////////////////////////////////////////////////////////////////////////////
// RUN ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  // Initialize delegates
  flasherA = new LedFlasher(OUTPUT_PIN_LED_A);
  flasherB = new LedFlasher(OUTPUT_PIN_LED_B);
  // Initialize protothreads
  protoThreadA = new ArduinoProtoThread();
  protoThreadB = new ArduinoProtoThread();
  protoThreadA->delegateCallbacksTo(flasherA);
  protoThreadB->delegateCallbacksTo(flasherB);
  protoThreadA->setExecutionIntervalTo(1000);
  protoThreadB->setExecutionIntervalTo(100);
  protoThreadA->changeStateTo(Start);
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

// End of TwoAsyncFlashingLEDs.ino
