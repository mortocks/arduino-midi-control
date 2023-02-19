#include <MIDI.h>
#include <MIDI.hpp>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {

  // Setup debugging serial and in build LED
  Serial.begin(9600);
  Serial.println("Start Midi");
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize the Midi Library.
  MIDI.begin(MIDI_CHANNEL_OMNI);  

  // Handle midi events
  MIDI.setHandleNoteOn(MyHandleNoteOn);
  MIDI.setHandleNoteOff(MyHandleNoteOff);
  MIDI.setHandleControlChange(HandleControlChange);
}

void loop() {
  MIDI.read();
}

/*
 * Handle Midi Note On event
 */
void MyHandleNoteOn(byte chanel, byte pitch, byte velocity) {
  Serial.print("Midi On: ");
  Serial.print(pitch);
  Serial.print(" ");
  Serial.println(velocity);

  digitalWrite(LED_BUILTIN, LOW);
}

/*
 * Handle Midi Note Off event
 */
void MyHandleNoteOff(byte chanel, byte pitch, byte velocity) {
  Serial.print("Midi off: ");
  Serial.print(pitch);
  Serial.print(" ");
  Serial.println(velocity);

  digitalWrite(LED_BUILTIN, HIGH);
}

/*
 * Handle Midi Control Change
 */
void HandleControlChange(byte chanel, byte number, byte value) {
  Serial.print("Control Change: ");
  Serial.println(number);

  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
}

/*
 * Handle Midi Program Change
 */
void HandleProgramChange(byte chanel, byte number, byte value) {
  Serial.print("Program Change: ");
  Serial.println(number);

  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
}


