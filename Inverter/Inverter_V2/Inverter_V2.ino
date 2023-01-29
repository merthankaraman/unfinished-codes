#include "Pinler.h"
#include "Duzenlenmis_kare_dalga.h"
#include "Kare_dalga.h"




void setup(){
  h_koprusu = false;
  kurulum_ayarlari();
  Serial.begin(115200);
}

void loop(){
  ekrana_yazdir();
  kare_dalga_olustur();
}
