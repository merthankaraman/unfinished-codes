#include <Wire.h> //I2C dahil ediliyor Nano uno için A4(SDA) A5(SCL) Mega icin 20(SDA) 21(SCL) Leonardo için 2(SDA) ve 3(SCL) SCL 10kohm pull-up hatlara 
//On taraf 1, Arka taraf 2, Hucre_1 3, Hucre_2 4 BU HATLARIN BOŞ BIRAKILMASI GEREKİYOR YOKSA BU HATLARDAN VERİ OKUYAMAZSIN

const int veri_sinir = 32;
char alinan_veri[veri_sinir] = {},gonderilen_veri[veri_sinir]={};
String toplam_veriler;

String pil_1_string, pil_2_string, pil_3_string, pil_4_string, pil_5_string, pil_6_string;
String pil_7_string, pil_8_string, pil_9_string, pil_10_string, pil_11_string, pil_12_string;
String pil_13_string;


char intten_chara(int sayi, char b[6]){
  String a;
  a = String(sayi);
  a.toCharArray(b,6);
}

#define reset_pin 12
void reset_kontrol(){
  if(alinan_veri[0] == 'R' && alinan_veri[1] == 'E' && alinan_veri[2] == 'S'){
    digitalWrite(reset_pin,LOW);
  }
}

void wire_verileri_duzenle(){
  /*intten_chara(pil_1_voltaj,pil_1_char); intten_chara(pil_2_voltaj,pil_2_char); intten_chara(pil_3_voltaj,pil_3_char);
  intten_chara(pil_4_voltaj,pil_4_char); intten_chara(pil_5_voltaj,pil_5_char); intten_chara(pil_6_voltaj,pil_6_char);
  intten_chara(pil_7_voltaj,pil_7_char); intten_chara(pil_8_voltaj,pil_8_char); intten_chara(pil_9_voltaj,pil_9_char);
  intten_chara(pil_10_voltaj,pil_10_char); intten_chara(pil_11_voltaj,pil_11_char); intten_chara(pil_12_voltaj,pil_12_char);
  intten_chara(pil_13_voltaj,pil_13_char);*/
  pil_1_string = "P1" + String(pil_1_voltaj) + "/"; pil_2_string = "P2" + String(pil_2_voltaj) + "/"; pil_3_string = "P3" + String(pil_3_voltaj) + "/";
  pil_4_string = "P4" + String(pil_4_voltaj) + "/"; pil_5_string = "P5" + String(pil_5_voltaj) + "/"; pil_6_string = "P6" + String(pil_6_voltaj) + "/";

  pil_7_string = "P7" + String(pil_7_voltaj) + "/"; pil_8_string = "P8" + String(pil_8_voltaj) + "/"; pil_9_string = "P9" + String(pil_9_voltaj) + "/";
  pil_10_string = "P10" + String(pil_10_voltaj) + "/"; pil_11_string = "P11" + String(pil_11_voltaj) + "/"; pil_12_string = "P12" + String(pil_12_voltaj) + "/";

  pil_13_string = "P13" + String(pil_13_voltaj) + "/";

  toplam_veriler = pil_1_string + pil_2_string + pil_3_string + pil_4_string + pil_5_string + pil_6_string;
  toplam_veriler += pil_7_string + pil_8_string + pil_9_string + pil_10_string + pil_11_string + pil_12_string + pil_13_string;
  toplam_veriler.toCharArray(gonderilen_veri,veri_sinir);
  
}

/*void wire_verileri_duzenle(){
  char harf;
  memset(alinan_veri, 0, sizeof(alinan_veri));
  for(int i=0;i<=veri_sinir;i++){
    harf = alinan_veri[i];
    if(harf == 'P'){
      int j=0,k=0;
      i+=1;
      for(;k<1;i++,j++){
        harf = alinan_veri[i];
        if(harf == '/') {i -= 1;k=1;}
        if(harf != '/'); }
    }
  }
}*/
