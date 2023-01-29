#include <Wire.h> //I2C dahil ediliyor Nano uno için A4(SDA) A5(SCL) Mega icin 20(SDA) 21(SCL) Leonardo için 2(SDA) ve 3(SCL) SCL 10kohm pull-up hatlara 
//On taraf 1, Arka taraf 2, Hucre_1 3, Hucre_2 4
const int veri_sinir = 32;
char alinan_veri[veri_sinir] = {},gonderilen_veri[veri_sinir]={};;
#define direksiyon_servo_pin A0
int direksiyon_servo_aci,istenen_aci;
String direksiyon_servo_string, farlar_string, pil_string, sicaklik_string,toplam_string;
#define farlar 13
int farlar_durum;
float pil_durum, sicaklik_durum;
#define pil_analog_pin A1
#define sicaklik_analog_pin A2
#define motor_faz_hiz 6
#define motor_faz_1 7
#define motor_faz_2 8
String gelen_aci_string;
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
  Wire.begin(1);
  Wire.onRequest(wire_veri_gonder);
  Wire.onReceive(wire_veri_al);
  pinMode(farlar,OUTPUT);
  pinMode(motor_faz_1,OUTPUT);
  pinMode(motor_faz_2,OUTPUT);
  pinMode(motor_faz_hiz,OUTPUT);
  Serial.begin(9600);
}

void motor_sur(int yon,float hiz){
  analogWrite(motor_faz_hiz,hiz);
  if(yon == -1){
    Serial.print("-1 yonune donuluyor hiz:"); Serial.println(hiz);
    digitalWrite(motor_faz_1,HIGH);
    digitalWrite(motor_faz_2,LOW);
  }
  else if (yon == 0){
    Serial.println("0 yonune donuluyor hiz:"); Serial.println(hiz);
    digitalWrite(motor_faz_1,HIGH);
    digitalWrite(motor_faz_2,HIGH);
  }
  else if(yon == 1){
    Serial.print("1 yonune donuluyor hiz:"); Serial.println(hiz);
    digitalWrite(motor_faz_1,LOW);
    digitalWrite(motor_faz_2,HIGH);
  }
  
}



void verileri_al(){
  direksiyon_servo_aci = map(analogRead(direksiyon_servo_pin),0,1023,-180,180);
  direksiyon_servo_string = "D:" + String(direksiyon_servo_aci) + "/";
  gelen_aci_string = String(alinan_veri);
  istenen_aci = gelen_aci_string.toInt();
  farlar_string = "F:" + String(farlar_durum);
  pil_durum = analogRead(pil_analog_pin) * (5.0/1023.0);
  pil_string = "P:" + String(pil_durum) + "V"  + "/" ;
  sicaklik_durum = analogRead(sicaklik_analog_pin) * (5.0/1023.0);
  sicaklik_string = "S:" + String(sicaklik_durum) + "C";
  toplam_string = direksiyon_servo_string + farlar_string + pil_string + sicaklik_string;
  toplam_string.toCharArray(gonderilen_veri,veri_sinir);
  
  
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
void direksiyon_konum_hareket(){
  verileri_al();
  Serial.print("Istenen aci: "); Serial.print(istenen_aci); Serial.print(" Suanki aci: "); Serial.println(direksiyon_servo_aci);
  if(istenen_aci < direksiyon_servo_aci){
    motor_sur(-1,map(istenen_aci-direksiyon_servo_aci,-360,360,255,100));
  }
  else if(istenen_aci == direksiyon_servo_aci){
    motor_sur(0,255);
  }
  else if(istenen_aci > direksiyon_servo_aci){
    motor_sur(1,map(istenen_aci-direksiyon_servo_aci,360,-360,255,100));
  }
}

void loop(){
  direksiyon_konum_hareket();
  //Serial.println(gonderilen_veri);
  //Serial.println(istenen_aci);
  //Serial.print("Gelen: "); Serial.println(alinan_veri);
  wire_veri_gonder();
 // delay(200);
}
