#include <FastLED.h>
#include <EEPROM.h>
#include <MIDI.h>

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();
int currentCC = 25;
int currentCCAddress = 0;
bool doBreak = false;

// LED Setup
#define NUM_LEDS 12
#define DATA_PIN 6
CRGB leds[NUM_LEDS];
#define FASTLED_ALLOW_INTERRUPTS 0;

unsigned long now = 0;

void setup() {

  // Setup debugging serial and in build LED
  Serial.begin(9600);
  Serial.println("Start Midi");
  pinMode(LED_BUILTIN, OUTPUT);

  // Restore variables
  currentCC = EEPROM.read(currentCCAddress);

  // Initialize the Midi Library.
  MIDI.begin(MIDI_CHANNEL_OMNI);  

  // Handle midi events
  MIDI.setHandleNoteOn(MyHandleNoteOn);
  MIDI.setHandleNoteOff(MyHandleNoteOff);
  MIDI.setHandleControlChange(HandleControlChange);

  // Setup Leds
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

}

CRGB getColor () {
  CRGB color = CRGB::Blue;
  switch (currentCC) {
    case 25:
      color = CRGB::LightSeaGreen;
      break;
    case 22:
      color = CRGB::DarkOrange;
      break;
    case 24:
      color = CRGB::Blue;
      break;
    case 26:
      color = CRGB::Purple;
      break;
    default:
      color = CRGB::Pink;
      break;
  }
  return color;
}

void loop() {
  MIDI.read();

  uint8_t sinBeat1 = beatsin8(60, 0, NUM_LEDS - 1, 0, 0);
  uint8_t sinBeat2 = beatsin8(15, 0, NUM_LEDS - 1, 0,255/2);

  blur1d(leds, NUM_LEDS, 350);
  
  leds[sinBeat1] = getColor();
  leds[sinBeat2] = CRGB::SkyBlue;

  EVERY_N_MILLISECONDS(1) {
    for (int i = 0; i < 5; i++) {
      //blur1d(leds, NUM_LEDS, 150);
    }
  }

  fadeToBlackBy(leds, NUM_LEDS, 2);

  FastLED.show();
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

  currentCC = number;
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);

  EEPROM.write(currentCCAddress, currentCC);
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


