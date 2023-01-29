#include "pinler.h"

int direksiyon_konum, gaz_konum, fren_konum, yon = 1, tork_modu = 0;

void verileri_duzenle(){
  direksiyon_konum = analogRead(direksiyon_pin);
  gaz_konum = analogRead(gaz_pin);
  fren_konum = analogRead(fren_pin);
  yon = digitalRead(yon_pin);
  tork_modu = digitalRead(tork_modu_pin);
}
