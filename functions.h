#include <TroykaCurrent.h>

//определение настроек - порогов срабатывания
#define DHT_SENSOR_ERROR_BARRIER  5     //количество циклов подряд, в которых не получилось принять показания датчика DHT - по истечении - сброс показаний температуры и влажности
#define TIME_BUZZER               80  //время на которое включается буззер сигнализации
#define FOTO_R_LASER_BARRIER      100 //порог фотосенсора при котором срабатывает сигнализация
#define FOTO_R_BARRIER            300
#define MAX_CURRENT               0.45

//определение состояний
#define STATE_DHT_DEFAULT         0       //начальное состояние (нет измерения)
#define STATE_DHT_KNOWN           1       //измерение произведено
#define STATE_DHT_ERROR           100     //ошибка датчика. Библиотека вернула ошибку - нет связи с датчиком. 
#define STATE_DHT_ERROR_UNBOUND   110     //ошибка датчика. Связь есть но выход за пределы диапазона измерений. 

#define STATE_COOLER_OFF          0       //вентилятор выключен. 
#define STATE_COOLER_ON           255     //вентилятор включен.

ACS712 sensorCurrent(A15);

//===================================================== Секция описания типов ===============================================================
enum QDState {                            //перечень состояний QuadDisplay
    STATE_QUAD_DISPLAY_OFF,               //начальное состояние - дисплей выключен
    STATE_QUAD_DISPLAY_CONTINUE,          //значение по умолчанию - продолжить показ в соответствии с алгоритмом - смена через QUAD_DISPLAY_CYCLE_DELAY
    STATE_QUAD_DISPLAY_ANIM1,             //дисплей в состоянии показа анимации 1...
    STATE_QUAD_DISPLAY_ANIM2,             //дисплей в состоянии показа анимации 2...
    STATE_QUAD_DISPLAY_CLEAR,             //дисплей в состоянии очищен
    STATE_QUAD_DISPLAY_TEMP =  10,        //дисплей в состоянии показа температуры
    STATE_QUAD_DISPLAY_HUM,               //дисплей в состоянии показа влажности
    STATE_QUAD_DISPLAY_MESSAGE            //дисплей в состоянии показа сообщения из переменной qdMessage
};

//=====================Секция глобальных переменных(постоянных - выживают между вызовами цикла loop и доступны во всех функциях)=============
 
struct QDListNode                         //структура для хранения в очереди сообщений
  {
    //обход косяка с типом QDState: http://forum.arduino.cc/index.php?topic=42032.0  Описание enum-а в файле Types.h в том же каталоге
    QDState   state;                      //состояние дисплея.  
    uint16_t  period;                     //время выдержки состояния
    String    message;                    //содержимое в виде строки если предусмотрено типом состояния
  };
  
//------------------------ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ - ПРОТОТИПЫ (сигнатуры = объявления)-----------------------
void onStateChanged (int state, int val);
int getTemperature () ;
void logMessage(String message);
inline uint8_t doTempHumMeasure(uint8_t &temp, uint8_t &hum);

//-----------------------------ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ - РЕАЛИЗАЦИЯ(само тело)-------------------------------
void onStateChanged (int state, int val, String message) {
    logMessage(message);
}




