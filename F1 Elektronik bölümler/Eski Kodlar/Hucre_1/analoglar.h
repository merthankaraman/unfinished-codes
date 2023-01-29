#include <EEPROM.h>
#include "pinler.h"
int pil_sayisi = 13;

float pil_1_katsayi = (((3900.0+330.0) /330.0) / 13.0), pil_2_katsayi = (((3900.0+390.0) /390.0) / 12.0), pil_3_katsayi = (((4700.0+470.0) / 470.0) / 11.0);
float pil_4_katsayi = (((4700.0+560.0) /560.0) / 10.0), pil_5_katsayi = (((4700.0+680.0) /680.0) / 9.0), pil_6_katsayi = (((10000.0+1500.0) / 1500.0) / 8.0);

float pil_7_katsayi = (((10000.0+1800.0) / 1800.0) / 7.0), pil_8_katsayi = (((10000.0+2200.0) / 2200.0) / 6.0), pil_9_katsayi = (((10000.0+2700.0) / 2700.0) / 5.0);
float pil_10_katsayi = (((10000.0+3300.0) / 3300.0) / 4.0), pil_11_katsayi = (((10000.0+5000.0) / 5000.0) / 3.0), pil_12_katsayi = (((10000.0+10000.0) / 10000.0) / 2.0);

float pil_13_katsayi = 1;

float pil_1_voltaj = 0, pil_2_voltaj = 0, pil_3_voltaj = 0, pil_4_voltaj = 0, pil_5_voltaj = 0, pil_6_voltaj = 0;

float pil_7_voltaj = 0, pil_8_voltaj = 0, pil_9_voltaj = 0, pil_10_voltaj = 0, pil_11_voltaj = 0, pil_12_voltaj = 0;

float pil_13_voltaj = 0;

float sinir_voltaj_pil_1 = 4.0, sinir_voltaj_pil_2 = 4.0, sinir_voltaj_pil_3 = 4.0, sinir_voltaj_pil_4 = 4.0, sinir_voltaj_pil_5 = 4.0, sinir_voltaj_pil_6 = 4.0;

float sinir_voltaj_pil_7 = 4.0, sinir_voltaj_pil_8 = 4.0, sinir_voltaj_pil_9 = 4.0, sinir_voltaj_pil_10 = 4.0, sinir_voltaj_pil_11 = 4.0, sinir_voltaj_pil_12 = 4.0;

float sinir_voltaj_pil_13 = 4.0;

//float sinir_voltaj_pil[pil_sayisi];
float sicaklik = 0;
int kapali_pinler = 0;

void eeprom_veri_al(){
  sinir_voltaj_pil_1 = EEPROM.read(1);
  sinir_voltaj_pil_2 = EEPROM.read(2);
  sinir_voltaj_pil_3 = EEPROM.read(3);
  sinir_voltaj_pil_4 = EEPROM.read(4);
  sinir_voltaj_pil_5 = EEPROM.read(5);
  sinir_voltaj_pil_6 = EEPROM.read(6);
  
  sinir_voltaj_pil_7 = EEPROM.read(7);
  sinir_voltaj_pil_8 = EEPROM.read(8);
  sinir_voltaj_pil_9 = EEPROM.read(9);
  sinir_voltaj_pil_10 = EEPROM.read(10);
  sinir_voltaj_pil_11 = EEPROM.read(11);
  sinir_voltaj_pil_12 = EEPROM.read(12);

  sinir_voltaj_pil_13 = EEPROM.read(13);
}
void eeprom_veri_yaz(){
  EEPROM.write(1,sinir_voltaj_pil_1); EEPROM.write(2,sinir_voltaj_pil_2); EEPROM.write(3,sinir_voltaj_pil_3);
  EEPROM.write(4,sinir_voltaj_pil_4); EEPROM.write(5,sinir_voltaj_pil_5); EEPROM.write(6,sinir_voltaj_pil_6);
  
  EEPROM.write(7,sinir_voltaj_pil_7); EEPROM.write(8,sinir_voltaj_pil_8); EEPROM.write(9,sinir_voltaj_pil_9);
  EEPROM.write(10,sinir_voltaj_pil_10); EEPROM.write(11,sinir_voltaj_pil_11); EEPROM.write(12,sinir_voltaj_pil_12);
  
  EEPROM.write(13,sinir_voltaj_pil_13);
}

void analoglari_oku(){
  pil_1_voltaj = map(analogRead(voltaj_pil_1),0,1023,0,5.0) * pil_1_katsayi;
  pil_2_voltaj = map(analogRead(voltaj_pil_2),0,1023,0,5.0) * pil_2_katsayi;
  pil_3_voltaj = map(analogRead(voltaj_pil_3),0,1023,0,5.0) * pil_3_katsayi;
  pil_4_voltaj = map(analogRead(voltaj_pil_4),0,1023,0,5.0) * pil_4_katsayi;
  pil_5_voltaj = map(analogRead(voltaj_pil_5),0,1023,0,5.0) * pil_5_katsayi;
  pil_6_voltaj = map(analogRead(voltaj_pil_6),0,1023,0,5.0) * pil_6_katsayi;

  pil_7_voltaj = map(analogRead(voltaj_pil_7),0,1023,0,5.0) * pil_7_katsayi;
  pil_8_voltaj = map(analogRead(voltaj_pil_8),0,1023,0,5.0) * pil_8_katsayi;
  pil_9_voltaj = map(analogRead(voltaj_pil_9),0,1023,0,5.0) * pil_9_katsayi;
  pil_10_voltaj = map(analogRead(voltaj_pil_10),0,1023,0,5.0) * pil_10_katsayi;
  pil_11_voltaj = map(analogRead(voltaj_pil_11),0,1023,0,5.0) * pil_11_katsayi;
  pil_12_voltaj = map(analogRead(voltaj_pil_12),0,1023,0,5.0) * pil_12_katsayi;

  pil_13_voltaj = map(analogRead(voltaj_pil_13),0,1023,0,5.0) * pil_13_katsayi;
  //sicaklik = ((analogRead(sicaklik_pin)) / 1023.0) * 500.0;
}
void voltaj_duzenle(float v_istenen, float v_olan, int pin_ayarlayici){
  if(v_olan >= v_istenen) { digitalWrite(pin_ayarlayici,LOW); kapali_pinler++; }
  else { digitalWrite(pin_ayarlayici,HIGH); kapali_pinler--;}
  kapali_pinler == pil_sayisi ? digitalWrite(guc_pini,HIGH) : digitalWrite(guc_pini,LOW);
  
}
void voltaj_duzenle(){
  analoglari_oku();
  voltaj_duzenle(sinir_voltaj_pil_1, pil_1_voltaj ,pil_1_anahtar);
  voltaj_duzenle(sinir_voltaj_pil_2, pil_2_voltaj ,pil_2_anahtar);
  voltaj_duzenle(sinir_voltaj_pil_3, pil_3_voltaj ,pil_3_anahtar);
  voltaj_duzenle(sinir_voltaj_pil_4, pil_4_voltaj ,pil_4_anahtar);
  voltaj_duzenle(sinir_voltaj_pil_5, pil_5_voltaj ,pil_5_anahtar);
  voltaj_duzenle(sinir_voltaj_pil_6, pil_6_voltaj ,pil_6_anahtar);

  voltaj_duzenle(sinir_voltaj_pil_7, pil_7_voltaj ,pil_7_anahtar);
  voltaj_duzenle(sinir_voltaj_pil_8, pil_8_voltaj ,pil_8_anahtar);
  voltaj_duzenle(sinir_voltaj_pil_9, pil_9_voltaj ,pil_9_anahtar);
  voltaj_duzenle(sinir_voltaj_pil_10, pil_10_voltaj ,pil_10_anahtar);
  voltaj_duzenle(sinir_voltaj_pil_11, pil_11_voltaj ,pil_11_anahtar);
  voltaj_duzenle(sinir_voltaj_pil_12, pil_12_voltaj ,pil_12_anahtar);

  voltaj_duzenle(sinir_voltaj_pil_13, pil_13_voltaj ,pil_13_anahtar);
  
}
