#include <ArduinoJson.h>
#include "GpsParser.h"

void GpsParser::parse()
{
  const size_t capacity = JSON_OBJECT_SIZE(4);
  DynamicJsonDocument doc(capacity);
  
  char lat_buffer[16];
  int buffer_len = sprintf(lat_buffer, "%8f", _message.gps.latitude);
  Serial.printf("Buffer length is %d \n\r\t %s\r\n", buffer_len, lat_buffer);
  char lng_buffer[16];
  buffer_len = sprintf(lng_buffer, "%8f", _message.gps.longitude);
  Serial.printf("Buffer length is %d \n\r\t %s\r\n", buffer_len, lng_buffer);
  char alt_buffer[16];
  buffer_len = sprintf(alt_buffer, "%8.2f", _message.gps.altitude);
  Serial.printf("Buffer length is %d \n\r\t %s\r\n", buffer_len, alt_buffer);

  _display->scrub();
  _display->left(TOP,    (String)"ALT: " + alt_buffer);
  _display->left(MIDDLE, (String)"LAT: " + lat_buffer);
  _display->left(BOTTOM, (String)"LNG: " + lng_buffer);
  _display->wait(500);

  doc["sender"] = _message.header.sender;
  doc["latitude"] = lat_buffer;
  doc["longitude"] = lng_buffer;
  doc["altitude"] = alt_buffer;

  Serial.printf("Sender   : %s\n",   doc["sender"].as<String>().c_str());
  Serial.printf("Latitude : %f\n",   doc["latitude"].as<double>());
  Serial.printf("Longitude: %f\n",   doc["longitude"].as<double>());
  Serial.printf("Altitude : %f m\n", doc["altitude"].as<double>());
  Serial.println();  
}
