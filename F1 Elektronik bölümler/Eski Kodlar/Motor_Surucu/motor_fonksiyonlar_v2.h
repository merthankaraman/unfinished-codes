int siradaki_adim = 0;

boolean tork_modu = true, sarj_modu = false, frende_sarj_modu = true, sensor_durum = false;

int sensor_rpm=0,rpm=0;
float hiz = 0, lastik_cap = 2;
boolean rpm_onceki_durum = false, rpm_oku = false;
unsigned long rpm_zaman=0;
char hiz_char[6] = {};

void hiz_hesapla(){
  hiz = ((2*PI*lastik_cap)/60)*rpm;
  String hiz_string = String(hiz);
  hiz_string.toCharArray(hiz_char,6);
}
void rpm_hesapla(){
  if(millis() - rpm_zaman >= 1000){//rpm = devir/60
    rpm = sensor_rpm*60;
    sensor_rpm = 0;
    rpm_zaman = millis();
    hiz_hesapla();
  }
}

#define sensor_pin 8
#define sarj_pin 9
#define yon_pin 12
#define tork_modu_pin 11

/*#define AL 2
#define BL 4
#define CL 6

#define AH 3
#define BH 5
#define CH 7*/

void portlari_temizle(){
  PORTD = B00000000;
}
void motor_pinler(){
  pinMode(sensor_pin,INPUT);
  pinMode(sarj_pin,OUTPUT); digitalWrite(sarj_pin,LOW);
  DDRD = B11111100;  //D2 D3 D4 D5 D6 D7 pinlerini çıkış olarak ayarladık
  PORTD = B00000000;
}

void AH_BL(){
  PORTD = B0011000; //d3 d4 yüksek
}

void AH_CL(){
  PORTD = B1001000; //d3 d6 yüksek
}
void BH_CL(){
  PORTD = B1100000; //d5 d6 yüksek
}
void BH_AL(){
  PORTD = B0100100; //d5 d2 yüksek
}
void CH_AL(){
  PORTD = B10000100; //d7 d2 yüksek
}
void CH_BL(){
  PORTD = B10010000; //d7 d4 yüksek
}

void adimlar(){
  portlari_temizle();
  switch(siradaki_adim){
    case 0:
      AH_BL();
      break;
    case 1:
      AH_CL();
      break;
    case 2:
      BH_CL();
      break;
    case 3:
      BH_AL();
      break;
    case 4:
      CH_AL();
      break;
    case 5:
      CH_BL();
      break;
  }
}
void fren_hareketi(){
  PORTD = B10101000;
}
void fren_bos(){
  PORTD = B00000000;
}
