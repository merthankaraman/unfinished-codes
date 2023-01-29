unsigned long yeni_zaman=0, eski_zaman=0, fren_yeni_zaman=0, fren_eski_zaman=0;
boolean sensor_bekle_1 = false , sensor_bekle_2 = false;

void ileri_motor_sur(){
  yeni_zaman = millis();
  if(((yeni_zaman - eski_zaman >= gaz_seviyesi) || tam_gaz == 1)  && (tork_modu ? (sensor_durum == HIGH) : 1)){
    adimlar();
    sensor_bekle_1 = true;
    if(tork_modu == false){
      eski_zaman = yeni_zaman;
      siradaki_adim++;
      siradaki_adim %= 6;
    }
  }
  if(tork_modu ? sensor_bekle_1 == true && sensor_durum == LOW : 0){
    eski_zaman = yeni_zaman;
    siradaki_adim++;
    siradaki_adim %= 6;
    sensor_bekle_1 = false;
  }
  if(((yeni_zaman - eski_zaman >= gaz_seviyesi) || tam_gaz == 1)  && (tork_modu ? (sensor_durum == LOW) : 1)){
    adimlar();
    sensor_bekle_2 = true;
    if(tork_modu == false){
      eski_zaman = yeni_zaman;
      siradaki_adim++;
      siradaki_adim %= 6;
    }
  }
  if(tork_modu ? sensor_bekle_2 == true && sensor_durum == HIGH : 0){
    eski_zaman = yeni_zaman;
    siradaki_adim++;
    siradaki_adim %= 6;
    sensor_bekle_2 = false;
  }
}
void geri_motor_sur(){
  yeni_zaman = millis();
  if(((yeni_zaman - eski_zaman >= gaz_seviyesi) || tam_gaz == 1)  && (tork_modu ? (sensor_durum == HIGH) : 1)){
    sensor_bekle_1 = true;
    if(tork_modu == false){
      eski_zaman = yeni_zaman;
      siradaki_adim--;
    }
    if(siradaki_adim < 0) siradaki_adim = 5;
    adimlar();
  }
  if(tork_modu ? sensor_bekle_1 == true && sensor_durum == LOW : 0){
    eski_zaman = yeni_zaman;
    siradaki_adim--;
    sensor_bekle_1 = false;
  }

  if(((yeni_zaman - eski_zaman >= gaz_seviyesi) || tam_gaz == 1)  && (tork_modu ? (sensor_durum == LOW) : 1)){
    sensor_bekle_2 = true;
    if(tork_modu == false){
      eski_zaman = yeni_zaman;
      siradaki_adim--;
    }
    if(siradaki_adim < 0) siradaki_adim = 5;
    adimlar();
  }
  if(tork_modu ? sensor_bekle_2 == true && sensor_durum == HIGH : 0){
    eski_zaman = yeni_zaman;
    siradaki_adim--;
    sensor_bekle_2 = false;
  }
}
void fren(){
  portlari_temizle();
  fren_yeni_zaman = millis();
  if(frende_sarj_modu == true){
    //if(fren_yeni_zaman - fren_eski_zaman >= (fren_seviyesi - (fren_seviyesi*95)/100)) {digitalWrite(sarj_pin,LOW); }
    if(fren_seviyesi >= (fren_az_sert - (fren_az_sert/2))) {digitalWrite(sarj_pin,HIGH); }
  }
  if((fren_yeni_zaman - fren_eski_zaman >= fren_seviyesi) || tam_fren == 1){
    digitalWrite(sarj_pin,LOW);
    //Serial.println("Frende");
    //PORTB = B00001110; //D9 dan d11e kadar pinleri 5 volta ayarladık
    fren_hareketi();
    fren_eski_zaman = fren_yeni_zaman;
    return;
  }
  frende_sarj_modu ? digitalWrite(sarj_pin,HIGH) : digitalWrite(sarj_pin,LOW);
  fren_bos();
}
int fren_kontrol(){
  verileri_duzenle();
  if(fren_seviyesi < fren_az_sert-35){
    fren();
    return 0;
  }
  return 1;
}
void motor_sur(){
  if(rpm_oku == true) rpm_hesapla();
  if (sarj_modu == false){
        digitalWrite(sarj_pin,LOW);
  }
      
  verileri_duzenle();
  if(fren_kontrol() > 0){
    if(gaz_seviyesi >= az_hiz - az_hiz/10){
      //Serial.println("Boşta");
      portlari_temizle();
      if (sarj_modu == true){
        digitalWrite(sarj_pin,HIGH);
      }
      /*PORTD != B00000000;
      PORTB = B00000000;*/
        }
      else if(gaz_seviyesi < az_hiz- az_hiz/10){
        digitalWrite(sarj_pin,LOW);
        if(yon == 1){
          ileri_motor_sur();
          return;
          }
        else if(yon == 0){
          geri_motor_sur();
          return;
          }
      }
  }
  
}
