#include "NetworkData.h"
#include "WiFIFunctions.h"

unsigned long previousMillis = 0;

void ConnectWiFi_STA(bool useStaticIP)
{
   Serial.println("");
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   if(useStaticIP) WiFi.config(ip, gateway, subnet);
   while (WiFi.status() != WL_CONNECTED) 
   { 
     delay(100);  
     Serial.print('.'); 
   }
 
   Serial.println("");
   Serial.print("Iniciado STA:\t");
   Serial.println(ssid);
   Serial.print("IP address:\t");
   Serial.println(WiFi.localIP());
   
}


void testWifiConnection()
{
  // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  if ((WiFi.status() != WL_CONNECTED) && (millis() - previousMillis >= INTERVAL_LOSS_WIFI)) 
  {
      Serial.print(millis());
      Serial.println("Reconnecting to WiFi...");
      WiFi.disconnect();
      WiFi.reconnect();
      previousMillis = millis();
      digitalWrite(WIFIOK_LED_PIN,LOW); // Sin wifi
  }
  else
    digitalWrite(WIFIOK_LED_PIN,HIGH); //Wifi ok
}
