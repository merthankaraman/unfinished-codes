
void motor_bosta(){
  siradaki_adim = 0;
  ACSR   = 0x10;            // Disable and clear (flag bit) analog comparator interrupt
  TCCR2A =  0;
  TCCR1A =  0;
  PORTD  = 0;  //D portu sıfırlandı  
  PORTB  &= !(a_yuksek_pin + b_yuksek_pin + c_yuksek_pin);  //B portu sıfırlandı
}
void motor_pinler(){
  DDRD  |= a_dusuk_pin + b_dusuk_pin + c_dusuk_pin; //Fazların düşük pinleri çıkış ayarlandı
  PORTD  = 0;
  DDRB  |= a_yuksek_pin + b_yuksek_pin + c_yuksek_pin; //Fazların yüksek pinleri çıkış ayarlandı
  PORTB  &= !(a_yuksek_pin + b_yuksek_pin + c_yuksek_pin);          //B01110001    D9, D10 and D11 to LOW
  // Timer1 module setting: set clock source to clkI/O / 1 (no prescaling)
  TCCR1A = 0;
  TCCR1B = 0x01; //bölme yok 1
  // Timer2 module setting: set clock source to clkI/O / 1 (no prescaling)
  TCCR2A = 0;
  TCCR2B = 0x01;
  // Analog comparator setting
  ACSR   = 0x10;           // Disable and clear (flag bit) analog comparator interrupt

  PCICR |= (1 << PCIE0);    //enable PCMSK0 scan                                                 
  PCMSK0 |= pwm_giris_pin + fren_giris_pin; //Fren ve gaz pinlerini kesme olarak tanımladık
}


void BEMF_A_RISING(){  
  ADCSRA = (0 << ADEN);     // Disable the ADC module
  ADCSRB = (1 << ACME);     // Enable MUX select for negative input of comparator
  ADMUX = 2;                // Select A2 as comparator negative input
  ACSR |= 0x03;             // Set interrupt on rising edge*/
}
void BEMF_A_FALLING(){
  ADCSRA = (0 << ADEN);     // Disable the ADC module
  ADCSRB = (1 << ACME);     // Enable MUX select for negative input of comparator
  ADMUX = 2;                // Select A2 as comparator negative input
  ACSR &= ~0x01;            // Set interrupt on falling edge*/
}
void BEMF_B_RISING(){
  ADCSRA = (0 << ADEN);     // Disable the ADC module
  ADCSRB = (1 << ACME);     // Enable MUX select for negative input of comparator
  ADMUX = 1;                // Select A1 as comparator negative input
  ACSR |= 0x03;             // Set interrupt on rising edge
}
void BEMF_B_FALLING(){
  ADCSRA = (0 << ADEN);     // Disable the ADC module
  ADCSRB = (1 << ACME);     // Enable MUX select for negative input of comparator
  ADMUX = 1;                // Select A1 as comparator negative input
  ACSR &= ~0x01;            // Set interrupt on falling edge*/
}
void BEMF_C_RISING(){
  ADCSRA = (0 << ADEN);     // Disable the ADC module
  ADCSRB = (1 << ACME);     // Enable MUX select for negative input of comparator
  ADMUX = 0;                // Select A0 as comparator negative input
  ACSR |= 0x03;             // Set interrupt on rising edge
}
void BEMF_C_FALLING(){
  ADCSRA = (0 << ADEN);     // Disable the ADC module
  ADCSRB = (1 << ACME);     // Enable MUX select for negative input of comparator
  ADMUX = 0;                // Select A0 as comparator negative input
  ACSR &= ~0x01;            // Set interrupt on falling edge*/
}

//D9 PWM and D4 HIGH.  
void AH_BL(){
  PORTD = b_dusuk_pin;      //Set D4 to HIGH and the rest to LOW
  TCCR2A =  0;            //OC2A - D11 normal port. 
  TCCR1A =  0x81;         //OC1A - D9 compare match noninverting mode, downcounting ,PWM 8-bit
}
//D9 PWM and D3 HIGH
void AH_CL(){
  PORTD = c_dusuk_pin;      //Set D3 to HIGH and the rest to LOW
  TCCR2A =  0;            //OC2A - D11 normal port. 
  TCCR1A =  0x81;         //OC1A - D9 compare match noninverting mode, downcounting ,PWM 8-bit  
}
//D10 PWM and D3 HIGH
void BH_CL(){
  PORTD = c_dusuk_pin;      //Set D3 to HIGH and the rest to LOW
  TCCR2A =  0;            //OC2A - D11 normal port. 
  TCCR1A =  0x21;         //OC1B - D10 compare match noninverting mode, downcounting ,PWM 8-bit 
}
//D10 PWM and D5 HIGH
void BH_AL(){  
  PORTD = a_dusuk_pin;      //Set D5 to HIGH and the rest to LOW
  TCCR2A =  0;            // OC2A - D11 normal port. 
  TCCR1A =  0x21;         //OC1B - D10 compare match noninverting mode, downcounting ,PWM 8-bit 
}
//D11 PWM and D5 HIGH
void CH_AL(){ 
  PORTD = a_dusuk_pin;      //Set D5 to HIGH and the rest to LOW
  TCCR1A =  0;            // OC1A and OC1B normal port
  TCCR2A =  0x81;         // OC2A - D11 compare match noninverting mode, downcounting ,PWM 8-bit  
}
//D11 PWM and D4 HIGH
void CH_BL(){  
  PORTD = b_dusuk_pin;      //Set D5 to HIGH and the rest to LOW
  TCCR1A =  0;            // OC1A and OC1B normal port
  TCCR2A =  0x81;         // OC2A - D11 compare match noninverting mode, downcounting ,PWM 8-bit
}

void adimlar(){        
  switch(siradaki_adim){
    case 0:
      AH_BL();
      BEMF_C_RISING();
      break;
    case 1:
      AH_CL();
      BEMF_B_FALLING();
      break;
    case 2:
      BH_CL();
      BEMF_A_RISING();
      break;
    case 3:
      BH_AL();
      BEMF_C_FALLING();
      break;
    case 4:
      CH_AL();
      BEMF_B_RISING();
      break;
    case 5:
      CH_BL();
      BEMF_A_FALLING();
      break;
  }
  if (!tork_modu){
    ACSR   = 0x10;            // Disable and clear (flag bit) analog comparator interrupt
  }
}


void PWM_ayarla(int genlik){
  if(genlik < pwm_min_deger)
    genlik  = pwm_min_deger;
  if(genlik > pwm_maks_deger)
    genlik  = pwm_maks_deger;
  if (tork_modu){
    OCR1A = genlik;                   // Set pin 9  PWM duty cycle
    OCR1B = genlik;                   // Set pin 10 PWM duty cycle
    OCR2A = genlik;                   // Set pin 11 PWM duty cycle
  }
  else{
    OCR1A = tork_disi_guc;
    OCR1B = tork_disi_guc;
    OCR2A = tork_disi_guc;
  }
}
void motor_ilk_baslama(){
  i = 2000;
  while(i > 500) {
    delayMicroseconds(i);
    adimlar();
    siradaki_adim += yon;
    if(siradaki_adim < 0) siradaki_adim = 5;
    siradaki_adim %= 6;
    i -= 10;
  }
}

// B portunun zaman kesicisi
ISR(PCINT0_vect){
  guncel_zaman = micros();
  if(PINB & pwm_giris_pin){
    if(pwm_giris_son_durum == 0){
      pwm_giris_son_durum = 1;
      sayici_1 = guncel_zaman;
    }
  }
  else if(pwm_giris_son_durum == 1){ 
    pwm_giris_son_durum = 0;
    
    gaz_seviyesi = guncel_zaman - sayici_1;
  }
  if(PINB & fren_giris_pin){
    if(fren_giris_son_durum == 0){
      fren_giris_son_durum = 1;
      sayici_2 = guncel_zaman;
    }
  }
  else if(fren_giris_son_durum == 1){ 
    fren_giris_son_durum = 0;
    fren_seviyesi = guncel_zaman - sayici_2;
  }

}

// The ISR vector of the Analog comparator
ISR (ANALOG_COMP_vect){
  for(i = 0; i < 10; i++){
    if(siradaki_adim & 1){
      if(!(ACSR & B00100000)) i -= 1;
    }
    else{
      if((ACSR & B00100000))  i -= 1;
    }
  }
  adimlar();
  siradaki_adim += yon;
  if(siradaki_adim < 0) siradaki_adim = 5;
  siradaki_adim %= 6;
}
