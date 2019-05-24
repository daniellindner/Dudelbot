#include <MIDI.h>
#include <SoftwareSerial.h>

static const unsigned offset = 0;
bool startProgram= false;
int button=9;
const byte rxPin=10;
const byte txPin=11;
byte statusByte;
byte dataByte1 ;
byte dataByte2;
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

void setup()
{
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);

  for(int i = 0; i < 8; i++)
  {
    pinMode(i+ 1 + offset, OUTPUT);
  }
  
  pinMode(button, INPUT_PULLUP);
  digitalWrite(button, HIGH);
  // start Pumpe
  
  Serial.begin(9600);
  
}

void loop()
{
  if (digitalRead(button)==LOW)
    {if (startProgram==false)
        {startProgram=true;}
        else 
          {startProgram=false;}
    }


  if(startProgram==true)
    {
  empfangMIDI();
    }
   else {stopPlay();}
}


void empfangMIDI(){
  // das Lesen von MidiBytes
   while (Serial.available() > 2)
     {
            statusByte = Serial.read();
            dataByte1 = Serial.read();
            dataByte2 = Serial.read();
             
     if((statusByte==144)&&( dataByte1>=0))
            { handleNoteOn(dataByte1);
              }
        else {stopPlay(); }      
     
     }

  

void handleNoteOn(byte pitch)
{
  //Act on Note recieved
  switch(pitch){
    case(56): playLowG();break;
    case(58):playLowA();break;
    case(60):playB();break;
    case(62):playC();break;
    case(63):playD();break;
    case(65):playE();break;
    case(67):playF();break;
    case(68):playHighG();break;
    case(70):playHighA();break;
    default: Serial.println("pitch can not be played");
    
  }
  
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
  digitalWrite(8 + offset, LOW);
}



void playB()
{
  digitalWrite(1 + offset, HIGH);
  digitalWrite(2 + offset, HIGH);
  digitalWrite(3 + offset, HIGH);
  digitalWrite(4 + offset, HIGH);
  digitalWrite(5 + offset, HIGH);
  digitalWrite(6 + offset, HIGH);
  digitalWrite(7 + offset, LOW);
  digitalWrite(8 + offset, LOW);
}

void playC()
{
  digitalWrite(1 + offset, HIGH);
  digitalWrite(2 + offset, HIGH);
  digitalWrite(3 + offset, HIGH);
  digitalWrite(4 + offset, HIGH);
  digitalWrite(5 + offset, HIGH);
  digitalWrite(6 + offset, LOW);
  digitalWrite(7 + offset, LOW);
  digitalWrite(8 + offset, HIGH);
}

void playD()
{
  digitalWrite(1 + offset, HIGH);
  digitalWrite(2 + offset, HIGH);
  digitalWrite(3 + offset, HIGH);
  digitalWrite(4 + offset, HIGH);
  digitalWrite(5 + offset, LOW);
  digitalWrite(6 + offset, LOW);
  digitalWrite(7 + offset, LOW);
  digitalWrite(8 + offset, HIGH);
}

void playE()
{
  digitalWrite(1 + offset, HIGH);
  digitalWrite(2 + offset, HIGH);
  digitalWrite(3 + offset, HIGH);
  digitalWrite(4 + offset, LOW);
  digitalWrite(5 + offset, HIGH);
  digitalWrite(6 + offset, HIGH);
  digitalWrite(7 + offset, HIGH);
  digitalWrite(8 + offset, LOW);
}

void playF()
{
  digitalWrite(1 + offset, HIGH);
  digitalWrite(2 + offset, HIGH);
  digitalWrite(3 + offset, LOW);
  digitalWrite(4 + offset, LOW);
  digitalWrite(5 + offset, HIGH);
  digitalWrite(6 + offset, HIGH);
  digitalWrite(7 + offset, HIGH);
  digitalWrite(8 + offset, LOW);
}

void playHighG()
{
  digitalWrite(1 + offset, HIGH);
  digitalWrite(2 + offset, LOW);
  digitalWrite(3 + offset, LOW);
  digitalWrite(4 + offset, LOW);
  digitalWrite(5 + offset, HIGH);
  digitalWrite(6 + offset, HIGH);
  digitalWrite(7 + offset, HIGH);
  digitalWrite(8 + offset, LOW);
}

void playHighA()
{
  digitalWrite(1 + offset, LOW);
  digitalWrite(2 + offset, LOW);
  digitalWrite(3 + offset, LOW);
  digitalWrite(4 + offset, HIGH);
  digitalWrite(5 + offset, HIGH);
  digitalWrite(6 + offset, HIGH);
  digitalWrite(7 + offset, HIGH);
  digitalWrite(8 + offset, LOW);
}

void stopPlay()
{
    // Deactivate all Solenoids
    for(int i = 0; i < 8; i++)
    {
        digitalWrite(i + 1 + offset, LOW);
    }
}
