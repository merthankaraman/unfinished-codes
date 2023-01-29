//#include "motor_fonksiyonlar_v1.h"
#include "motor_fonksiyonlar_v2.h"

//#include "wire_kodlar.h"
#include "analog_kodlar.h"

//#include "Sensorlu.h"
//#include "Sensorsuz.h"
#include "Sensorlu_v2.h"




void setup(){
  //wire_setup();
  motor_pinler();
  Serial.begin(9600);
  lastik_cap = 2;
  rpm_oku = true;
  tork_modu = false;
  sarj_modu = true;
  frende_sarj_modu = false;
  fren_az_sert= 1000, fren_fazla_sert=0, fazla_hiz = 0, az_hiz = 500, yon = 0;
}
void loop(){
  //verileri_duzenle();
  motor_sur();
  //Serial.print("RPM: "); Serial.println(rpm); Serial.print("\tHIZ: "); Serial.println(hiz); 
  //Serial.println(siradaki_adim);
  //Serial.println(sensor_rpm);
  //Serial.print("Gaz: "); Serial.print(gaz_seviyesi); Serial.print("\t\tFren: "); Serial.println(fren_seviyesi);
  //Serial.print("Tam_gaz: "); Serial.print(tam_gaz); Serial.print("tam_fren: "); Serial.println(tam_fren);
  //Serial.println(digitalRead(sensor_pin));
  //Serial.print("Gaz: "); Serial.print(gaz_char); Serial.print("\t\tFren: "); Serial.println(fren_char);
}
