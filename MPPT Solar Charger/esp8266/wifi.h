#include <ESP8266WiFi.h>

void wifi_setup(){
  delay(10);
  /*Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);*/

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  randomSeed(micros());

  /*Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());*/
}
