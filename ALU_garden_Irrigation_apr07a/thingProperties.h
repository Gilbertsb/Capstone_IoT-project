// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "4752104a-e06b-46b8-be09-182266f530bb";

const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = SECRET_DEVICE_KEY;    // Secret device password

void onOffOnChange();

float water;
CloudLight off_on;
int moisture_Sensor_1;
int moisture_Sensor_2;
bool status;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(water, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(off_on, READWRITE, ON_CHANGE, onOffOnChange);
  ArduinoCloud.addProperty(moisture_Sensor_1, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(moisture_Sensor_2, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(status, READ, ON_CHANGE, NULL);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);