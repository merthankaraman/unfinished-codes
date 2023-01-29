#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;

void wifi_setup(){
  wifiMulti.addAP("KARAMAN_2.4GHz_plus", "K4R4M4N_61");
  wifiMulti.addAP("KARAMAN_2.4GHz", "K4R4M4N_61");
  //wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

  Serial.println("Connecting Wifi...");
  if (wifiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}
