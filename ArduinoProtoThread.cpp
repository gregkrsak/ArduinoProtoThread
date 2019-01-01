// ArduinoProtoThread
// ArduinoProtoThread.cpp
//
// Implements a protothread API, allowing Arduino compatibles to multitask.
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


#include "ArduinoProtoThread.hpp"

// Defines hardware pins
#include "pins.h"

// Arduino library
#include <Arduino.h>


//
// Member Function: setEecutionIntervalTo
// Purpose: Sets the protothread execution interval.
// Parameters:
//  newInterval: Try to run this protothread every X number of milliseconds.
// Returns: void
//
void ArduinoProtoThread::setExecutionIntervalTo(unsigned long newIntervalInMs)
{
  this->interval = newIntervalInMs;
}


//
// Member Function: executionInterval
// Purpose: Returns the protothread execution interval.
// Returns: unsigned long
//
unsigned long ArduinoProtoThread::executionInterval()
{
  unsigned long result = this->interval;
  return result;
}


//
// Member Function: changeStateTo
// Purpose: Changes the state of the protothread's state machine.
// Returns: void
//
void ArduinoProtoThread::changeStateTo(ArduinoProtoThreadState newState)
{
  this->state = newState;
  return;
}


//
// Member Function: currentState
// Purpose: Returns the state of the protothread's state machine.
// Returns: enum
//
ArduinoProtoThreadState ArduinoProtoThread::currentState()
{
  ArduinoProtoThreadState result = this->state;
  return result;
}


//
// Member Function: timeSlice
// Purpose: Executes the thread for one slice of time.
// Returns: void
//
void ArduinoProtoThread::timeSlice()
{
  static bool ledState = LOW;
  unsigned long currentTime;
  unsigned long timeDifference;
  ArduinoProtoThreadState state;

  currentTime = millis();
  timeDifference = currentTime - this->previousExecutionTime;
  state = this->currentState();

  switch (state)
  {
    case WillRun:
      break;
    case Running:
      // BEGIN MAIN PROGRAM LOOP //////////
      // Does the protothread need to be executed?
      if (timeDifference > this->executionInterval())
      {
        // Reset the variable that holds the last time it executed
        this->previousExecutionTime = currentTime;
        // Flip-flop the LED state
        if (ledState == HIGH)
        {
          ledState = LOW;
        }
        else
        {
          ledState = HIGH;
        }
        // Send the state to hardware
        digitalWrite(OUTPUT_PIN_LED, ledState);
      }
      // END MAIN PROGRAM LOOP ////////////
      break;
    case JustRan:
      break;
    case WillStop:
      break;
    case Stopped:
      break;
  }
}

// End of ArduinoProtoThread.cpp
