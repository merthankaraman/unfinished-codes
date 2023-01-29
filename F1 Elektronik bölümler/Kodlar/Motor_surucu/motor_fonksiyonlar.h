
void motor_bosta(){
  siradaki_adim = 0;
  ACSR   = 0x10;            // Disable and clear (flag bit) analog comparator interrupt
  TCCR2A =  0;
  TCCR1A =  0;
  PORTD  = B00000000;            //pins 0 to 7 set to LOW //stop everything    
  PORTB  = B00000000;           //B00110001    D9, D10 and D11 to LOW    
}
void motor_pinler(){
  DDRD  |= dusukpinler; //Fazların düşük pinleri çıkış ayarlandı
  PORTD  = 0;
  DDRB  |= yuksekpinler; //Fazların yüksek pinleri çıkış ayarlandı
  PORTB  &= !(yuksekpinler + pow(2,(13 - 8)));          //B01110001    D9, D10 and D11 to LOW
  // Timer1 module setting: set clock source to clkI/O / 1 (no prescaling)
  TCCR1A = 0;
  TCCR1B = 0x01;
  // Timer2 module setting: set clock source to clkI/O / 1 (no prescaling)
  TCCR2A = 0;
  TCCR2B = 0x01;
  // Analog comparator setting
  ACSR   = 0x10;           // Disable and clear (flag bit) analog comparator interrupt
  //Set D8 (PWM in) to trigger interrupt
  PCICR |= (1 << PCIE0);    //enable PCMSK0 scan                                                 
  PCMSK0 |= (1 << PCINT0);  //Set pin D8 trigger an interrupt on state change. 
  PCMSK0 |= (1 << PCINT1);  //Set pin D12 trigger an interrupt on state change. 
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
  PORTD = B00010000;      //Set D4 to HIGH and the rest to LOW
  TCCR2A =  0;            //OC2A - D11 normal port. 
  TCCR1A =  0x81;         //OC1A - D9 compare match noninverting mode, downcounting ,PWM 8-bit
}
//D9 PWM and D3 HIGH
void AH_CL(){
  PORTD = B00001000;      //Set D3 to HIGH and the rest to LOW
  TCCR2A =  0;            //OC2A - D11 normal port. 
  TCCR1A =  0x81;         //OC1A - D9 compare match noninverting mode, downcounting ,PWM 8-bit  
}
//D10 PWM and D3 HIGH
void BH_CL(){
  PORTD = B00001000;      //Set D3 to HIGH and the rest to LOW
  TCCR2A =  0;            //OC2A - D11 normal port. 
  TCCR1A =  0x21;         //OC1B - D10 compare match noninverting mode, downcounting ,PWM 8-bit 
}
//D10 PWM and D5 HIGH
void BH_AL(){  
  PORTD = B00100000;      //Set D5 to HIGH and the rest to LOW
  TCCR2A =  0;            // OC2A - D11 normal port. 
  TCCR1A =  0x21;         //OC1B - D10 compare match noninverting mode, downcounting ,PWM 8-bit 
}
//D11 PWM and D5 HIGH
void CH_AL(){ 
  PORTD = B00100000;      //Set D5 to HIGH and the rest to LOW
  TCCR1A =  0;            // OC1A and OC1B normal port
  TCCR2A =  0x81;         // OC2A - D11 compare match noninverting mode, downcounting ,PWM 8-bit  
}
//D11 PWM and D4 HIGH
void CH_BL(){  
  PORTD = B00010000;      //Set D5 to HIGH and the rest to LOW
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

 
void PWM_ayarla(byte genlik){
  if(genlik < PWM_min_deger)
    genlik  = PWM_min_deger;
  if(genlik > PWM_maks_deger)
    genlik  = PWM_maks_deger;
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
  // Motor start
  while(i > 500) {
    delayMicroseconds(i);
    adimlar();
    siradaki_adim += yon;
    if(siradaki_adim < 0) siradaki_adim = 5;
    siradaki_adim %= 6;
    i -= 10;
  }
}

//This is the interruption routine
//----------------------------------------------

ISR(PCINT0_vect){
  //First we take the current count value in micro seconds using the micros() function
  guncel_zaman = micros();
  ///////////////////////////////////////Channel 1
  if(PINB & B00000001){                              //We make an AND with the pin state register, We verify if pin 8 is HIGH???
    if(d8_son_durum == 0){                         //If the last state was 0, then we have a state change...
      d8_son_durum = 1;                            //Store the current state into the last state for the next loop
      sayici_1 = guncel_zaman;                     //Set counter_1 to current value.
    }
  }
  else if(d8_son_durum == 1){                      //If pin 8 is LOW and the last state was HIGH then we have a state change      
    d8_son_durum = 0;                              //Store the current state into the last state for the next loop
    gaz_seviyesi = guncel_zaman - sayici_1;           //We make the time difference. Channel 1 is current_time - timer_1.
  }
  if(PINB & B00010000){                              //We make an AND with the pin state register, We verify if pin 12 is HIGH???
    if(d12_son_durum == 0){                         //If the last state was 0, then we have a state change...
      d12_son_durum = 1;                            //Store the current state into the last state for the next loop
      sayici_2 = guncel_zaman;                     //Set counter_2 to current value.
    }
  }
  else if(d12_son_durum == 1){                      //If pin 8 is LOW and the last state was HIGH then we have a state change      
    d12_son_durum = 0;                              //Store the current state into the last state for the next loop
    fren_seviyesi = guncel_zaman - sayici_2;           //We make the time difference. Channel 2 is current_time - timer_1.
  }

}

// The ISR vector of the Analog comparator
ISR (ANALOG_COMP_vect) {
  for(i = 0; i < 10; i++) {           //We check the comparator output 10 times to be sure
    if(siradaki_adim & 1)             //If step = odd (0001, 0011, 0101) 1, 3 or 5
    {
      if(!(ACSR & B00100000)) i -= 1; //!B00100000 -> B11011111 ACO = 0 (Analog Comparator Output = 0)
    }
    else                              //else if step is 0, 2 or 4
    {
      if((ACSR & B00100000))  i -= 1; //else if B00100000 -> B11011111 ACO = 1 (Analog Comparator Output = 1)
    }
  }
  adimlar();                    //set the next step of the sequence
  siradaki_adim += yon;                    //increment step by 1, next part of the sequence of 6
  if(siradaki_adim < 0) siradaki_adim = 5;
  siradaki_adim %= 6;                 //If step > 5 (equal to 6) then step = 0 and start over
}
