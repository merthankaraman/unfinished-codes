#include "wire_kodlar.h"

unsigned long simdiki_zaman=0, eski_zaman=0;
void butun_cihazlari_resetle(){
  for(int k=1;k<=cihaz_sayisi;k++){
    Wire.beginTransmission(k);
    Wire.write("RES");
    Wire.write("%");
    Wire.endTransmission();
  }
}

void wire_veri_ilet(){
  gonder_on_kisim();
  gonder_surucu_1();
}


void durumlari_yaz(){
  for(int i=0;i<=cihaz_sayisi;i++){
    Serial.print(wire_bolumler[i]); Serial.print(";"); Serial.print(guncel_veriler[i]); Serial.println("%");
  }
  //Serial.println("--------------------------------");
  
}


void setup(){
  pinler_setup();
  Wire.begin();
  butun_cihazlari_resetle();
  Serial.begin(9600);
}

void loop(){
  wire_loop();
  veri_al();
  durumlari_yaz();
  wire_veri_ilet();
}
