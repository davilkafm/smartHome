//#include <Timer.h>

#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>


#define RGB_1_RED_PIN     2
#define RGB_1_GREEN_PIN   3
#define RGB_1_BLUE_PIN    6

#define DIR_1             4
#define SPEED_1           5 

#define POT_PIN           A8

#define MAX_VOLUME        30
#define MAX_ADC           1024

#define DELAY_PERIOD      300

//const int period  = 1000;

int RED_BLINK  [] =
{
  LOW, HIGH, HIGH, LOW, HIGH, LOW, LOW
};

int GREEN_BLINK[] =
{
  HIGH, LOW, HIGH, LOW, LOW, HIGH, LOW
};

int BLUE_BLINK [] =
{
  HIGH, HIGH, LOW, HIGH, LOW, LOW, LOW
};

int flashRGB(int);
int potVal = 0;

//Timer t; 

void setup() 
{
 pinMode(RGB_1_RED_PIN,   OUTPUT);
 pinMode(RGB_1_GREEN_PIN, OUTPUT);
 pinMode(RGB_1_BLUE_PIN,  OUTPUT);

 pinMode(DIR_1,           OUTPUT);
 pinMode(SPEED_1,         OUTPUT);

 pinMode(POT_PIN,         INPUT);

 Serial.begin(9600);

// t.every(period, flashRGB);
 
 mp3_set_serial (Serial);    //set Serial for DFPlayer-mini mp3 module 
 delay (100);
 mp3_set_volume (15);
 delay (100);
 mp3_play(); // запускаем трек 

 digitalWrite(DIR_1, HIGH);
 digitalWrite(SPEED_1, 1);
}

void loop() 
{
 potVal = analogRead(POT_PIN) / (MAX_ADC / MAX_VOLUME);

 mp3_set_volume(potVal);

 int i = 0;
  
 while (i < 8) //попробовать while
 { 
  int flashRGB(i);

  i++;
 }
}



int flashRGB(int i)
{
  digitalWrite(RGB_1_RED_PIN,   RED_BLINK  [i]);
  digitalWrite(RGB_1_GREEN_PIN, GREEN_BLINK[i]);
  digitalWrite(RGB_1_BLUE_PIN,  BLUE_BLINK [i]);

  delay(DELAY_PERIOD);
  
  //t.update();

  return 0;
 }


