#define DEBUG
#define CLIMAT2
//E_MODULE
#define BLUETOOTH_MODULE

boolean debug = true;

#include <QuadDisplay.h>
#include <TroykaDHT11.h>
//#include <QuadDisplay2.h>
#include <QueueList.h>

//QuadDisplay qd(43);

/*
  #define PIN_DISPLAY             33
  #define PIN_BT_LED_1            44
  #define PIN_BT_LED_2            46
  #define PIN_FOTO_R_LASER        A7         //фоторезистор
  #define PIN_FOTO_R              A8
  #define PIN_DOOR_LED            51         //инициализируем пин для светодиода
  #define PIN_PIR                 53         //инициализируем пин для получения сигнала от пироэлектрического датчика движения
  #define PIN_BUZZER              47         //пьезодинамик (пищалка)
  #define PIN_LASER               5          //лазер от охранной сигнализации
  #define PIN_COOLER              43         //кондиционер
  #define PIN_GERKON              41         //Геркон
  #define PIN_DHT                 3          //датчик DHT11
  #define PIN_BUTTON_RED          45
  #define PIN_BUTTON_LED_RED      49
*/

#define PIN_DISPLAY             43
#define PIN_BT_LED_1            52
#define PIN_BT_LED_2            42
#define PIN_FOTO_R_LASER        A15          //фоторезистор
#define PIN_FOTO_R              A0
#define POT_PIN                 A0
#define PIN_DOOR_LED            48          //инициализируем пин для светодиода
#define PIN_PIR                 46          //инициализируем пин для получения сигнала от пироэлектрического датчика движения
#define PIN_BUZZER              10          //пьезодинамик (пищалка)
#define PIN_LASER               41          //лазер от охранной сигнализации
#define PIN_COOLER              40          //кондиционер
#define PIN_GERKON              50          //Геркон
#define PIN_DHT                 45          //датчик DHT11
#define PIN_BUTTON_RED          8
#define PIN_BUTTON_LED_RED      9
#define PIN_RGB_RED             5
#define PIN_RGB_GREEN           6
#define PIN_RGB_BLUE            7
#define PIN_WARM_FLOOR          39
#define MOTOR_DISCO             38

//----------------------------------НАСТРОЙКА BLUETOOTH_MODULE---------------------


#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include "bluetooth.h"

// RemoteXY connection settings
#define REMOTEXY_SERIAL_RX 11
#define REMOTEXY_SERIAL_TX 12
#define REMOTEXY_SERIAL_SPEED 9600
#define REMOTEXY_ACCESS_PASSWORD "7887"

// конфигурация интерфейса
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
{ 255, 5, 0, 2, 0, 185, 1, 6, 0, 4,
  2, 0, 3, 16, 32, 16, 2, 1, 208, 146,
  208, 186, 208, 187, 46, 0, 208, 146, 209, 139,
  208, 186, 208, 187, 46, 0, 2, 0, 3, 43,
  32, 16, 2, 1, 208, 146, 208, 186, 208, 187,
  46, 0, 208, 146, 209, 139, 208, 186, 208, 187,
  46, 0, 2, 0, 58, 19, 34, 11, 2, 1,
  208, 146, 208, 186, 208, 187, 46, 0, 208, 146,
  209, 139, 208, 186, 208, 187, 46, 0, 2, 0,
  46, 14, 46, 15, 2, 2, 208, 146, 208, 186,
  208, 187, 46, 0, 208, 146, 209, 139, 208, 186,
  208, 187, 46, 0, 2, 0, 4, 38, 31, 20,
  2, 2, 208, 146, 208, 186, 208, 187, 46, 0,
  208, 146, 209, 139, 208, 186, 208, 187, 46, 0,
  65, 6, 42, 10, 11, 11, 2, 1, 130, 1,
  40, 8, 58, 25, 6, 1, 129, 0, 2, 1,
  14, 6, 11, 1, 208, 161, 208, 178, 208, 181,
  209, 130, 0, 130, 1, 2, 8, 34, 25, 8,
  1, 130, 1, 2, 35, 34, 25, 8, 1, 129,
  0, 3, 8, 18, 6, 6, 1, 208, 154, 208,
  190, 208, 188, 208, 189, 208, 176, 209, 130, 208,
  176, 32, 49, 0, 129, 0, 3, 36, 30, 6,
  6, 1, 208, 154, 208, 190, 208, 188, 208, 189,
  208, 176, 209, 130, 208, 176, 32, 50, 0, 130,
  1, 40, 3, 58, 29, 9, 2, 129, 0, 41,
  1, 22, 6, 11, 1, 208, 151, 208, 176, 209,
  137, 208, 184, 209, 130, 208, 176, 0, 129, 0,
  55, 9, 42, 6, 8, 1, 208, 161, 208, 184,
  208, 179, 208, 189, 208, 176, 208, 187, 208, 184,
  208, 183, 208, 176, 209, 134, 208, 184, 209, 143,
  0, 129, 0, 43, 4, 51, 6, 6, 2, 209,
  128, 208, 181, 208, 182, 208, 184, 208, 188, 32,
  208, 180, 208, 184, 209, 129, 208, 186, 208, 190,
  209, 130, 208, 181, 208, 186, 208, 176, 0, 131,
  1, 44, 52, 24, 7, 2, 1, 208, 190, 209,
  129, 208, 189, 46, 0, 131, 0, 71, 52, 24,
  7, 2, 2, 208, 180, 208, 190, 208, 191, 46,
  0, 130, 1, 40, 35, 58, 25, 13, 0, 129,
  0, 51, 36, 34, 7, 9, 0, 209, 129, 209,
  130, 209, 128, 208, 176, 208, 189, 208, 184, 209,
  134, 209, 139, 0, 130, 1, 3, 3, 33, 57,
  11, 2, 129, 0, 5, 5, 30, 8, 6, 2,
  209, 130, 208, 181, 208, 191, 208, 187, 209, 139,
  208, 185, 0, 129, 0, 12, 14, 15, 8, 6,
  2, 208, 191, 208, 190, 208, 187, 0
};


// структура определяет все переменные вашего интерфейса управления
struct {

  // input variable
  uint8_t switch_2; // =1 если переключатель включен и =0 если отключен
  uint8_t switch_3; // =1 если переключатель включен и =0 если отключен
  uint8_t switch_1; // =1 если переключатель включен и =0 если отключен
  uint8_t switch_4; // =1 если переключатель включен и =0 если отключен
  uint8_t switch_5; // =1 если переключатель включен и =0 если отключен

  // output variable
  uint8_t led_1_r; // =0..255 яркость красного цвета индикатора
  uint8_t led_1_g; // =0..255 яркость зеленого цвета индикатора

  // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

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
unsigned long startTime    = 0;
int           delayPeriod  = 1000;
int           countTime    = 0;

//-----------------------------------RGB МАССИВЫ-----------------------------------------------

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
  pinMode(PIN_WARM_FLOOR,         OUTPUT);
  pinMode(MOTOR_DISCO,            OUTPUT);
  pinMode(PIN_RGB_RED,            OUTPUT);
  pinMode(PIN_RGB_GREEN,          OUTPUT);
  pinMode(PIN_RGB_BLUE,           OUTPUT);

  dht.begin();
  //qd.begin();
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
  static int COOLER_OFF_BARRIER = getTemperature();

  //  #ifdef BLUETOOTH_MODULE
  RemoteXY_Handler();                                    //читаем состояние смартфона
  //   #endif
  //-------------------------------АНАЛИЗ ПОКАЗАНИЙ СЕНСОРОВ-------------------------------------


  if (tempVal != tempState) {
    onStateChanged(tempState, tempVal, "Temp changed: " + String(tempVal));

    displayTemperatureC(PIN_DISPLAY, tempVal);

    if (tempVal >= COOLER_ON_BARRIER)   coolVal = STATE_COOLER_ON;
    if (tempVal <= COOLER_OFF_BARRIER)  coolVal = STATE_COOLER_OFF;

    tempState = tempVal;
  }
  
    /*
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

    /* if (buttonRedVal == LOW || RemoteXY.button_1==1)
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
    }*/

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
  if (fotoRLaserVal > FOTO_R_LASER_BARRIER && RemoteXY.switch_1 == 1)  //если показания с фоторезистора ниже 900 и кнопка на телефоне нажата то...
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

  if (RemoteXY.switch_1 == 0)
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

    coolState = coolVal;
  }

  /*   if (coolVal != coolState) {
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
     Serial.println(fotoRLaserVal);

  */
  //-----------------------------------ДЕМОНСТРАЦИЯ ЧТЕНИЯ С ТЕЛЕФОНА-------------------------------------------------

#ifdef BLUETOOTH_MODULE

  digitalWrite(PIN_LASER,      RemoteXY.switch_1 == 0 ? LOW : HIGH);
  digitalWrite(PIN_WARM_FLOOR, RemoteXY.switch_5 == 0 ? LOW : HIGH);
  digitalWrite(PIN_BT_LED_1,   RemoteXY.switch_2 == 0 ? LOW : HIGH);
  digitalWrite(PIN_BT_LED_2,   RemoteXY.switch_3 == 0 ? LOW : HIGH);




  if (RemoteXY.switch_4 == 1)
  {
    analogWrite(MOTOR_DISCO, 150);
    flashRGB();
  }
  else
  {
    analogWrite(MOTOR_DISCO, 0);
    not_flashRGB();
  }





#endif
}

void flashRGB()
{
  unsigned long currentTime = millis();

  if (currentTime - startTime > delayPeriod)
  {
    startTime = currentTime;

    digitalWrite(PIN_RGB_RED,   RED_BLINK  [countTime]);
    digitalWrite(PIN_RGB_GREEN, GREEN_BLINK[countTime]);
    digitalWrite(PIN_RGB_BLUE,  BLUE_BLINK [countTime]);
  }
  countTime++;

  if (countTime >= 7) countTime = 0;
}


void not_flashRGB()
{
  digitalWrite(PIN_RGB_RED,   HIGH);
  digitalWrite(PIN_RGB_GREEN, HIGH);
  digitalWrite(PIN_RGB_BLUE,  HIGH);
}



