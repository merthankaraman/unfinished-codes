//#include "matematik_kismi.h"
#include "matematik_kismi_v2.h"
unsigned long yeni_zaman = 0, eski_zaman = 0;
int bekleme_suresi = 0;

void motorlari_calistir(){
  acidan_koordinat_yap();
  yeni_zaman = millis();
  if(yeni_zaman - eski_zaman >= bekleme_suresi - 0.001){
    servo_1.write(servo_1_aci); servo_2.write(servo_2_aci); servo_3.write(servo_3_aci);
    eski_zaman = yeni_zaman;
  }
}
