#ifndef _GPS_PARSER_H_
#define _GPS_PARSER_H_

#include <Gsdc_SSD1306.h>
#include <NowCommon.h>

class GpsParser
{
private:
  esp_datagram _message;
  Gsdc_SSD1306* _display;
public:
  GpsParser(esp_datagram message, Gsdc_SSD1306 *display) 
  { 
    _message = message; 
    _display = display;
  }
  void parse();
};


#endif