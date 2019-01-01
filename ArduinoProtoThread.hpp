// ArduinoProtoThread
// ArduinoProtoThread.hpp
//
// The header for the primary class of the ArduinoProtoThread project.
//
// Written by Greg M. Krsak <greg.krsak@gmail.com>, 2018
// https://github.com/gregkrsak/ArduinoProtoThread
//


#pragma once

#include "APTStateMachine.hpp"


//
// Class: ArduinoProtoThread
// Derived from: MainProgram
// Purpose: The main class of the sketch.
//
class ArduinoProtoThread : public APTStateMachine
{
  public:
    ArduinoProtoThread() { }
    ~ArduinoProtoThread() { }

    void setExecutionIntervalTo(unsigned long newIntervalInMs);
    unsigned long executionInterval();

    // From APTStateMachine
    void changeStateTo(APTStates newState);
    APTStates currentState();
    void timeSlice();

  protected:
    unsigned long interval;

  private:
    unsigned long previousExecutionTime;
};


// End of ArduinoProtoThread.hpp
