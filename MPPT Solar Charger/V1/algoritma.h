#include "TimerOne.h"
#define pwm_full 1023
#define pwm_maks 100
int pwm_min = 60, pwm_baslangic = 90, pwm_artis = 1;
#define bir_saniye 5000

unsigned int seconds = 0;
unsigned int eski_saniye = 0;
unsigned int interrupt_counter = 0;
unsigned long time = 0;
int pwm = 0;

void callback(){
  if(interrupt_counter++ > bir_saniye){
    interrupt_counter = 0;
    seconds++;
  }
}

void algoritma_setup(){
  
  Timer1.initialize(20);
  Timer1.pwm(mosfet_pwm, 0);
  Timer1.attachInterrupt(callback);
  pwm = pwm_baslangic;
  
}

void pwm_ayarla(){
  if(pwm > pwm_maks){
    pwm = pwm_maks;
  }
  else if(pwm < pwm_min){
    pwm = pwm_min;
  }
  if (pwm < pwm_maks){
    Timer1.pwm(mosfet_pwm,(pwm_full * (long)pwm / 100), 20);
  }
  else if (pwm == pwm_maks){
    Timer1.pwm(mosfet_pwm, pwm_full - 1, 20);
  }
}
