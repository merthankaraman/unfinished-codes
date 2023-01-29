#include "motorlar_kismi.h"
#include "seri_port_kismi.h"



void setup(){
  baglantilar_setup();
  kol_1_mesafe = 100, kol_2_mesafe = 100, govde_yukseklik = 100; // kol_1 ön kol dikey eksen ****** kol_2 arka kol dikey eksen
  servo_1_sifirlama_payi = 0, servo_2_sifirlama_payi = 0, servo_3_sifirlama_payi = 180;
  ek_x_mesafe = 0, ek_y_mesafe = 0, ek_z_mesafe = 0;
  bekleme_suresi = 500;
  Serial.begin(9600);
}
int x_artma_sinir = 5, y_artma_sinir = 5;//, z_artma_sinir = 100;
float x_sinir = 100, y_sinir = 200, z_sinir = 100;
void joystickten_oku(){
  istenen_koordinat[0] = constrain(map(analogRead(joystick_x),0,1023,-x_artma_sinir,x_artma_sinir) + suanki_konum[0],-x_sinir,x_sinir);
  istenen_koordinat[1] = constrain(map(analogRead(joystick_y),0,1023,-y_artma_sinir,y_artma_sinir) + suanki_konum[1],-y_sinir,y_sinir);
  istenen_koordinat[2] = constrain(map(analogRead(pot_z),0,1023,0,z_sinir),0,z_sinir);
  
}

void loop(){
  joystickten_oku();
  istenen_koordinata_acila();
  motorlari_calistir();
  seri_port_yazdir();
  //Serial.println("**************************"); Serial.println(analogRead(joystick_x)); Serial.println(analogRead(joystick_y)); Serial.println(analogRead(pot_z));
  //delay(1000);

}
