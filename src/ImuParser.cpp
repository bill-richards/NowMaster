#include <ArduinoJson.h>
#include "ImuParser.h"

void ImuParser::parse()
{
  const size_t capacity = JSON_OBJECT_SIZE(4);
  DynamicJsonDocument doc(capacity);
  
  char pitch_buffer[16];
  sprintf(pitch_buffer, "%8f%u", _message.imu.pitch, char(161));

  char roll_buffer[16];
  sprintf(roll_buffer, "%8f%u", _message.imu.roll, char(161));

  _display->scrub();
  _display->left(TOP,    "Position: ");
  _display->left(MIDDLE, (String)"Pitch: " + pitch_buffer);
  _display->left(BOTTOM, (String)"Roll: " + roll_buffer);
  _display->wait(500);

  doc["sender"] = _message.header.sender;
  doc["pitch"] = pitch_buffer;
  doc["roll"] = roll_buffer;

  Serial.printf("Sender : %s\n",   doc["sender"].as<String>().c_str());
  Serial.printf("Pitch  : %f\n",   doc["pitch"].as<float>());
  Serial.printf("Roll   : %f\n",   doc["roll"].as<float>());
  Serial.println();  
}
