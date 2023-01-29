#include <Wire.h> //I2C dahil ediliyor Nano uno için A4(SDA) A5(SCL) Mega icin 20(SDA) 21(SCL) Leonardo için 2(SDA) ve 3(SCL) SCL 10kohm pull-up hatlara 
//On taraf 1, Arka taraf 2, Hucre_1 3, Hucre_2 4 BU HATLARIN BOŞ BIRAKILMASI GEREKİYOR YOKSA BU HATLARDAN VERİ OKUYAMAZSIN
//#include <EEPROM.h> //PWM pinleri 3 5 6 9 10 11
#define wire_konum 3
const int veri_sinir = 32;
char alinan_veri[veri_sinir] = {}/*"G1023/F1023/Y1/T1"*/, gonderilen_veri[veri_sinir]="IYI";


String gaz_string, fren_string;
char gaz_char[7] ={}, fren_char[7] {}, yon_char[2] = {}, tork_char[2] = {};
int gaz_seviyesi= 0, fren_seviyesi = 0, fren_az_sert= 500, fren_fazla_sert=0, fazla_hiz = 0, az_hiz = 500;
int yon = 1, tam_gaz = 0, tam_fren = 0;

#define reset_pin 12
void reset_kontrol(){
  if(alinan_veri[0] == 'R' && alinan_veri[1] == 'E' && alinan_veri[2] == 'S'){
    digitalWrite(reset_pin,LOW);
  }
}

void wire_verileri_duzenle(){
  char harf;
  memset(gaz_char, 0, sizeof(gaz_char)); memset(fren_char, 0, sizeof(fren_char)); memset(yon_char, 0, sizeof(yon_char)); memset(tork_char, 0, sizeof(tork_char));
  for(int i=0;i<=veri_sinir;i++){
    harf = alinan_veri[i];
    if(harf == 'G'){
      int j=0,k=0;
      i+=1;
      for(;k<1;i++,j++){
        harf = alinan_veri[i];
        if(harf == '/') {i -= 1;k=1;}
        if(harf != '/') gaz_char[j] = harf;}
    }
    else if(harf == 'F'){
      int j=0,k=0;
      i+=1;
      for(;k<1;i++,j++){
        harf = alinan_veri[i];
        if(harf == '/') {i -= 1,k=1;}
        if(harf != '/') fren_char[j] = harf;}
    }
    else if(harf == 'Y'){
      int j=0,k=0;
      i+=1;
      for(;k<1;i++,j++){
        harf = alinan_veri[i];
        if(harf == '/') {i -= 1,k=1;}
        if(harf != '/') yon_char[j] = harf;}
    }
    else if(harf == 'T'){
      int j=0,k=0;
      i+=1;
      for(;k<1;i++,j++){
        harf = alinan_veri[i];
        if(harf == '/') {i -= 1,k=1;}
        if(harf != '/') tork_char[j] = harf;}
    }
  }
}
void verileri_duzenle(){
  //wire_verileri_duzenle();
  sensor_durum = digitalRead(sensor_pin);
  if((rpm_onceki_durum == LOW && sensor_durum == HIGH) && (rpm_oku == true)) {sensor_rpm++;  rpm_onceki_durum = HIGH; }
  else if ((rpm_onceki_durum == HIGH && sensor_durum == LOW) && (rpm_oku == true)){sensor_rpm++;  rpm_onceki_durum = LOW; }
  String gaz_string = gaz_char, fren_string = fren_char, yon_string = yon_char , tork_string = tork_char;
  gaz_seviyesi = map(gaz_string.toInt(),0,1023,az_hiz,fazla_hiz);
  if(gaz_seviyesi < fazla_hiz + 10) tam_gaz = 1;
  else tam_gaz = 0;
  fren_seviyesi = map(fren_string.toInt(),0,1023,fren_az_sert,fren_fazla_sert);
  if(fren_seviyesi < fren_fazla_sert + 15) tam_fren = 1;
  else tam_fren = 0;
  yon = yon_string.toInt();
  tork_modu = tork_string.toInt();
}

void wire_veri_gonder(){
  Wire.write(hiz_char);
  Wire.write("%");
  
}
void wire_veri_al(){
  int i=0;
  memset(alinan_veri, 0, sizeof(alinan_veri));
  while(Wire.available()){
    char veri = Wire.read();
    if(veri == '%'){ reset_kontrol(); wire_verileri_duzenle(); return;}
    alinan_veri[i] = veri;
    i++;
  }
}
void wire_setup(){
  digitalWrite(reset_pin,HIGH); //wire ile ilgili bazen senkron hatası yapıyor eğer merkez resetlenirse diğer bölgeler de kendisini resetliyor
  delay(200);
  pinMode(reset_pin,OUTPUT);
  Wire.begin(wire_konum);
  Wire.onRequest(wire_veri_gonder);
  Wire.onReceive(wire_veri_al);
}
