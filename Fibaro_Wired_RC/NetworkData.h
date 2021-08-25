
#ifndef NETWORK_DATA_H
#define NETWORK_DATA_H

#include <WiFi.h>

const char* ssid     = "Cazuela_2.4";
const char* password = "c@fec0n1eche";
const char* hostname = "ESP32_Fibaro1";

IPAddress ip(192, 168, 0, 200);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);


#endif