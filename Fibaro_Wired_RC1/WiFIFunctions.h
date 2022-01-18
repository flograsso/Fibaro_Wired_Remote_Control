#ifndef WIFIFUNCTIONS_H
#define WIFIFUNCTIONS_H


#define INTERVAL_LOSS_WIFI    30000
#define WIFIOK_LED_PIN        26



void ConnectWiFi_STA(bool useStaticIP = false);
void testWifiConnection();

#endif