// ArduinoProtoThread
// APTStateMachine.hpp
//
// Abstract class that defines a state machine for ArduinoProtoThread.
//
// Written by Greg M. Krsak <greg.krsak@gmail.com>, 2018
// https://github.com/gregkrsak/ArduinoProtoThread
//


#pragma once

// Used for pure virtual functions. I think this looks cleaner and is more self-documenting.
#define PURE_VIRTUAL 0


// Used for state machines
enum APTStates { WillRun, Running, JustRan, WillStop, Stopped };


//
// Abstract class: APTStateMachine
// Purpose: Defines the API for a state machine.
//
class APTStateMachine
{
  public:
    inline virtual ~APTStateMachine() = PURE_VIRTUAL;
    virtual void changeStateTo(APTStates newState) = PURE_VIRTUAL;
    virtual APTStates currentState();

  protected:
    APTStates state;
};
APTStateMachine::~APTStateMachine() { }

// End of APTStateMachine.hpp
