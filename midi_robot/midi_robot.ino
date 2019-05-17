//MIDI Signal to Signal for MOSFET
//Daniel Lindner


#include <MIDI.h>

static const unsigned offset = 0;
static const unsigned invert = 0; // Set to 1 to invert

MIDI_CREATE_DEFAULT_INSTANCE();

void setup()
{
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  //Define DO Pins    1 nearest to mouthpiece
  // 1 bottom
  // 2 top 
  // 3 seconds hole down on top ...
  for(int i = 0; i < 8; i++)
  {
    pinMode(i+ 1 + offset, OUTPUT);
  }
  
}

void loop()
{
  
  MIDI.read();

}

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  //Act on Note recieved
  
  
}

void handleNoteOff(byte channel, byte pitch, byte velocity){
  // Act on Note released
}


void playLowG()
{
  digitalWrite(1 + offset, HIGH);
  digitalWrite(2 + offset, HIGH);
  digitalWrite(3 + offset, HIGH);
  digitalWrite(4 + offset, HIGH);
  digitalWrite(5 + offset, HIGH);
  digitalWrite(6 + offset, HIGH);
  digitalWrite(7 + offset, HIGH);
  digitalWrite(8 + offset, HIGH);
}


void playLowA()
{
  digitalWrite(1 + offset, HIGH);
  digitalWrite(2 + offset, HIGH);
  digitalWrite(3 + offset, HIGH);
  digitalWrite(4 + offset, HIGH);
  digitalWrite(5 + offset, HIGH);
  digitalWrite(6 + offset, HIGH);
  digitalWrite(7 + offset, HIGH);
}



void playB()
{
  digitalWrite(1 + offset, HIGH);
  digitalWrite(2 + offset, HIGH);
  digitalWrite(3 + offset, HIGH);
  digitalWrite(4 + offset, HIGH);
  digitalWrite(5 + offset, HIGH);
  digitalWrite(6 + offset, HIGH);
}

void playC()
{
  digitalWrite(1 + offset, HIGH);
  digitalWrite(2 + offset, HIGH);
  digitalWrite(3 + offset, HIGH);
  digitalWrite(4 + offset, HIGH);
  digitalWrite(5 + offset, HIGH);
  digitalWrite(8 + offset, HIGH);
}

void playD()
{
  digitalWrite(1 + offset, HIGH);
  digitalWrite(2 + offset, HIGH);
  digitalWrite(3 + offset, HIGH);
  digitalWrite(4 + offset, HIGH);
  digitalWrite(8 + offset, HIGH);
}

void playE()
{
  digitalWrite(1 + offset, HIGH);
  digitalWrite(2 + offset, HIGH);
  digitalWrite(3 + offset, HIGH);
  digitalWrite(5 + offset, HIGH);
  digitalWrite(6 + offset, HIGH);
  digitalWrite(7 + offset, HIGH);
}

void playF()
{
  digitalWrite(1 + offset, HIGH);
  digitalWrite(2 + offset, HIGH);
  digitalWrite(5 + offset, HIGH);
  digitalWrite(6 + offset, HIGH);
  digitalWrite(7 + offset, HIGH);
}

void playHighG()
{
  digitalWrite(1 + offset, HIGH);
  digitalWrite(5 + offset, HIGH);
  digitalWrite(6 + offset, HIGH);
  digitalWrite(7 + offset, HIGH);
}

void playHighA()
{
  digitalWrite(4 + offset, HIGH);
  digitalWrite(5 + offset, HIGH);
  digitalWrite(6 + offset, HIGH);
  digitalWrite(7 + offset, HIGH);
}

void stopPlay()
{
    // Deactivate all Solenoids
    for(int i = 0; i < 8; i++)
    {
        digitalWrite(i + 1 + offset, LOW);
    }
}
