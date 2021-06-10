
// ****** Start Of Included File:main.cpp ****** 
// Teensy-Synth Part 9
// 5-PIN MIDI INPUT
// By Notes and Volts
// www.notesandvolts.com
#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <MIDI.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "constData.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(128, 32, &Wire, -1); // -1 = no reset pin


const int ledPin = 13;
int ledState = LOW;             // ledState used to set the LED
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long currentMillis = 0;
unsigned long currentInterval = 0;
unsigned long ledBlinkOnInterval = 100;
unsigned long ledBlinkOffInterval = 2000;

#define btnInEnablePin 9
#define btnSustainPin 23
#define btnSostenutoPin 22
#define btnSoftPedalPin 21
uint8_t btnSustain = 0;
uint8_t btnSostenuto = 0;
uint8_t btnSoftPedal = 0;
uint8_t btnSustainPressed = 0;
uint8_t btnSostenutoPressed = 0;
uint8_t btnSoftPedalPressed = 0;

#define btnNextInstrumentPin 20
uint8_t btnNextInstrument = 0;
uint8_t btnNextInstrumentPressed = 0;

#define btnSelectInstrumentsA_Pin 17
uint8_t btnSelectInstrumentsA = 0;
uint8_t btnSelectInstrumentsA_Pressed = 0;

#define btnSelectInstrumentsB_Pin 16
uint8_t btnSelectInstrumentsB = 0;
uint8_t btnSelectInstrumentsB_Pressed = 0;

void uartMidi_NoteOn(byte channel, byte note, byte velocity);
void uartMidi_NoteOff(byte channel, byte note, byte velocity);
void uartMidi_ControlChange(byte channel, byte control, byte value);
void uartMidi_PitchBend(byte channel, int value);


void usbMidi_NoteOn(byte channel, byte note, byte velocity);
void usbMidi_NoteOff(byte channel, byte note, byte velocity);
void usbMidi_ControlChange(byte channel, byte control, byte value);
void usbMidi_PitchBend(byte channel, int value);


void uartMidi_ProgramChange(byte channel, byte value);
void usbMidi_ProgramChange(byte channel, byte value);

void blinkLedTask(void);
void btnInputProcessTask(void);

#include "Synth.h"


Synth synth;
//#include "generatedCode.h"
//OneClassMain ocMain;

//AudioMixer<4> mix4;
//AudioMixer<2> mix2;
  
#define KEYBOARD_NOTE_SHIFT_CORRECTION 21//-12

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

void setup()
{
    AudioMemory(96);

    if (display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        delay(2000);
        display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
        delay(2000);
        display.clearDisplay();
        display.display();
        //display.setFont(&FreeMono9pt7b);
        display.setTextSize(1);
        display.setTextColor(WHITE, BLACK);
        display.setCursor(0, 0);
        // Display static text
        display.println("Manicken Poly Synth");
        display.display();
        //delay(1000);
    }
    else{
        //DEBUG_UART.println(F("oled init fail"));
        //if (display.begin(SSD1306_SWITCHCAPVCC, 0x3D))
        //    DEBUG_UART.println(F("oled addr is 0x3D"));
    }
  //mix4.gain(1/4);
  //mix2.gain(1/2);
  
  MIDI.begin();
  MIDI.setHandleNoteOn(uartMidi_NoteOn);
  MIDI.setHandleNoteOff(uartMidi_NoteOff);
  MIDI.setHandleControlChange(uartMidi_ControlChange);
  MIDI.setHandlePitchBend(uartMidi_PitchBend);
  MIDI.setHandleProgramChange(uartMidi_ProgramChange);

  usbMIDI.setHandleNoteOn(usbMidi_NoteOn);
  usbMIDI.setHandleNoteOff(usbMidi_NoteOff);
  usbMIDI.setHandleControlChange(usbMidi_ControlChange);
  usbMIDI.setHandlePitchChange(usbMidi_PitchBend);
  usbMIDI.setHandleProgramChange(usbMidi_ProgramChange);

  synth.begin();
  synth.SetWaveForm_As_Primary();
  //synth.SetWaveTable_As_Primary();
  synth.handleMidiProgramChange(0);
  //synth.set_Instrument(*GMinst[0]);
  //ocMain.begin();

  pinMode(btnSustainPin, INPUT);
  pinMode(btnSostenutoPin, INPUT);
  pinMode(btnSoftPedalPin, INPUT);
  pinMode(btnNextInstrumentPin, INPUT);
  pinMode(btnSelectInstrumentsA_Pin, INPUT);
  pinMode(btnSelectInstrumentsB_Pin, INPUT);

  pinMode(btnInEnablePin, OUTPUT);
  digitalWrite(btnInEnablePin, LOW);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  btnSustainPressed = 0;
  btnSoftPedalPressed = 0;
  btnSostenutoPressed = 0;
  btnNextInstrumentPressed = 0;
  btnSelectInstrumentsA_Pressed = 0;
  btnSelectInstrumentsB_Pressed = 0;
  


}

void loop()
{
    usbMIDI.read();
    MIDI.read();

    btnInputProcessTask();
    
    blinkLedTask();
}

void uartMidi_NoteOn(byte channel, byte note, byte velocity) {
    note += KEYBOARD_NOTE_SHIFT_CORRECTION;
    if (btnSelectInstrumentsA_Pressed == 0 && btnSelectInstrumentsB_Pressed == 0) {
        velocity = 127 - velocity;
        synth.noteOn(note, velocity);
        usbMIDI.sendNoteOn(note, velocity, channel, 0);
    }
    else {
        if (note < 36) note = 0;
        else {
            note -= 36;
            if (note > 63) note = 63;
        }
        if (btnSelectInstrumentsA_Pressed == 1) {
            synth.handleMidiProgramChange(note);

            display.setCursor(0, 7);
            display.println(instrumentNames[note]);

            display.setCursor(0, 24);
            display.print(note);

            display.display();
        }
        else if (btnSelectInstrumentsB_Pressed == 1) {
            synth.handleMidiProgramChange(note+64);

            display.setCursor(0, 7);
            display.println(instrumentNames[note+64]);
            
            display.setCursor(0, 24);
            display.print(note+64);

            display.display();
        }

        
    }
}

void uartMidi_NoteOff(byte channel, byte note, byte velocity) {
    note += KEYBOARD_NOTE_SHIFT_CORRECTION;
    if (btnSelectInstrumentsA_Pressed == 0 && btnSelectInstrumentsB_Pressed == 0) {
        velocity = 127 - velocity;
        synth.noteOff(note);
        usbMIDI.sendNoteOff(note, velocity, channel, 0);
    }
}

void uartMidi_ControlChange(byte channel, byte control, byte value) {
    usbMIDI.sendControlChange(control, value, channel, 0x00);
}

void uartMidi_PitchBend(byte channel, int value) {
    usbMIDI.sendPitchBend(value, channel, 0x00);
}
void uartMidi_ProgramChange(byte channel, byte value) {
    synth.SetWaveTable_As_Primary();
    if (value > 127) value = 127;
    synth.currentWTinstrument = value;
    synth.handleMidiProgramChange(value);
    //synth.set_Instrument(*GMinst[value]);
}
void usbMidi_ProgramChange(byte channel, byte value) {
    synth.SetWaveTable_As_Primary();
    if (value > 127) value = 127;
    synth.currentWTinstrument = value;
    synth.handleMidiProgramChange(value);
    //synth.set_Instrument(*GMinst[value]);
}

void usbMidi_NoteOn(byte channel, byte note, byte velocity) {
    synth.noteOn(note, velocity);
}

void usbMidi_NoteOff(byte channel, byte note, byte velocity) {
    synth.noteOff(note);    
}

void usbMidi_PitchBend(byte channel, int value) {
  
}

void usbMidi_ControlChange(byte channel, byte control, byte value) {
    switch (control) { // cases 20-31,102-119 is undefined in midi spec
        case 64:
          if (value == 0)
            synth.deactivateSustain();
          else if (value == 127)
            synth.activateSustain();
          break;
        case 0:
          if (value == 0) synth.SetWaveForm_As_Primary();
          else if (value == 1) synth.SetWaveTable_As_Primary();
          break;
        case 20: // OSC A waveform select
          synth.set_OSC_A_waveform(value);
          break;
        case 21: // OSC B waveform select
          synth.set_OSC_B_waveform(value);
          break;
        case 22: // OSC C waveform select
          synth.set_OSC_C_waveform(value);
          break;

        case 23:
          synth.set_OSC_A_pulseWidth(value);
          break;
        case 24:
          synth.set_OSC_B_pulseWidth(value);
          break;
        case 25:
          synth.set_OSC_C_pulseWidth(value);
          break;

        case 26:
          synth.set_OSC_A_phase(value);
          break;
        case 27:
          synth.set_OSC_B_phase(value);
          break;
        case 28:
          synth.set_OSC_C_phase(value);
          break;

        case 29:
          synth.set_OSC_A_amplitude(value);
          break;
        case 30:
          synth.set_OSC_B_amplitude(value);
          break;
        case 31:
          synth.set_OSC_C_amplitude(value);
          break;
        case 32: //("LSB for Control 0 (Bank Select)" @ midi spec.)
          synth.set_OSC_D_amplitude(value);
          break;

        case 33: 
          synth.set_mixVoices_gains(value);
          break;
        
        case 100:
          synth.set_envelope_delay(value);
          break;
        case 101:
          synth.set_envelope_attack(value);
          break;
        case 102:
          synth.set_envelope_hold(value);
          break;
        case 103:
          synth.set_envelope_decay(value);
          break;
        case 104:
          synth.set_envelope_sustain(value);
          break;
        case 105:
          synth.set_envelope_release(value);
          break;
                 
        case 108:
          synth.set_OSC_A_freqMult(value);
          break;
        case 109:
          synth.set_OSC_B_freqMult(value);
          break;
        case 110:
          synth.set_OSC_C_freqMult(value);
          break;

        case 115: // set wavetable as primary (Piano mode)
          synth.SetWaveTable_As_Primary();
          break;
        case 116:
          synth.SetWaveForm_As_Primary();
          break;
          
        case 117: // EEPROM read settings
          synth.EEPROM_ReadSettings();
          break;
        case 118: // EEPROM save settings
          synth.EEPROM_SaveSettings();
          break;

        case 119: // get all values
          synth.sendAllSettings();
        break;
    }
}
uint8_t mode = 0;
void btnInputProcessTask(void)
{
  btnSustain = digitalRead(btnSustainPin);
  btnSostenuto = digitalRead(btnSostenutoPin);
  btnSoftPedal = digitalRead(btnSoftPedalPin);
  btnNextInstrument = digitalRead(btnNextInstrumentPin);
  btnSelectInstrumentsA = digitalRead(btnSelectInstrumentsA_Pin);
  btnSelectInstrumentsB = digitalRead(btnSelectInstrumentsB_Pin);

    // Sustain pedal
    if ((btnSustain == LOW) && (btnSustainPressed == 0))
    {
        btnSustainPressed = 1;
        usbMIDI.sendControlChange(0x40, 0x7F, 0x00);
        synth.activateSustain();

        uint16_t memory_used = AudioMemoryUsageMax();
        uint16_t cpu_used = AudioProcessorUsageMax();
        uint8_t data[11];
        data[0] = 0x30 + memory_used/10000;
        data[1] = 0x30 + memory_used%10000/1000;
        data[2] = 0x30 + memory_used%10000%1000/100;
        data[3] = 0x30 + memory_used%10000%1000%100/10;
        data[4] = 0x30 + memory_used%10000%1000%100%10;
        data[5] = ':';
        data[6] = 0x30 + cpu_used/10000;
        data[7] = 0x30 + cpu_used%10000/1000;
        data[8] = 0x30 + cpu_used%10000%1000/100;
        data[9] = 0x30 + cpu_used%10000%1000%100/10;
        data[10] = 0x30 + cpu_used%10000%1000%100%10;
        usbMIDI.sendSysEx(11, data);
    }
    else if ((btnSustain == HIGH) && (btnSustainPressed == 1))
    {
        btnSustainPressed = 0;
        usbMIDI.sendControlChange(0x40, 0x00, 0x00);
        synth.deactivateSustain();
    }
    // Sostenuto Pedal
    if ((btnSostenuto == LOW) && (btnSostenutoPressed == 0))
    {
        btnSostenutoPressed = 1;
        usbMIDI.sendControlChange(0x42, 0x7F, 0x00);
    }
    else if ((btnSostenuto == HIGH) && (btnSostenutoPressed == 1))
    {
        btnSostenutoPressed = 0;
        usbMIDI.sendControlChange(0x42, 0x00, 0x00);
    }
    // Soft Pedal
    if ((btnSoftPedal == LOW) && (btnSoftPedalPressed == 0))
    {
        btnSoftPedalPressed = 1;
        usbMIDI.sendControlChange(0x43, 0x7F, 0x00);
    }
    else if ((btnSoftPedal == HIGH) && (btnSoftPedalPressed == 1))
    {
        btnSoftPedalPressed = 0;
        usbMIDI.sendControlChange(0x43, 0x00, 0x00);
    }
    // Next Instrument button
    if ((btnNextInstrument == LOW) && (btnNextInstrumentPressed == 0))
    {
        btnNextInstrumentPressed = 1;

        if (mode == 0) { mode = 1; synth.SetWaveTable_As_Primary(); }
        else if (mode == 1) { mode = 0; synth.SetWaveForm_As_Primary(); }
        /*if (synth.currentWTinstrument == (128 - 1)) synth.currentWTinstrument = 0;
        else synth.currentWTinstrument++;
        
        synth.handleMidiProgramChange(synth.currentWTinstrument);
        usbMIDI.sendProgramChange(0, synth.currentWTinstrument, 0x00);*/
    }
    else if ((btnNextInstrument == HIGH) && (btnNextInstrumentPressed == 1))
    {
        btnNextInstrumentPressed = 0;
    }

    if ((btnSelectInstrumentsA == LOW) && (btnSelectInstrumentsA_Pressed == 0)) {
        btnSelectInstrumentsA_Pressed = 1;
        display.setCursor(0, 0);
        display.println("Instruments 0-63     ");
        display.display();
    }
    else if ((btnSelectInstrumentsA == HIGH) && (btnSelectInstrumentsA_Pressed == 1)) {
        btnSelectInstrumentsA_Pressed = 0;
    }
    if ((btnSelectInstrumentsB == LOW) && (btnSelectInstrumentsB_Pressed == 0)) {
        btnSelectInstrumentsB_Pressed = 1;
        display.setCursor(0, 0);
        display.println("Instruments 64-127   ");
        display.display();
    }
    else if ((btnSelectInstrumentsA == HIGH) && (btnSelectInstrumentsB_Pressed == 1)) {
        btnSelectInstrumentsB_Pressed = 0;
    }
}

void blinkLedTask(void)
{
    currentMillis = millis();
    currentInterval = currentMillis - previousMillis;
    
    if (ledState == LOW)
    {
        if (currentInterval > ledBlinkOffInterval)
        {
            previousMillis = currentMillis;
            ledState = HIGH;
            digitalWrite(ledPin, HIGH);
        }
    }
    else
    {
        if (currentInterval > ledBlinkOnInterval)
        {
            previousMillis = currentMillis;
            ledState = LOW;
            digitalWrite(ledPin, LOW);
        }
    }
}
// ****** End Of Included file:main.cpp ******
