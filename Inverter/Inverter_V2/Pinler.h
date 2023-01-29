#define faza_H 13//5
#define faza_L 7

#define fazb_H 6
#define fazb_L 8

#define pot_pin A0

int frekans_sabit = 60, frekans_min = 0;//, frekans;
long frekans_maks = 200, frekans;
float periyot = 0;

void kurulum_ayarlari(){
  pinMode(faza_H,OUTPUT);
  pinMode(faza_L,OUTPUT);
  digitalWrite(faza_H,LOW);
  digitalWrite(faza_L,LOW);
  
  pinMode(fazb_H,OUTPUT);
  pinMode(fazb_L,OUTPUT);
  digitalWrite(fazb_H,LOW);
  digitalWrite(fazb_L,LOW);

}
void ekrana_yazdir(){
  Serial.print("Frekans: "); Serial.print(frekans); 
  Serial.print("\t\tperiyot: "); Serial.println(periyot,6);
}

void verileri_al(){
  frekans = map(analogRead(pot_pin),0,1023,frekans_min,frekans_maks);
  //frekans = constrain(frekans,0,frekans_maks);
  periyot = (1000.0/frekans); 
}

void portlari_temizle(){
  digitalWrite(faza_H,LOW); digitalWrite(faza_L,LOW); digitalWrite(fazb_H,LOW); digitalWrite(fazb_L,LOW);
}
