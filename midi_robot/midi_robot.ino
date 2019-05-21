//MIDI Signal to Signal for MOSFET
//Daniel Lindner


#include <MIDI.h>

#define selectedChannel 1
#define t2 53
#define t3 51
#define t4 49
#define t5 47
#define t6 45
#define t7 43
#define t8 41
#define t9 39
#define startButtonInterrupt 3

volatile bool onState;

/*
  top is by mouthpiece

   t2 bottom
   t3 top
   t4 second hole down form top
   t5 ...
*/

MIDI_CREATE_DEFAULT_INSTANCE();

void setup()
{
  //Setup MIDI
  MIDI.setHandleNoteOn(onNoteOn);
  MIDI.setHandleNoteOff(onNoteOff);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  //Setup Solenoids
  pinMode(t2, OUTPUT);
  pinMode(t3, OUTPUT);
  pinMode(t4, OUTPUT);
  pinMode(t5, OUTPUT);
  pinMode(t6, OUTPUT);
  pinMode(t7, OUTPUT);
  pinMode(t8, OUTPUT);
  pinMode(t9, OUTPUT);

  //Setup Start/Stop Button
  onState = false;
  pinMode(startButtonInterrupt, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(startButtonInterrupt), toggleStart, FALLING);

  //Setup debug
  Serial.begin(9600);

  Serial.println("Press StartButton to begin.");
  
  while (!onState) {
    //Wait for Start
  }

}

void loop()
{
  if (onState) {

    MIDI.read();

  } else {
    stopPlay();
    Serial.println("Press StartButton to begin.");
  }
}

void onNoteOn(byte channel, byte pitch, byte velocity)
{
  //Act on Note recieved
  if (channel != selectedChannel) {
    return; //Filter for right channel
  }

  switch (pitch) {
    case 56: playLowG(); break;
    case 58: playLowA(); break;
    case 60: playB(); break;
    case 62: playC(); break;
    case 63: playD(); break;
    case 65: playE(); break;
    case 67: playF(); break;
    case 68: playHighG(); break;
    case 70: playHighA(); break;
    default: Serial.print("Note: ");
      Serial.print(pitch);
      Serial.println(" not mapped.");
      break;

  }
}

void onNoteOff(byte channel, byte pitch, byte velocity) {
  // Act on Note released
  if (channel != selectedChannel) {
    return;
  }

  stopPlay();
}

void toggleStart() {
  onState = !onState;
}

void playLowG()
{
  digitalWrite(t2 , HIGH);
  digitalWrite(t3 , HIGH);
  digitalWrite(t4 , HIGH);
  digitalWrite(t5 , HIGH);
  digitalWrite(t6 , HIGH);
  digitalWrite(t7 , HIGH);
  digitalWrite(t8 , HIGH);
  digitalWrite(t9 , HIGH);

  Serial.println("Playing LowG.");
}


void playLowA()
{
  digitalWrite(t2 , HIGH);
  digitalWrite(t3 , HIGH);
  digitalWrite(t4 , HIGH);
  digitalWrite(t5 , HIGH);
  digitalWrite(t6 , HIGH);
  digitalWrite(t7 , HIGH);
  digitalWrite(t8 , HIGH);

  Serial.println("Playing LowA.");
}



void playB()
{
  digitalWrite(t2 , HIGH);
  digitalWrite(t3 , HIGH);
  digitalWrite(t4 , HIGH);
  digitalWrite(t5 , HIGH);
  digitalWrite(t6 , HIGH);
  digitalWrite(t7 , HIGH);

  Serial.println("Playing B.");
}

void playC()
{
  digitalWrite(t2 , HIGH);
  digitalWrite(t3 , HIGH);
  digitalWrite(t4 , HIGH);
  digitalWrite(t5 , HIGH);
  digitalWrite(t6 , HIGH);
  digitalWrite(t9 , HIGH);

  Serial.println("Playing C.");
}

void playD()
{
  digitalWrite(t2 , HIGH);
  digitalWrite(t3 , HIGH);
  digitalWrite(t4 , HIGH);
  digitalWrite(t5 , HIGH);
  digitalWrite(t9 , HIGH);

  Serial.println("Playing D.");
}

void playE()
{
  digitalWrite(t2 , HIGH);
  digitalWrite(t3 , HIGH);
  digitalWrite(t4 , HIGH);
  digitalWrite(t6 , HIGH);
  digitalWrite(t7 , HIGH);
  digitalWrite(t8 , HIGH);

  Serial.println("Playing E.");
}

void playF()
{
  digitalWrite(t2 , HIGH);
  digitalWrite(t3 , HIGH);
  digitalWrite(t6 , HIGH);
  digitalWrite(t7 , HIGH);
  digitalWrite(t8 , HIGH);

  Serial.println("Playing F.");
}

void playHighG()
{
  digitalWrite(t2 , HIGH);
  digitalWrite(t6 , HIGH);
  digitalWrite(t7 , HIGH);
  digitalWrite(t8 , HIGH);

  Serial.println("Playing HighG.");
}

void playHighA()
{
  digitalWrite(t5 , HIGH);
  digitalWrite(t6 , HIGH);
  digitalWrite(t7 , HIGH);
  digitalWrite(t8 , HIGH);

  Serial.println("Playing HighA.");
}

void stopPlay()
{
  // Deactivate all Solenoids
  digitalWrite(t2, LOW);
  digitalWrite(t3, LOW);
  digitalWrite(t4, LOW);
  digitalWrite(t5, LOW);
  digitalWrite(t6, LOW);
  digitalWrite(t7, LOW);
  digitalWrite(t8, LOW);
  digitalWrite(t9, LOW);
}
