
unsigned long yeni_ekran_zaman = 0, eski_ekran_zaman = 0;

void seri_port_yazdir(){
  yeni_ekran_zaman = millis();
  if (yeni_ekran_zaman - eski_ekran_zaman >= 500 + 0.01){
    Serial.print("Suanki konum X:"); Serial.print(suanki_konum[0]); Serial.print("\tY:"); Serial.print(suanki_konum[1]); Serial.print("\tZ:"); Serial.println(suanki_konum[2]); 
    Serial.print("servo_1_aci "); Serial.println(servo_1_aci); Serial.print("servo_2_aci "); Serial.println(servo_2_aci); Serial.print("servo_3_aci "); Serial.println(servo_3_aci); Serial.println("************");
    //Serial.print("servo_1_istenen_aci"); Serial.println(servo_1_istenen_aci); Serial.print("servo_2_istenen_aci"); Serial.println(servo_2_istenen_aci);Serial.print("servo_3_istenen_aci"); Serial.println(servo_3_istenen_aci); Serial.println("************");
    eski_ekran_zaman = yeni_ekran_zaman;
  }
}
