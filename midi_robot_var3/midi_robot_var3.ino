//MIDI Signal to Signal for MOSFET
//Daniel, Amal, Hazem


#include <MIDI.h>
#include <Bounce2.h>

#define selectedChannel 1
#define tCompressor 29
#define t2 23
#define t3 38
#define t4 40
#define t5 42
#define t6 44
#define t7 46
#define t8 48
#define t9 50
#define startButton 41
#define stopButton 43
#define compressorButton 45
#define redLED 37
#define greenLED 53
#define blueLED 35

/*
  top is by mouthpiece

   t2 bottom
   t3 top
   t4 second hole down form top
   t5 ...
*/

bool onState;
bool compressorState;
int count; //debug



MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

Bounce debounceStart = Bounce();
Bounce debounceStop = Bounce();
Bounce debounceCompressor = Bounce();

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
  pinMode(tCompressor, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  count = 0; //debug

  //Setup Start/Stop/Compressor Button
  onState = false;
  compressorState = false;
  pinMode(startButton, INPUT_PULLUP);
  debounceStart.attach(startButton);
  debounceStart.interval(5);
  pinMode(stopButton, INPUT_PULLUP);
  debounceStop.attach(stopButton);
  debounceStop.interval(5);
  pinMode(compressorButton, INPUT_PULLUP);
  debounceCompressor.attach(compressorButton);
  debounceCompressor.interval(5);

  //Setup debug
  Serial.begin(115200);
  while (!Serial) {}
  Serial.println("Dudelbot");
  Serial.println("Press Start to Play.");
}

void loop()
{
  updateButtons();
  updateLED();
  //debug();

  digitalWrite(tCompressor, compressorState); //Start Stop Compressor
  MIDI.read();

  if (!onState) {
    stopPlay();
  }
}

void onNoteOn(byte channel, byte pitch, byte velocity)
{
  //Act on Note recieved
  /*if (channel != selectedChannel) {
    return; //Filter for right channel
    }*/
  if(!onState){
    return;
  }
  pitch += 1;

  switch (pitch) {
    case 55:
    case 56: playLowG(); break;
    case 57:
    case 58: playLowA(); break;
    case 59: playNaturalB(); break;
    case 60: playB(); break;
    case 61: playNaturalC(); break;
    case 62: playC(); break;
    case 63: playD(); break;
    case 64: playNaturalE(); break;
    case 65: playE(); break;
    case 66: playNaturalF(); break;
    case 67: playF(); break;
    case 68: playHighG(); break;
    case 69: playSharpG(); break;
    case 70: playHighA(); break;
    case 71: playHighBFlat(); break;
    case 72: playHighB(); break;
    case 73: playHighCFlat(); break;
    case 74: playHighC(); break;
    case 75: playHighD(); break;
    case 76: playHighEFlat(); break;
    case 77: playHighE(); break;
    default: Serial.print("Note: ");
      Serial.print(pitch);
      Serial.println(" not mapped.");
      break;

  }
  //Serial.print("Channel: "); Serial.println(channel);
}

void onNoteOff(byte channel, byte pitch, byte velocity) {
  // Act on Note released
  /*
  if (channel != selectedChannel) {
    return;
  }
  */

  stopPlay();
}

void debug() {
  static long last_debug = 0;
  long now = millis();

  Serial.print("OnState\t");
  Serial.println(onState);
  Serial.print("CompressorState\t");
  Serial.println(compressorState);

}

void updateButtons() {
  //check for pressed Buttons
  debounceStart.update();
  debounceStop.update();
  debounceCompressor.update();

  if (debounceStart.fell()) {
    onState = true;
    Serial.print("onState:\t");
    Serial.println(onState);
  }
  if (debounceStop.fell()) {
    onState = false;
    compressorState = false;
    Serial.print("onState:\t");
    Serial.println(onState);
  }
  if (debounceCompressor.fell()) {
    compressorState = !compressorState;
    Serial.print("CompressorState:\t");
    Serial.println(compressorState);
  }
}

void updateLED() {
  //update Status LED
  // RED = off
  // BLUE = compressor active
  // green = on
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);

  if (onState) {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(blueLED, LOW);
  } else if (compressorState) {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, HIGH);
  } else {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
  }
}

void playLowG()
{
  digitalWrite(t2 , LOW);
  digitalWrite(t3 , LOW);
  digitalWrite(t4 , LOW);
  digitalWrite(t5 , LOW);
  digitalWrite(t6 , LOW);
  digitalWrite(t7 , LOW);
  digitalWrite(t8 , LOW);
  digitalWrite(t9 , LOW);

  Serial.println("Playing LowG.");
}


void playLowA()
{
  digitalWrite(t2 , LOW);
  digitalWrite(t3 , LOW);
  digitalWrite(t4 , LOW);
  digitalWrite(t5 , LOW);
  digitalWrite(t6 , LOW);
  digitalWrite(t7 , LOW);
  digitalWrite(t8 , LOW);

  Serial.println("Playing LowA.");
}

void playNaturalB()
{
  digitalWrite(t2 , LOW);
  digitalWrite(t3 , LOW);
  digitalWrite(t4 , LOW);
  digitalWrite(t5 , LOW);
  digitalWrite(t6 , LOW);
  digitalWrite(t7 , LOW);
  digitalWrite(t9 , LOW);

  Serial.println("Playing NaturalB.");
}

void playB()
{
  digitalWrite(t2 , LOW);
  digitalWrite(t3 , LOW);
  digitalWrite(t4 , LOW);
  digitalWrite(t5 , LOW);
  digitalWrite(t6 , LOW);
  digitalWrite(t7 , LOW);

  Serial.println("Playing B.");
}

void playNaturalC()
{
  digitalWrite(t2 , LOW);
  digitalWrite(t3 , LOW);
  digitalWrite(t4 , LOW);
  digitalWrite(t5 , LOW);
  digitalWrite(t6 , LOW);
  digitalWrite(t8 , LOW);

  Serial.println("Playing NaturalC.");
}

void playC()
{
  digitalWrite(t2 , LOW);
  digitalWrite(t3 , LOW);
  digitalWrite(t4 , LOW);
  digitalWrite(t5 , LOW);
  digitalWrite(t6 , LOW);
  digitalWrite(t9 , LOW);

  Serial.println("Playing C.");
}

void playD()
{
  digitalWrite(t2 , LOW);
  digitalWrite(t3 , LOW);
  digitalWrite(t4 , LOW);
  digitalWrite(t5 , LOW);
  digitalWrite(t9 , LOW);

  Serial.println("Playing D.");
}

void playNaturalE()
{
  digitalWrite(t2 , LOW);
  digitalWrite(t3 , LOW);
  digitalWrite(t4 , LOW);
  digitalWrite(t5 , LOW);
  digitalWrite(t7 , LOW);
  digitalWrite(t8 , LOW);

  Serial.println("Playing NaturalE.");
}

void playE()
{
  digitalWrite(t2 , LOW);
  digitalWrite(t3 , LOW);
  digitalWrite(t4 , LOW);
  digitalWrite(t6 , LOW);
  digitalWrite(t7 , LOW);
  digitalWrite(t8 , LOW);

  Serial.println("Playing E.");
}

void playNaturalF()
{
  digitalWrite(t2 , LOW);
  digitalWrite(t3 , LOW);
  digitalWrite(t5 , LOW);
  digitalWrite(t6 , LOW);
  digitalWrite(t7 , LOW);
  digitalWrite(t8 , LOW);

  Serial.println("Playing NaturalF.");
}

void playF()
{
  digitalWrite(t2 , LOW);
  digitalWrite(t3 , LOW);
  digitalWrite(t6 , LOW);
  digitalWrite(t7 , LOW);
  digitalWrite(t8 , LOW);

  Serial.println("Playing F.");
}

void playHighG()
{
  digitalWrite(t2 , LOW);
  digitalWrite(t4 , LOW);
  digitalWrite(t5 , LOW);

  Serial.println("Playing HighG.");
}

void playSharpG()
{
  digitalWrite(t2 , LOW);
  digitalWrite(t4 , LOW);
  digitalWrite(t5 , LOW);
  digitalWrite(t6 , LOW);
  digitalWrite(t8 , LOW);

  Serial.println("Playing SharpG.");
}

void playHighA()
{
  digitalWrite(t5 , LOW);
  digitalWrite(t6 , LOW);
  digitalWrite(t7 , LOW);
  digitalWrite(t8 , LOW);

  Serial.println("Playing HighA.");
}

void playHighBFlat()
{
  digitalWrite(t3 , LOW);
  digitalWrite(t4 , LOW);
  digitalWrite(t5 , LOW);
  digitalWrite(t6 , LOW);
  digitalWrite(t7 , LOW);
  digitalWrite(t9 , LOW);

  Serial.println("Playing HighBFlat.");
}

void playHighB()
{
  digitalWrite(t3 , LOW);
  digitalWrite(t4 , LOW);
  digitalWrite(t5 , LOW);
  digitalWrite(t6 , LOW);
  digitalWrite(t7 , LOW);

  Serial.println("Playing HighB.");
}

void playHighCFlat()
{
  digitalWrite(t3 , LOW);
  digitalWrite(t4 , LOW);
  digitalWrite(t5 , LOW);
  digitalWrite(t6 , LOW);
  digitalWrite(t8 , LOW);

  Serial.println("Playing HighCFlat.");
}

void playHighC()
{
  digitalWrite(t3 , LOW);
  digitalWrite(t4 , LOW);
  digitalWrite(t5 , LOW);
  digitalWrite(t6 , LOW);

  Serial.println("Playing HighC.");
}

void playHighD()
{
  digitalWrite(t3 , LOW);
  digitalWrite(t4 , LOW);
  digitalWrite(t5 , LOW);

  Serial.println("Playing HighD.");
}

void playHighEFlat()
{
  digitalWrite(t3 , LOW);
  digitalWrite(t4 , LOW);
  digitalWrite(t5 , LOW);
  digitalWrite(t7 , LOW);
  digitalWrite(t9 , LOW);

  Serial.println("Playing HighEFlat.");
}

void playHighE()
{
  digitalWrite(t3 , LOW);
  digitalWrite(t4 , LOW);
  digitalWrite(t6 , LOW);

  Serial.println("Playing HighE.");
}

void stopPlay()
{
  // Deactivate all Solenoids
  digitalWrite(t2, HIGH);
  digitalWrite(t3, HIGH);
  digitalWrite(t4, HIGH);
  digitalWrite(t5, HIGH);
  digitalWrite(t6, HIGH);
  digitalWrite(t7, HIGH);
  digitalWrite(t8, HIGH);
  digitalWrite(t9, HIGH);

  Serial.println("Stopped.");
}
