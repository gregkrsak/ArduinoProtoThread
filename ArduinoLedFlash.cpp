// arduino_led_flash
// ArduinoLedFlash.cpp
//
// The primary class of the arduino_led_flash project.
//
// Written by Greg M. Krsak <greg.krsak@gmail.com>, 2018
// https://github.com/gregkrsak/arduino_led_flash
//
// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
//
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// For more information, please refer to <http://unlicense.org/>
//


#include "ArduinoLedFlash.hpp"

// Defines hardware pins
#include "pins.h"

// Arduino library
#include <Arduino.h>


//
// Member Function: setFlashIntervalTo
// Purpose: Sets the LED flash interval.
// Parameters:
//  newInterval: The number of milliseconds the LED will spend on or off, in a 50% duty cycle.
// Returns: void
//
void ArduinoLedFlash::setFlashIntervalTo(unsigned long newInterval)
{
  this->interval = newInterval;
}


//
// Member Function: flashInterval
// Purpose: Returns the LED flash interval.
// Returns: unsigned long
//
unsigned long ArduinoLedFlash::flashInterval()
{
  unsigned long result = this->interval;
  return result;
}


//
// Member Function: enableDebugMode
// Purpose: Enables or disables debug mode for the program.
// Returns: void
//
void ArduinoLedFlash::enableDebugMode()
{
  this->debugMode = true;
  return;
}


//
// Member Function: changeStateTo
// Purpose: Changes the state of the program's state machine.
// Returns: void
//
void ArduinoLedFlash::changeStateTo(ProgramStateMachine newState)
{
  this->state = newState;
  return;
}


//
// Member Function: currentState
// Purpose: Returns the state of the program's state machine.
// Returns: enum
//
ProgramStateMachine ArduinoLedFlash::currentState()
{
  ProgramStateMachine result = this->state;
  return result;
}


//
// Member Function: timeSlice
// Purpose: Executes the program for one slice of time.
// Returns: void
//
void ArduinoLedFlash::timeSlice()
{
  static bool ledState = LOW;
  unsigned long currentTime;
  unsigned long timeDifference;
  ProgramStateMachine state;

  currentTime = millis();
  timeDifference = currentTime - this->previousFlashTime;
  state = this->currentState();

  switch (state)
  {
    case Starting:
      // Set the LED pin to output mode and turn the LED off
      pinMode(OUTPUT_PIN_LED, OUTPUT);
      digitalWrite(OUTPUT_PIN_LED, LOW);
      // Set the flash interval
      this->setFlashIntervalTo(1000);
      // Update program state
      program->changeStateTo(Running);
      break;
    case Running:
      // BEGIN MAIN PROGRAM LOOP //////////
      // Has an LED state change triggered?
      if (timeDifference > this->flashInterval())
      {
        // Reset the variable that holds the last time it triggered
        this->previousFlashTime = currentTime;
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
    case Stopping:
      // Update program state
      program->changeStateTo(Stopped);
      break;
    case Stopped:
      break;
  }
}

// End of ArduinoLedFlash.cpp
