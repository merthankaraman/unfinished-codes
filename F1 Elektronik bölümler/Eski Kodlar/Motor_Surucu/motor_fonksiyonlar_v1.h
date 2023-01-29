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

#define AL 2
#define BL 4
#define CL 6

#define AH 3
#define BH 5
#define CH 7
void portlari_temizle(){
  digitalWrite(AL,LOW); digitalWrite(BL,LOW); digitalWrite(CL,LOW);
  digitalWrite(AH,LOW); digitalWrite(BH,LOW); digitalWrite(CH,LOW);
}
void motor_pinler(){
  pinMode(sensor_pin,INPUT);
  pinMode(sarj_pin,OUTPUT); digitalWrite(sarj_pin,LOW);
  pinMode(AL,OUTPUT); pinMode(BL,OUTPUT); pinMode(CL,OUTPUT);
  pinMode(AH,OUTPUT); pinMode(BH,OUTPUT); pinMode(CH,OUTPUT);
}

void AH_BL(){
  digitalWrite(AH,HIGH);
  digitalWrite(BL,HIGH);
}

void AH_CL(){
  digitalWrite(AH,HIGH);
  digitalWrite(CL,HIGH);
}
void BH_CL(){
  digitalWrite(BH,HIGH);
  digitalWrite(CL,HIGH);
}
void BH_AL(){
  digitalWrite(BH,HIGH);
  digitalWrite(AL,HIGH);
}
void CH_AL(){
  digitalWrite(CH,HIGH);
  digitalWrite(AL,HIGH);
}
void CH_BL(){
  digitalWrite(CH,HIGH);
  digitalWrite(BL,HIGH);
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
  digitalWrite(AH,HIGH); digitalWrite(BH,HIGH); digitalWrite(CH,HIGH); 
}
void fren_bos(){
  digitalWrite(AH,LOW); digitalWrite(BH,LOW); digitalWrite(CH,LOW);
}
