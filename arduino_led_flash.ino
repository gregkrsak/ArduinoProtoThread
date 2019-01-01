// ArduinoProtoThreadExample
// ArduinoProtoThreadExample.ino
//
// The main sketch file of the ArduinoProtoThreadExample project.
//
// Written by Greg M. Krsak <greg.krsak@gmail.com>, 2018
// https://github.com/gregkrsak/ArduinoProtoThread
//


#include "ArduinoProtoThread.hpp"

#include "APTStateMachine.hpp"

#include "pins.h"


// Main protoThread instance
ArduinoProtoThread *protoThread;


//////////////////////////////////////////////////////////////////////////////////////////////////
// RUN ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
    // Initialize hardware
  pinMode(OUTPUT_PIN_LED, OUTPUT);
  digitalWrite(OUTPUT_PIN_LED, LOW);
  
  // Initialize proto threads
  protoThread = new ArduinoProtoThread();
  protoThread->setExecutionIntervalTo(500);
  protoThread->changeStateTo(Running);
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// INFINITE LOOP
//////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  protoThread->timeSlice();
}

// End of ArduinoProtoThreadExample.ino
