#include <ESPAsyncWebServer.h>

#include "GpsParser.h"
#include "ImuParser.h"

char BOARD_ID[32] = "GSDC_NOW Master";

esp_datagram _incomingMessage;
inter_gram _outgoingMessage;
String _remoteServerMacAddress;
Gsdc_SSD1306 _display(0x3C, SDA, SCL);

static unsigned long _previousMillis = 0;
static const unsigned long EVENT_INTERVAL_MS = 2000;

DEFAULT_NVM()
// CREATE_WEB_SERVER_AND_REGISTER_EVENT_SOURCE(80, "/events")

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  String message = status == ESP_NOW_SEND_SUCCESS ? "Success" : "Failure";
  _display.leftHeading("Send status");
  _display.flashCenter(line_positions::MIDDLE, message);
  _display.wait(500);
  _display.scrub();
}

void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) 
{ 
  _display.scrub();
  memcpy(&_incomingMessage, incomingData, sizeof(_incomingMessage));
  _display.centerHeading("Packet received");
  _display.center(MIDDLE, "from");
  _display.center(BOTTOM, _incomingMessage.header.sender);
  _display.wait(500);

  switch(_incomingMessage.header.transmitted_data)
  {
    case NowTransmittedDataTypes::NONE:
      break;
    case NowTransmittedDataTypes::GPS:
    {
      GpsParser gps(_incomingMessage, &_display);
      gps.parse();
    }
      break;
    case NowTransmittedDataTypes::IMU:
    {
      ImuParser imu(_incomingMessage, &_display);
      imu.parse();
    }
      break;
  }
}

void setup(){
  Serial.begin(250000);
  Wire.begin();
  _display.begin();

  READ_CREDENTIALS_FROM_EEPROM_AND_CONNECT_TO_WIFI_AS_ACCESSPOINT_AND_REMOTE_STATION()
  CALL_AND_WAIT_500_MILLIS(_display.leftHeading("INITIALIZE"))
  CALL_AND_WAIT_500_MILLIS(_display.left(MIDDLE, "File system"))
  INITIALIZE_THE_LOCAL_FILE_SYSTEM()  
  _display.clearLine(MIDDLE);
  CALL_AND_WAIT_500_MILLIS(_display.left(MIDDLE, "ESP Now"))
  INITIALIZE_ESP_NOW_AND_REGISTER_RECEIVED_HANDLER(OnDataRecv)
  REGISTER_SEND_HANDLER(OnDataSent)
  REGISTER_ESP_NOW_PEER(remote_broadcastAddress)
  CALL_AND_WAIT_500_MILLIS(_display.important("Setup Complete"))
  _display.scrub();

  
  //REGISTER_ROUTE("/", HTTP_GET, "/index.html", String())
  //REGISTER_ROUTE("/style.css", HTTP_GET, "/style.css", "text/css")
  
  //events.onConnect([](AsyncEventSourceClient *client){
  //  if(client->lastId()){
  //    Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
  //  }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
  //  client->send("hello!", NULL, millis(), 10000);
  //});

  //server.addHandler(&events);
  //server.begin();
}

void loop(){
  //if ((millis() - lastEventTime) > EVENT_INTERVAL_MS) {
  //  events.send("ping",NULL,millis());
  //  lastEventTime = millis();
  //}

  unsigned long currentMillis = millis();
  if (currentMillis - _previousMillis < EVENT_INTERVAL_MS) return;

  _previousMillis = currentMillis;    
  //_outgoingMessage.sender = BOARD_ID;
  //SEND_MESSAGE_USING_ESP_NOW(remote_broadcastAddress, _outgoingMessage)
}

