// arduino_led_flash
// ArduinoLedFlash.hpp
//
// The header for the primary class of the arduino_led_flash project.
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


#pragma once

// Available at: https://gist.github.com/gregkrsak/5dd52a396138639ea9f4cf4b3bedf039
#include "MainProgram.hpp"


//
// Class: ArduinoLedFlash
// Derived from: MainProgram
// Purpose: The main class of the sketch.
//
class ArduinoLedFlash : public MainProgram
{
public:
	ArduinoLedFlash() { }
	~ArduinoLedFlash() { }
  
  void setFlashIntervalTo(unsigned long newInterval);
  unsigned long flashInterval();
   
  // From MainProgram
  void enableDebugMode();
  void changeStateTo(ProgramStateMachine newState);
  ProgramStateMachine currentState();
  void timeSlice();
  
protected:
  unsigned long interval;

private:
  unsigned long previousFlashTime;
};


// Used elsewhere to hold an instance of the main program class
extern ArduinoLedFlash *program;

// End of ArduinoLedFlash.hpp
