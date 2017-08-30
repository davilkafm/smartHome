#ifndef PIN_DHT
#define PIN_DHT    3                       //датчик DHT11
#endif

extern  DHT11 dht(PIN_DHT);

inline int getTemperature () {
    int tempStatus     = dht.read();
    //if (0 != tempStatus) logMessage ("Error with DHT11!!"); else logMessage("DHT WORKEs NOW!!");
    return dht.getTemperatureC();
}

//читает показания датчика DHT11 и возвращает через параметры-ссылки значения температуры и влажности.
inline uint8_t doTempHumMeasure(uint8_t &temp, uint8_t &hum)
{
  static uint8_t  errorCounter = 0;           //счетчик ошибок. При доститижении порога DHT_SENSOR_ERROR_BARRIER обнулить показания температуры и влажности
  uint8_t retcode = dht.read();               //обращаемся к датчику за новыми показаниями - данные сохраняются в библиотеке

  switch (retcode) {
      case DHT_OK:         
            errorCounter = 0;                 //раз все ок, то сбрасываем счетчик ошибок
            temp  = dht.getTemperatureC();    //забираем из библиотеки значение температуры в градусах - выталкиваем в параметр по ссылке
            hum   = dht.getHumidity();        //забираем из библиотеки значение влажности в процентах  - выталкиваем в параметр по ссылке
            
            //TODO: Проверить диапазон возвращаемых значений и установить STATE_DHT11_ERROR_UNBOUND если вышли за границы и верить нельзя
            return STATE_DHT_KNOWN;           //раз успешно прочитали показания - нужно вернуть исправное состояние                 
            
      case DHT_ERROR_CHECKSUM: 
      case DHT_ERROR_TIMEOUT:
      default:
                retcode = STATE_DHT_ERROR;
  }
      if (++errorCounter >= DHT_SENSOR_ERROR_BARRIER) 
                                          temp = hum = 0; 
  return retcode;  
}





