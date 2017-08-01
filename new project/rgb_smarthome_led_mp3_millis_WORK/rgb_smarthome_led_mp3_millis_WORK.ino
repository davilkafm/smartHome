
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

#define RGB_1_RED_PIN     22
#define RGB_1_GREEN_PIN   24
#define RGB_1_BLUE_PIN    26

#define POT_PIN           A0

#define MAX_VOLUME        30
#define MAX_ADC           1024


int RED_BLINK  [] =
{
  LOW, HIGH, HIGH, LOW, HIGH, LOW
};
int GREEN_BLINK[] =
{
  HIGH, LOW, HIGH, LOW, LOW, HIGH
};

int BLUE_BLINK [] =
{
  HIGH, HIGH, LOW, HIGH, LOW, LOW
};


long startTime     = 0;
int  delayPeriod   = 1000;
int  countTime     = 0;

void setup() 
{
 pinMode(RGB_1_RED_PIN,   OUTPUT);
 pinMode(RGB_1_GREEN_PIN, OUTPUT);
 pinMode(RGB_1_BLUE_PIN,  OUTPUT);

 pinMode(POT_PIN,         INPUT);

 Serial.begin(9600);
 
 mp3_set_serial (Serial);    //set Serial for DFPlayer-mini mp3 module 
 mp3_set_volume (15);
 mp3_play(); // запускаем трек 
}

void loop() 
{
 int potVal = 0; 

 potVal = analogRead(POT_PIN) / (MAX_ADC / MAX_VOLUME);

 mp3_set_volume(potVal);


 flashRGB();

 /*
 unsigned long currentTime = millis();

 if (currentTime - startTime > delayPeriod)
 {
  startTime = currentTime;

  digitalWrite(RGB_1_RED_PIN,   RED_BLINK  [countTime]);
  digitalWrite(RGB_1_GREEN_PIN, GREEN_BLINK[countTime]);
  digitalWrite(RGB_1_BLUE_PIN,  BLUE_BLINK [countTime]);
 }
 countTime++;

 if (countTime>=7) countTime = 0;
 */
}





void flashRGB()
{
 unsigned long currentTime = millis();

 if (currentTime - startTime > delayPeriod)
 {
  startTime = currentTime;

  digitalWrite(RGB_1_RED_PIN,   RED_BLINK  [countTime]);
  digitalWrite(RGB_1_GREEN_PIN, GREEN_BLINK[countTime]);
  digitalWrite(RGB_1_BLUE_PIN,  BLUE_BLINK [countTime]);
 }
 countTime++; 

 if (countTime>=7) countTime = 0;
}





  
