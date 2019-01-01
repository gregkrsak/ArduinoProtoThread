// ArduinoProtoThread
// ArduinoProtoThread.cpp
//
// The primary class of the ArduinoProtoThread project.
//
// Written by Greg M. Krsak <greg.krsak@gmail.com>, 2018
// https://github.com/gregkrsak/ArduinoProtoThread
//


#include "ArduinoProtoThread.hpp"

// Defines hardware pins
#include "pins.h"

// Arduino library
#include <Arduino.h>


//
// Member Function: setEecutionIntervalTo
// Purpose: Sets the proto thread execution interval.
// Parameters:
//  newInterval: Try to run this proto thread every X number of milliseconds.
// Returns: void
//
void ArduinoProtoThread::setExecutionIntervalTo(unsigned long newIntervalInMs)
{
  this->interval = newIntervalInMs;
}


//
// Member Function: executionInterval
// Purpose: Returns the proto thread execution interval.
// Returns: unsigned long
//
unsigned long ArduinoProtoThread::executionInterval()
{
  unsigned long result = this->interval;
  return result;
}


//
// Member Function: changeStateTo
// Purpose: Changes the state of the proto thread's state machine.
// Returns: void
//
void ArduinoProtoThread::changeStateTo(APTStates newState)
{
  this->state = newState;
  return;
}


//
// Member Function: currentState
// Purpose: Returns the state of the proto thread's state machine.
// Returns: enum
//
APTStates ArduinoProtoThread::currentState()
{
  APTStates result = this->state;
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
  APTStates state;

  currentTime = millis();
  timeDifference = currentTime - this->previousExecutionTime;
  state = this->currentState();

  switch (state)
  {
    case WillRun:
      break;
    case Running:
      // BEGIN MAIN PROGRAM LOOP //////////
      // Does the proto thread need to be executed?
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
