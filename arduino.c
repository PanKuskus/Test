const int pinButtons[] = {5, 6, 7};
const int numOfButtons = 3;
const int pinEncoder1 = 2;
const int pinEncoder2 = 3;
const int pinGas = A0;
const int pinBrake = A1;
const int pinClutch = A2;
const int pinEncReset = 8;

long encPositionOld = 0;
int gasPositionOld = 0;
int brakePositionOld = 0;
int clutchPositionOld = 0;
unsigned long buttonsState = 0;


#include <Encoder.h>
Encoder wheelEnc(pinEncoder1, pinEncoder2);


void setup() {
  Serial.begin(115200);

  for(int i=0; i<numOfButtons; i++)
  {
    pinMode(pinButtons[i], INPUT_PULLUP);
  }
  pinMode(pinEncReset, INPUT_PULLUP);

}



void loop() {
  sendWheelData(encPositionOld);
  sendPedalsData(gasPositionOld, pinGas, 'g');
  sendPedalsData(brakePositionOld, pinBrake, 'b');
  sendPedalsData(clutchPositionOld, pinClutch, 'c');
  sendButtonsData(pinButtons, numOfButtons, buttonsState);
  resetEnc(pinEncReset, wheelEnc);

  delay(10000);
}

void sendWheelData(long & encOldPosition)
{
   long encPositionNew = wheelEnc.read();
   if(encOldPosition != encPositionNew)
   {
      encOldPosition = encPositionNew;
      Serial.print('w');
      Serial.println(encPositionNew);
   }
}



void sendPedalsData(int &positionOld, int pin, char id)
{
  int positionNew = analogRead(pin);
  if(positionOld != positionNew)
    {
        positionOld = positionNew;
        Serial.print(id);
        Serial.println(positionNew);
    }
}

void sendButtonsData(int pinButtons[], int numOfButtons, unsigned long &buttonsState)
{
    unsigned long buttonsStateNew = 0;
    for(int i=0; i<numOfButtons; i++)
    {
        if(digitalRead(pinButtons[i]) == LOW)
        {
            buttonsStateNew += (1<<i);
        }
    }
    if(buttonsState != buttonsStateNew)
    {
      buttonsState = buttonsStateNew;
      Serial.print('a');
      Serial.println(buttonsState);
    }
}

void resetEnc(int resetPin, Encoder & enc)
{
    if(digitalRead(resetPin) == LOW)
    {
        enc.write(0);
    }
}

