
/*В этой первоначальной версии была задержка с помощью delay,
 *из-за этого потенциометр переключал звук рывками и для умного дома задержка не годится. 
 *Цикл for в loop также работал некорректно с вычислением задержки используя функцию millis.
 *от него можно избавиться - ведь loop и есть цикл.
*/

#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

#define RGB_1_RED_PIN     2
#define RGB_1_GREEN_PIN   3
#define RGB_1_BLUE_PIN    6



#define POT_PIN           A8

#define MAX_VOLUME        30
#define MAX_ADC           1024

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

int potVal = 0;

void setup() 
{
 pinMode(RGB_1_RED_PIN,   OUTPUT);
 pinMode(RGB_1_GREEN_PIN, OUTPUT);
 pinMode(RGB_1_BLUE_PIN,  OUTPUT);

 pinMode(POT_PIN,         INPUT);

 Serial.begin(9600);
 
 mp3_set_serial (Serial);    //set Serial for DFPlayer-mini mp3 module 
 delay (100);
 mp3_set_volume (15);
 delay (100);
 mp3_play(); // запускаем трек 
}

void loop() 
{
 potVal = analogRead(POT_PIN) / (MAX_ADC / MAX_VOLUME);

 mp3_set_volume(potVal);
  
 for (int i = 0; i!=8; i++)
 { 
  digitalWrite(RGB_1_RED_PIN,   RED_BLINK  [i]);
  digitalWrite(RGB_1_GREEN_PIN, GREEN_BLINK[i]);
  digitalWrite(RGB_1_BLUE_PIN,  BLUE_BLINK [i]);
  
  delay(300); 
 }
}
