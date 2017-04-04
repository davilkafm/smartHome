#define DEBUG
#define CLIMATE_MODULE
#define BLUETOOTH_MODULE

boolean debug = true;

#include <QuadDisplay.h>
#include <TroykaDHT11.h>
#include <QueueList.h>

#define PIN_DISPLAY             53
#define PIN_BT_LED_1            6       
#define PIN_BT_LED_2            7  
#define PIN_FOTO_R_LASER        A7         //фоторезистор
#define PIN_FOTO_R              A14
#define PIN_DOOR_LED            4          //инициализируем пин для светодиода
#define PIN_PIR                 51         //инициализируем пин для получения сигнала от пироэлектрического датчика движения
#define PIN_BUZZER              41         //пьезодинамик (пищалка)
#define PIN_LASER               9         //лазер от охранной сигнализации
#define PIN_COOLER              47         //кондиционер
#define PIN_GERKON              43         //Геркон
#define PIN_DHT                 5          //датчик DHT11
#define PIN_BUTTON_RED          49
#define PIN_BUTTON_LED_RED      45


//----------------------------------НАСТРОЙКА BLUETOOTH_MODULE---------------------  

#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h> 
#include "bluetooth.h"


 
#define REMOTEXY_SERIAL_RX 11
#define REMOTEXY_SERIAL_TX 12
#define REMOTEXY_SERIAL_SPEED 9600

   
#pragma pack(push, 1) 
uint8_t RemoteXY_CONF[] = 
  { 4,4,229,0,6,0,0,2,0,58
  ,9,40,16,2,79,78,0,79,70,70
  ,0,2,0,3,16,32,16,2,79,78
  ,0,79,70,70,0,2,0,3,43,32
  ,16,2,79,78,0,79,70,70,0,1
  ,0,86,36,12,12,1,208,161,208,177
  ,209,128,208,190,209,129,0,65,6,45
  ,6,12,12,2,65,6,47,32,12,12
  ,2,129,0,56,2,42,6,1,208,161
  ,208,184,208,179,208,189,208,176,208,187
  ,208,184,208,183,208,176,209,134,208,184
  ,209,143,0,130,1,43,2,57,24,6
  ,129,0,2,1,14,6,11,208,161,208
  ,178,208,181,209,130,0,130,1,2,8
  ,34,25,8,130,1,2,35,34,25,8
  ,129,0,3,8,18,6,6,208,154,208
  ,190,208,188,208,189,208,176,209,130,208
  ,176,32,49,0,129,0,3,36,30,6
  ,6,208,154,208,190,208,188,208,189,208
  ,176,209,130,208,176,32,50,0,130,1
  ,43,28,56,21,9,129,0,64,29,33
  ,6,0,208,159,208,181,209,128,208,181
  ,208,179,209,128,209,131,208,183,208,186
  ,208,176,0 }; 

 struct { 

  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  uint8_t switch_2; // =1 if switch ON and =0 if OFF 
  uint8_t switch_3; // =1 if switch ON and =0 if OFF 

  uint8_t button_1;

  uint8_t led_1_r; // =0..255 LED Red brightness 
  uint8_t led_1_g; // =0..255 LED Green brightness 

  uint8_t led_2_r; // =0..255 LED Red brightness 
  uint8_t led_2_g; // =0..255 LED Green brightness 
    
    // other variable
  uint8_t connect_flag;  

} RemoteXY; 
#pragma pack(pop) 

//----------------подключение доп-файлов----------------

#include "functions.h"
#include "climate.h"
#include "display.h"

//-----------------состояние сенсоров-------------------
int pirState              = LOW;            // начинаем работу программы, предполагая, что движения нет
int tempState             = 0;              // состояние температуры (предыдущее значение)
int gerkonState           = LOW;            // состояние геркона


//-----------состояние устройств(исполнители)-----------
int doorLedState          = LOW;            //состояние светодиода над дверью
int signalState           = 0;
int coolerState           = HIGH;
int buttonRedLedState     = LOW;
int buttonBlueOneLedState = LOW;
int buttonBlueTwoLedState = LOW;


int PEREGRUZKA            = LOW;

unsigned long coolerTime;


//-----------------------------------НАСТРОЙКА ВСЕГО-------------------------------------------
void setup()
{
    pinMode(PIN_FOTO_R_LASER,       INPUT);
    pinMode(PIN_FOTO_R,             INPUT);
    pinMode(PIN_PIR,                INPUT);
    pinMode(PIN_GERKON,             INPUT);
    pinMode(PIN_BUTTON_RED,         INPUT);
   
    
    pinMode(PIN_DOOR_LED,           OUTPUT);
    pinMode(PIN_BUZZER,             OUTPUT);
    pinMode(PIN_COOLER,             OUTPUT);
    pinMode(PIN_LASER,              OUTPUT);
    pinMode(PIN_BT_LED_1,           OUTPUT);
    pinMode(PIN_BT_LED_2,           OUTPUT);
    pinMode(PIN_LASER,              OUTPUT);
    pinMode(PIN_BUTTON_LED_RED,     OUTPUT);
   

    dht.begin();
    Serial.begin(9600);

    #ifdef BLUETOOTH_MODULE
    RemoteXY_Init();
    #endif


}

//------------------------------------ГЛАВНЫЙ ЦИКЛ ПРОГРАММЫ--------------------------------------
void loop()
{
    int   fotoRLaserVal     = 0;
    int   pirVal            = 0;                                //переменная для чтения состояния пина  
    int   tempStatus        = 0;                                //статус чтения информации с датчика температуры (ошибка или нет)
    int   tempVal           = 0;
    int   fotoRVal          = 0;
    int   gerkonVal         = HIGH;                             //Геркон
    int   buttonRedVal      = HIGH;
   
    
    float currentVal;
    
    static  byte coolState   =  LOW;                       //состояние кондиционера 
    static  byte coolVal     =  coolState;                 //Предлагаемое состояние кондиционера равно текущему состоянию 
    static  int  doorLedVal  =  doorLedState;              //Предлагаемое состояние светодиода выключено
   
    //---------------------------------ЧТЕНИЕ ПОКАЗАНИЙ СЕНСОРОВ-------------------------------------
    tempVal          = getTemperature(); 
    fotoRLaserVal    = analogRead (PIN_FOTO_R_LASER);         //прочитать показания сигнализации
    fotoRVal         = analogRead (PIN_FOTO_R);
    pirVal           = digitalRead(PIN_PIR);                  //считываем значение с датчика
    gerkonVal        = digitalRead(PIN_GERKON);               //прочитать состояние двери
    buttonRedVal     = digitalRead(PIN_BUTTON_RED);

    currentVal = sensorCurrent.readCurrentDC();
  
    static int COOLER_ON_BARRIER  = getTemperature() + 1;
    static int COOLER_OFF_BARRIER = getTemperature() - 1; 
    
    #ifdef BLUETOOTH_MODULE
    RemoteXY_Handler();                                    //читаем состояние смартфона
    #endif   
    //-------------------------------АНАЛИЗ ПОКАЗАНИЙ СЕНСОРОВ-------------------------------------

    if (tempVal != tempState) {
          onStateChanged(tempState, tempVal, "Temp changed: " + String(tempVal));
          
          displayTemperatureC(PIN_DISPLAY, tempVal);

          tempState = tempVal;
    }

 if (PEREGRUZKA == LOW)
 {
  coolerState = HIGH;

  buttonRedLedState = LOW;
 }
 else
 {
  coolerState = LOW;

  buttonRedLedState = HIGH;
 }

 if (PEREGRUZKA == LOW && currentVal >= MAX_CURRENT)
 {
  coolerTime = millis();

  if (coolerTime >= 2000)
  {
   if (currentVal >= MAX_CURRENT)
   {
     PEREGRUZKA = HIGH;
   }
   else
   {
    PEREGRUZKA = LOW;
   }
  }
 }

 if (buttonRedVal == LOW || RemoteXY.button_1==1)
 {
  if (PEREGRUZKA == HIGH)
  {
    PEREGRUZKA = LOW;
    RemoteXY.led_2_r = 0;
    RemoteXY.led_2_g = 255;
  }
 }
 else
 {
  if (PEREGRUZKA == HIGH)
  {
    RemoteXY.led_2_r = 255;
    RemoteXY.led_2_g = 0;
  }
 }
       
    if (fotoRVal >= FOTO_R_BARRIER)
    {
         if (pirVal != pirState) {
              onStateChanged(pirState, pirVal, "PIR changed: " + String(pirState) +
                                        " -> " + String(pirVal));

              if (HIGH == pirVal)           doorLedVal = HIGH;
              else   if (HIGH == gerkonVal) doorLedVal = LOW;
             
         
              pirState  = pirVal; 
         }

         if (gerkonVal != gerkonState) {
             onStateChanged(gerkonState, gerkonVal, "Door state changed: " + String(gerkonState) + 
                                         " -> " + String(gerkonVal));    
             
               if (LOW == gerkonVal)      doorLedVal = HIGH;
               else  if (LOW == pirVal)   doorLedVal = LOW;
             
          
               gerkonState = gerkonVal;
         }
    }
    else
    {
         doorLedVal = LOW;
    }

      
  
    #ifdef BLUETOOTH_MODULE    
    if (fotoRLaserVal > FOTO_R_LASER_BARRIER && RemoteXY.switch_1==1)    //если показания с фоторезистора ниже 900 и кнопка на телефоне нажата то...
    {       
      tone(PIN_BUZZER, map(fotoRLaserVal, 0, 1023, 2500, 4500), TIME_BUZZER);

       RemoteXY.led_1_r = 255;
       RemoteXY.led_1_g = 0;
    }
    else
    {   
      noTone(PIN_BUZZER);

       RemoteXY.led_1_r = 0;
       RemoteXY.led_1_g = 255;
    }

    if (RemoteXY.switch_1==0)
    {
      RemoteXY.led_1_r = 0;
      RemoteXY.led_1_g = 0;
    }
    #endif

//-------------------------------------ИЗМЕНЕНИЕ СОСТОЯНИЙ ИСПОЛНИТЕЛЬНЫХ УСТРОЙСТВ-------------------------------
    if (doorLedVal != doorLedState) {
        onStateChanged(doorLedState, doorLedVal, "#Led state changed: " + String(doorLedState) + 
                                                          " -> " + String(doorLedVal));
    
        doorLedState = doorLedVal;
        digitalWrite(PIN_DOOR_LED, doorLedState);
    }

    if (coolVal != coolState) {
         onStateChanged(coolState, coolVal, "#Cooler state changed: " + String(coolState) + 
                                                          " -> " + String(coolVal));
         
         if (STATE_COOLER_ON == coolVal) analogWrite(PIN_COOLER, STATE_COOLER_ON);  else analogWrite(PIN_COOLER, STATE_COOLER_OFF);         
         
         coolState=coolVal;
    } 

    if (PEREGRUZKA == LOW)
 {
  coolerState = HIGH;

  buttonRedLedState = LOW;
 }
 else
 {
  coolerState = LOW;

  buttonRedLedState = HIGH;
 }

 if (PEREGRUZKA == LOW && currentVal >= MAX_CURRENT)
 {
  coolerTime = millis();

  if (coolerTime >= 2000)
  {
   if (currentVal >= MAX_CURRENT)
   {
     PEREGRUZKA = HIGH;
   }
   else
   {
    PEREGRUZKA = LOW;
   }
  }
 }

 if (buttonRedVal == LOW && PEREGRUZKA == HIGH)
 {
  PEREGRUZKA = LOW;
 }
    digitalWrite(PIN_COOLER,             coolerState);
    digitalWrite(PIN_BUTTON_LED_RED,     buttonRedLedState);

    //Serial.print  (currentVal);
    //Serial.println(" mA");

    //-----------------------------------ДЕМОНСТРАЦИЯ ЧТЕНИЯ С ТЕЛЕФОНА-------------------------------------------------     
    
#ifdef BLUETOOTH_MODULE

   digitalWrite(PIN_LASER,    RemoteXY.switch_1==0?LOW:HIGH);
    
    digitalWrite(PIN_BT_LED_1, RemoteXY.switch_2==0?LOW:HIGH);
    digitalWrite(PIN_BT_LED_2, RemoteXY.switch_3==0?LOW:HIGH);

#endif
}     



             
