unsigned long yeni_zaman=0, eski_zaman=0, fren_yeni_zaman=0, fren_eski_zaman=0;


void ileri_motor_sur(){
  yeni_zaman = millis();
  if(((yeni_zaman - eski_zaman >= gaz_seviyesi) || tam_gaz == 1)  && (tork_modu ? (digitalRead(sensor_pin) == HIGH) : 1)){
    eski_zaman = yeni_zaman;
    adimlar();
    siradaki_adim++;
    siradaki_adim %= 6;
  }
}
void geri_motor_sur(){
  yeni_zaman = millis();
  if(((yeni_zaman - eski_zaman >= gaz_seviyesi) || tam_gaz == 1)  && (tork_modu ? (digitalRead(sensor_pin) == HIGH) : 1)){
    eski_zaman = yeni_zaman;
    siradaki_adim--;
    if(siradaki_adim < 0) siradaki_adim = 5;
    adimlar();
  }
}
void fren(){
  //PORTD |= B00000000; //D0dan d7e kadar bütün pinler 0 voltta
  portlari_temizle();
  fren_yeni_zaman = millis();
  if((fren_yeni_zaman - fren_eski_zaman >= fren_seviyesi) || tam_fren == 1){
    //Serial.println("Frende");
    //PORTB = B00001110; //D9 dan d11e kadar pinleri 5 volta ayarladık
    digitalWrite(AH,HIGH); digitalWrite(BH,HIGH); digitalWrite(CH,HIGH); 
    fren_eski_zaman = fren_yeni_zaman;
    return;
  }
  digitalWrite(AH,LOW); digitalWrite(BH,LOW); digitalWrite(CH,LOW);
  //PORTB = B00000000; //D9 dan d11e kadar pinleri 0 volta ayarladık sürekli kilitlenmesin diye
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
