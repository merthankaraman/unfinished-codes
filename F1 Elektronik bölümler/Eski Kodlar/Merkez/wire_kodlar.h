#include "analoglar.h"
#include <Wire.h> //I2C dahil ediliyor Nano uno için A4(SDA) A5(SCL) Mega icin 20(SDA) 21(SCL) Leonardo için 2(SDA) ve 3(SCL) SCL 10kohm pull-up hatlara 
//On taraf 1, Arka taraf 2, Hucre_1 3, Hucre_2 4 Motor Sürücü_ 8
const int cihaz_sayisi = 6, veri_sinir=32;
char wire_bolumler[cihaz_sayisi+1][12] = {"Merkez", "On Taraf", "Arka Taraf", "Surucu_1", "Surucu_2", "Hucre_1", "Hucre_2"};
char guncel_veriler[cihaz_sayisi+1][veri_sinir] = {};
char gonderilecekler[cihaz_sayisi+1][veri_sinir] = {};
int i = 0;

String direksiyon_string, gaz_string, fren_string, yon_string, tork_string, toplam_konum;
char direksiyon_char[6] = {}, gaz_char[4], fren_char[4], yon_char[2], tork_char[2];
char bolum_ayirma_isareti = ';';

char intten_chara(int sayi, char b[6]){
  String a;
  a = String(sayi);
  a.toCharArray(b,6);
}

#define reset_pin 12
void reset_kontrol(){
  if(guncel_veriler[i][0] == 'R' && guncel_veriler[i][1] == 'E' && guncel_veriler[i][2] == 'S'){
    digitalWrite(reset_pin,LOW);
  }
}

void analog_verileri_kaydet(){
  verileri_duzenle();
  intten_chara(direksiyon_konum,direksiyon_char);
  intten_chara(gaz_konum,gaz_char);
  intten_chara(fren_konum,fren_char);
  intten_chara(yon,yon_char);
  intten_chara(tork_modu,tork_char);
  direksiyon_string = "D"+ String(direksiyon_konum) + bolum_ayirma_isareti ;
  gaz_string = "G" + String(gaz_konum) + bolum_ayirma_isareti ;
  fren_string = "F" + String(fren_konum) + bolum_ayirma_isareti;
  yon_string = "Y" + String(yon) + bolum_ayirma_isareti;
  tork_string = "T" + String(tork_modu) + bolum_ayirma_isareti;
  toplam_konum = direksiyon_string + gaz_string + fren_string + yon_string + tork_string;
  toplam_konum.toCharArray(guncel_veriler[0],veri_sinir);
}

void gonder_on_kisim(){
  Wire.beginTransmission(1);
  Wire.write(direksiyon_char);
  Wire.write("%");
  Wire.endTransmission();
}
void gonder_surucu_1(){
  Wire.beginTransmission(3);
  Wire.write("G"); Wire.write(gaz_char); Wire.write(bolum_ayirma_isareti); Wire.write("F"); Wire.write(fren_char); Wire.write(bolum_ayirma_isareti); 
  Wire.write("Y"); Wire.write(yon_char); Wire.write(bolum_ayirma_isareti); Wire.write("T"); Wire.write(tork_char); Wire.write(bolum_ayirma_isareti);
  Wire.write("%");
  Wire.endTransmission();
}

void veri_al(){
  //simdiki_zaman = millis();
  memset(guncel_veriler, 0, sizeof(guncel_veriler));
  analog_verileri_kaydet();
  for(i=1;i<=cihaz_sayisi;i++){
    Wire.requestFrom(i,veri_sinir);
    int j=0;
    while (Wire.available()){
      char veri = Wire.read();
      if (veri == '%'){ reset_kontrol(); return;}
      guncel_veriler[i][j] = veri;
      j++;
    }
  }
}

void wire_loop(){
  analog_verileri_kaydet();
}
