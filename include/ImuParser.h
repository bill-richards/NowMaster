#ifndef _IMU_PARSER_H_
#define _IMU_PARSER_H_

#include <Gsdc_SSD1306.h>
#include <NowCommon.h>

class ImuParser
{
private:
  esp_datagram _message;
  Gsdc_SSD1306* _display;
public:
  ImuParser(esp_datagram message, Gsdc_SSD1306 *display) 
  { 
    _message = message; 
    _display = display;
  }
  void parse();
};

#endif