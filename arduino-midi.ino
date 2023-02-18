#include <MIDI.h>
#include <MIDI.hpp>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>


#define LED 13  // Arduino Board LED is on Pin 13

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("Start Midi");

  MIDI.begin(MIDI_CHANNEL_OMNI);  // Initialize the Midi Library.

  MIDI.setHandleNoteOn(MyHandleNoteOn);  // This is important!! This command
  MIDI.setHandleNoteOff(MyHandleNoteOff);  // This command tells the Midi Library
  MIDI.setHandleProgramChange(HandleProgramChange);
  MIDI.setHandleControlChange(HandleControlChange);
}

void loop() {
  MIDI.read();
}

/*
 * Handle Midi Note On event
 */
void MyHandleNoteOn(byte chanel, byte pitch, byte velocity) {
  Serial.println(" Midi on");
  digitalWrite(LED_BUILTIN, LOW);
}

/*
 * Handle Midi Note Off event
 */
void MyHandleNoteOff(byte chanel, byte pitch, byte velocity) {
  digitalWrite(LED_BUILTIN, HIGH);
}

/*
 * Handle Midi Control Change
 */
void HandleControlChange(byte chanel, byte number, byte value) {
  Serial.println(number);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
}

/*
 * Handle Midi Program Change
 */
void HandleProgramChange(byte chanel, byte number, byte value) {
  Serial.println(number);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
}


