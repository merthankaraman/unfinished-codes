#include <Wire.h> //I2C dahil ediliyor Nano uno için A4(SDA) A5(SCL) Mega icin 20(SDA) 21(SCL) Leonardo için 2(SDA) ve 3(SCL) SCL 10kohm pull-up hatlara 
//On taraf 1, Arka taraf 2, Hucre_1 3, Hucre_2 4 BU HATLARIN BOŞ BIRAKILMASI GEREKİYOR YOKSA BU HATLARDAN VERİ OKUYAMAZSIN
#include <EEPROM.h> //PWM pinleri 3 5 6 9 10 11
const int veri_sinir = 32;
char alinan_veri[veri_sinir] = {},gonderilen_veri[veri_sinir]={};
#define voltaj_giris_pin A0 //Güç kaynağından gelen voltaj okuma
#define voltaj_cikis_pin A1 //Pillere giden voltaj okuma
#define akim_pin A2
#define sicaklik_pin A3 //  LM35DZ Yazi on 5V Analog GND  \\

#define v_ayar 3 //PWM
#define a_ayar 5 //PWM
float voltaj_giris_veri, voltaj_cikis_veri, akim_veri, sicaklik_veri;
float voltaj_istenen = 4.2, akim_istenen = 2.0, voltaj_gereken, akim_gereken ,akim_sinir = 3.0, voltaj_donusturucu_ust_sinir; //Voltaj regülatörünün maksimum değeri 
float voltaj_sinir = 5; //Voltaj giriş pininin ölçtüğü maksimum değerin kaça eşit olduğu belirleniyor
int akim_direnc = 10;
String voltaj_giris_string, voltaj_cikis_string, akim_string, sicaklik_string, toplam_string;

#define reset_pin 12

void reset_kontrol(){
  if(alinan_veri[0] == 'R' && alinan_veri[1] == 'E' && alinan_veri[2] == 'S'){
    digitalWrite(reset_pin,LOW);
  }
}

void setup(){
  digitalWrite(reset_pin,HIGH);
  delay(200);
  pinMode(reset_pin,OUTPUT);
  //akim_istenen = EEPROM.read(1);
  Wire.begin(3);
  Wire.onRequest(wire_veri_gonder);
  Wire.onReceive(wire_veri_al);
  Serial.begin(9600);
  pinMode(v_ayar,OUTPUT);
  pinMode(a_ayar,OUTPUT);
}
void verileri_al(){
  voltaj_giris_veri = (((analogRead(voltaj_giris_pin)) / 1023.0) * voltaj_sinir); //Analog pinden alınan maksimum 5 voltun aslında bölücülerle kaç volt olduğu hesaplanıyor
  voltaj_giris_string = "VG:" + String(voltaj_giris_veri) + "/";
  voltaj_donusturucu_ust_sinir = voltaj_giris_veri - 2.0; //Voltaj regülatörünün maksimum değeri 
  voltaj_cikis_veri = (((analogRead(voltaj_cikis_pin)) / 1023.0) * voltaj_sinir);
  voltaj_cikis_string = "VC:" + String(voltaj_cikis_veri) + "/";
  akim_veri = (analogRead(akim_pin)) / 1023.0;
  akim_string = "A:" + String(akim_veri) + "/";
  sicaklik_veri = ((analogRead(sicaklik_pin)) / 1023.0) * 500.0;
  sicaklik_string = "S:" + String(sicaklik_veri);
  toplam_string = voltaj_giris_string + voltaj_cikis_string + akim_string + sicaklik_string;
  toplam_string.toCharArray(gonderilen_veri,veri_sinir);
  voltaj_duzenle();
  akim_duzenle();
}

void voltaj_duzenle(){
  voltaj_gereken = voltaj_istenen - (voltaj_cikis_veri - voltaj_istenen);
  if (voltaj_gereken > voltaj_donusturucu_ust_sinir) voltaj_gereken = voltaj_donusturucu_ust_sinir;
  else if(voltaj_gereken < 0) voltaj_gereken = 0;
  analogWrite(v_ayar,(voltaj_gereken/voltaj_donusturucu_ust_sinir)*255.0);
}
void akim_duzenle(){
  akim_gereken = akim_istenen - (akim_veri - akim_istenen);
  if (akim_gereken > akim_sinir) akim_gereken = akim_sinir;
  else if(akim_gereken < 0) akim_gereken = 0;
  analogWrite(a_ayar,(akim_gereken/akim_sinir)*255.0);
}

void wire_veri_gonder(){
  Wire.write(gonderilen_veri);
  Wire.write("%");
  
}
void wire_veri_al(){
  int i=0;
  memset(alinan_veri, 0, sizeof(alinan_veri));
  while(Wire.available()){
    char veri = Wire.read();
    if(veri == '%'){ reset_kontrol(); return;}
    alinan_veri[i] = veri;
    i++;
  }
}

void loop(){
  wire_veri_gonder();
  verileri_al();
}
