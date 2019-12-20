/*  Example using waveshaping to modify the spectrum of an audio signal
    using Mozzi sonification library.
  
    Demonstrates the use of WaveShaper(), EventDelay(), Smooth(),
    rand(), and fixed-point numbers.
  
    Circuit: Audio output on digital pin 9 on a Uno or similar, or
    DAC/A14 on Teensy 3.0/3.1, or 
    check the README or http://sensorium.github.com/Mozzi/
  
    Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users
  
    Tim Barrass 2012, CC by-nc-sa.
*/

//#include <ADC.h>  // Teensy 3.0/3.1 uncomment this line and install http://github.com/pedvide/ADC
//
#define PIN_CTRL 13

#include <MozziGuts.h>
#include <Oscil.h>
#include <WaveShaper.h>
#include <EventDelay.h>
#include <mozzi_rand.h>
#include <mozzi_midi.h>
#include <Smooth.h>
#include <tables/sin2048_int8.h>
#include <tables/waveshape_chebyshev_3rd_256_int8.h>
#include <tables/waveshape_chebyshev_6th_256_int8.h>
#include <tables/waveshape_compress_512_to_488_int16.h>


#include "PinChangeInterrupt.h"
// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 68 // powers of 2 please

// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA); // sine wave sound source
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aGain1(SIN2048_DATA); // to fade sine wave in and out before waveshaping
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aGain2(SIN2048_DATA); // to fade sine wave in and out before waveshaping

// Chebyshev polynomial curves, The nth curve produces the n+2th harmonic component.
WaveShaper <char> aCheby3rd(CHEBYSHEV_3RD_256_DATA); // 5th harmonic
WaveShaper <char> aCheby6th(CHEBYSHEV_6TH_256_DATA); // 8th harmonic
WaveShaper <int> aCompress(WAVESHAPE_COMPRESS_512_TO_488_DATA); // to compress instead of dividing by 2 after adding signals

// for scheduling note changes
EventDelay kChangeNoteDelay;

// for random notes
Q8n0 octave_start_note = 84;
Q24n8 carrier_freq; // unsigned long with 24 integer bits and 8 fractional bits

// smooth transitions between notes
Smooth <unsigned int> kSmoothFreq(0.85f);
int target_freq, smoothed_freq;



void setup(){

  sleepMode(SLEEP_POWER_DOWN);
  disablePower(POWER_ADC);
  //disablePower(POWER_SPI);
  disablePower(POWER_SERIAL0);
  disablePower(POWER_SERIAL1);

  pinMode(13, OUTPUT);
  pinMode(A0, INPUT_PULLUP);
  attachPCINT(digitalPinToPCINT(A0), onPress, FALLING);

  startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
  randSeed(); // reseed the random generator for different results each time the sketch runs
  aSin.setFreq(220); // set the frequency
  aGain1.setFreq(4.f); // use a float for low frequencies, in setup it doesn't need to be fast
  aGain2.setFreq(.8f);
  kChangeNoteDelay.set(4000); // note duration ms, within resolution of CONTROL_RATE
}

bool interrupted = false;
void onPress(){

}

byte rndPentatonic(){
  byte note = rand((byte)5);
  // insert reading from accel
  switch(note){
  case 0:
    note = 0;
    break;
  case 1:
    note = 3;
    break;
  case 2:
    note = 5;
    break;
  case 3:
    note = 7;
    break;
  case 4:
    note = 10;
    break;
  }
  return note;
}

void updateControl(){
  if(kChangeNoteDelay.ready()){
    if(rand((byte)5)<=2){ // about 1 in 5 or so
      // change octave to midi 24 or any of 3 octaves above
      octave_start_note = (rand((byte)5)*10)+36;
      // TODO replace by acel reading
    }
    Q16n16 midi_note = Q8n0_to_Q16n16(octave_start_note+rndPentatonic());
    target_freq = Q16n16_to_Q16n0(Q16n16_mtof(midi_note)); // has to be 16 bits for Smooth
    kChangeNoteDelay.start();
  }
  smoothed_freq = kSmoothFreq.next(target_freq*4); // temporarily scale up target_freq to get better int smoothing at low values
  aSin.setFreq(smoothed_freq/4); // then scale it back down after it's smoothed
}


int updateAudio(){
  char asig0 = aSin.next(); // sine wave source
  // make 2 signals fading in and out to show effect of amplitude when waveshaping with Chebyshev polynomial curves
  // offset the signals by 128 to fit in the 0-255 range for the waveshaping table lookups
  byte asig1 = (byte)128+((asig0*((byte)128+aGain1.next()))>>8);
  byte asig2 = (byte)128+((asig0*((byte)128+aGain2.next()))>>8);
  // get the waveshaped signals
  char awaveshaped1 = aCheby3rd.next(asig1);
  char awaveshaped2 = aCheby6th.next(asig2);
  // use a waveshaping table to squeeze 2 summed 8 bit signals into the range -244 to 243
  int awaveshaped3 = aCompress.next(256u + awaveshaped1 + awaveshaped2);
  return awaveshaped3;
}



void loop(){
  digitalWrite(PIN_CTRL, HIGH);
  enablePower(POWER_TIMER1);
  enablePower(POWER_TIMER2);
  enablePower(POWER_TIMER3);
  interrupted = false;

  if(!digitalRead(A0)){
    audioHook(); // required here
  }else{
    delay(10);
    if(digitalRead(A0)){
      digitalWrite(PIN_CTRL, LOW);
      disablePower(POWER_TIMER1);
      disablePower(POWER_TIMER2);
      disablePower(POWER_TIMER3);
      sleep();
    }
  }
}





