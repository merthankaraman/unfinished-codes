int fren_kontrol(){
  return 1;
}


void motor_sur(){
  verileri_duzenle();

  if(fren_kontrol() > 0){
    if(gaz_seviyesi > (gaz_min_seviyesi + 115)){
      //digitalWrite(sarj_pin,LOW);
      motor_calis = true;
      
    }
    if(motor_calis){
      PWM_ayarla(PWM_baslangic_deger);     // Setup starting PWM with duty cycle = PWM_START_DUTY
      
      motor_ilk_baslama();
      
      motor_speed = PWM_baslangic_deger;
      ACSR |= 0x08;                    // Enable analog comparator interrupt  
      while(motor_calis){
        verileri_duzenle();
        if(ilk_defa_tork_modu and tork_modu){
          ACSR |= 0x08;
          ilk_defa_tork_modu = false;
        }
        
        gaz_seviyesi = constrain(gaz_seviyesi,gaz_min_seviyesi,gaz_maks_seviyesi);
        gaz_seviye_tersi = map(gaz_seviyesi,gaz_min_seviyesi,gaz_maks_seviyesi,gaz_maks_seviyesi,gaz_min_seviyesi);
        motor_speed = map(gaz_seviyesi,gaz_min_seviyesi,gaz_maks_seviyesi,PWM_min_deger,PWM_maks_deger);
        PWM_ayarla(motor_speed);
        if(!tork_modu){
          ilk_defa_tork_modu = true;
          if(micros() - eski_zaman >= (gaz_seviye_tersi*10)){
            adimlar();
            siradaki_adim += yon;
            if(siradaki_adim < 0) siradaki_adim = 5;
            siradaki_adim %= 6;
            eski_zaman = micros();
          }
        }
        if(gaz_seviyesi < (gaz_min_seviyesi + 30)){
          if(motor_kapatma_sayaci > 10000){
            motor_calis = false;
            motor_bosta();
          }
          motor_kapatma_sayaci = motor_kapatma_sayaci + 1;       
        }
      }
    }
    
      
  }
}
