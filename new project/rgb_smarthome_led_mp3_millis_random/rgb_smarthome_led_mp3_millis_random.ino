
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

#define RGB_1_RED_PIN     2
#define RGB_1_GREEN_PIN   3
#define RGB_1_BLUE_PIN    6

#define POT_PIN           A8

#define MAX_VOLUME        30
#define MAX_ADC           1024

/*
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
*/

long previousTime  = 0;
long interval      = 300;

int ledRGBRedState = 0;
int ledRGBGreenState = 0;
int ledRGBBlueState = 0;

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

}


void flashRGB()
{
 int ledRGBRedVal   = random(HIGH, LOW);
 int ledRGBGreenVal = random(HIGH, LOW);
 int ledRGBBlueVal  = random(HIGH, LOW);
 
 unsigned long currentTime = millis();

 if(currentTime - previousTime > interval)
 {
   // сохраняем время последнего переключения
   previousTime = currentTime;

   if (ledRGBRedState == LOW)
      ledRGBRedVal = HIGH;
    else
      ledRGBRedVal = LOW;

    if (ledRGBGreenState == LOW)
      ledRGBGreenVal = HIGH;
    else
      ledRGBGreenVal = LOW;

    if (ledRGBBlueState == LOW)
      ledRGBBlueVal = HIGH;
    else
      ledRGBBlueVal = LOW;


   digitalWrite(RGB_1_RED_PIN,   ledRGBRedState);
   digitalWrite(RGB_1_GREEN_PIN, ledRGBGreenState);
   digitalWrite(RGB_1_BLUE_PIN,  ledRGBBlueState);
 }

 ledRGBRedState   = ledRGBRedVal;
 ledRGBGreenState = ledRGBGreenVal;
 ledRGBBlueState  = ledRGBBlueVal;
}



