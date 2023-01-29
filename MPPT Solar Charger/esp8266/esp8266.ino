#include "degiskenler.h"
#include "wifi.h"
//#include "wifi_multi.h"
#include "mqtt.h"
#include "ota.h"
#include "seri_port.h"
//#include "seri_port_eski.h"




void setup() {
  Serial.begin(74880);
  pinMode(LED_BUILTIN, OUTPUT);
  //sof_serial_setup();
  wifi_setup();
  mqtt_setup();
  ota_setup();
}

 
void loop() {
  
  ota_loop();
  seri_port_loop();
  mqtt_loop();
  
}
