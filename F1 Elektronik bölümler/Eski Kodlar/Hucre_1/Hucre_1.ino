#include "analoglar_v2.h"
#include "wire_kodlar.h"

int wire_konum = 8;

void setup(){
  digitalWrite(reset_pin,HIGH);
  delay(200);
  pinMode(reset_pin,OUTPUT);
  Wire.begin(wire_konum);
  //Wire.onRequest(wire_veri_gonder);
  //Wire.onReceive(wire_veri_al);
  Serial.begin(9600);
  //eeprom_veri_al();
  pinler();
}

void loop(){
  
}
