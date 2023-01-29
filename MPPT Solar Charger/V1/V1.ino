#include <EEPROM.h>
#include "pinler_ve_okuma.h"
#include "algoritma.h"
#include "pil_sarj.h"
#include "iletisim.h"
//#include "iletisim_eski.h"
#include "kolay_ayarlar.h"


void setup(){
  Serial.begin(115200);
  kolay_setup();
  pinler_setup();
  iletisim_setup();
  sarj_durumu = kapali;
  pil_secimi();
  algoritma_setup();
}

void loop(){
  degerleri_oku();
  sarj_baslat();
  seri_port_loop();
  //Serial.print("PV:"); Serial.print(solar_V); Serial.print("V;"); Serial.print(solar_A); Serial.print("A;"); Serial.print(solar_W); Serial.println("W");
  
}
