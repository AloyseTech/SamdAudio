/*
  ###########################
        WORK IN PROGRESS
  ###########################
  Audio player, non blocking.
  read 8bit mono .wav file, up to 4 channels
  use Audacity to convert your audio file

  Author : AloyseTech
*/

#include <SdFat.h>
SdFat SD;
#include <SPI.h>
#include <SamdAudio.h>
SamdAudio AudioPlayer;

// which Serial you prefer, for information.
#define SERIAL SerialUSB
//#define SERIAL Serial

// SD chip select pin (with ethernet shield : 4)
#define YOUR_SD_CS 29

//your wav file
const char *filename = "TRACK/CASTROCK.wav";

//indicate sample rate here (use audacity to convert your wav)
const unsigned int sampleRate = 22050;

bool state = true;

uint32_t timer = 0, updatetimer = 0;

void setup()
{
  pinMode(15, OUTPUT);
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(16, OUTPUT);

  // debug output at 115200 baud
  delay(10);
  SERIAL.begin(115200);
  while (!SERIAL);
  //delay(500);

  // setup SD-card
  SERIAL.print("Initializing SD card...");
  if (!SD.begin(YOUR_SD_CS)) {
    SERIAL.println(" failed!");
    return;
  }

  SERIAL.println(" done.");

  // hi-speed SPI transfers
  // TODO: should be replaced by beginTx and endTx in SD lib...
  //SPI.setClockDivider(4);

  pinMode(16, OUTPUT);

  digitalWrite(16, HIGH);

  AudioPlayer.begin(sampleRate);
  AudioPlayer.play(filename, 0);

  SERIAL.println("Playing file.....");
}

void loop()
{
  if (millis() - timer > 500) {

    //I'm working late at night, full led brightness is painfull!
    digitalWrite(15, state);
    //analogWrite(15, state ? 0 : 4);

    state = !state;
    timer = millis();
  }


  if (!digitalRead(0))
    AudioPlayer.play("FX/FX6.wav", 0);
  if (!digitalRead(1))
    AudioPlayer.play("FX/FX5.wav", 1);
  if (!digitalRead(2))
    AudioPlayer.play("TRACK/HAWKEYE.wav", 2);
  if (!digitalRead(3))
    AudioPlayer.play("TRACK/COMMANDO.wav", 3);


  if (SERIAL.available()) {
    char c = SERIAL.read();

    if ( c == 'o') {
      AudioPlayer.play("FX/FX6.wav", 0);
      SERIAL.println("pouwww! ch1!");
    }
    else if ( c == 'O') {
      AudioPlayer.play("FX/FX6.wav", 1);
      SERIAL.println("pouwww! ch2!");
    }
    else if ( c == 's') {
      AudioPlayer.play("TRACK/HAWKEYE.wav", 0);
      SERIAL.println("hawkeye ch1!");
    }
    else if ( c == 'S') {
      AudioPlayer.play("TRACK/HAWKEYE.wav", 1);
      SERIAL.println("hawkeye ch2!");
    }
    else if ( c == 'd') {
      AudioPlayer.play("TRACK/COMMANDO.wav", 0);
      SERIAL.println("commando ch1!");
    }
    else if ( c == 'D') {
      AudioPlayer.play("TRACK/COMMANDO.wav", 1);
      SERIAL.println("commando ch2!");
    }
    else if ( c == 'm') {
      AudioPlayer.play("TRACK/MARIACHI.wav", 0);
      SERIAL.println("mariachi ch1!");
    }
    else if ( c == 'M') {
      AudioPlayer.play("TRACK/MARIACHI.wav", 1);
      SERIAL.println("mariachi ch2!");
    }
    else if ( c == 'l') {
      AudioPlayer.play("TRACK/GRANNIES.wav", 0);
      SERIAL.println("GRANNIES ch1!");
    }
    else if ( c == 'L') {
      AudioPlayer.play("TRACK/GRANNIES.wav", 1);
      SERIAL.println("GRANNIES ch2!");
    }

    else if ( c == '0') {
      AudioPlayer.stopChannel(0);
      SERIAL.println("ch1 off!");
    }
    else if ( c == '1') {
      AudioPlayer.stopChannel(1);
      SERIAL.println("ch2 off!");
    }
    else if ( c == '2') {
      AudioPlayer.stopChannel(2);
      SERIAL.println("ch3 off!");
    }
    else if ( c == '3') {
      AudioPlayer.stopChannel(3);
      SERIAL.println("ch4 off!");
    }
  }

}
