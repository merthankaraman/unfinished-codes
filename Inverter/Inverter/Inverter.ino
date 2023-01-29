#define faza_H 8
#define faza_L 10

#define fazb_H 9
#define fazb_L 11

#define pot_pin A0
#define pot_aktif_pin 12
int frekans_sabit = 60, frekans_min = 1;//, frekans;
long frekans_maks = 200, frekans;
float periyot = 0;
unsigned long yeni_zaman=0, eski_zaman=0;

int siradaki_adim = 0;

boolean h_koprusu = true, h_koprusu_degisken = true;
#define kopru_jumper 12

void setup(){
  Serial.begin(9600);
  pinMode(faza_H,OUTPUT);
  pinMode(faza_L,OUTPUT);

  pinMode(fazb_H,OUTPUT);
  pinMode(fazb_L,OUTPUT);

  pinMode(pot_aktif_pin,INPUT);
  pinMode(kopru_jumper,INPUT);
}

void portlari_temizle(){
  digitalWrite(faza_H,LOW); digitalWrite(faza_L,LOW); digitalWrite(fazb_H,LOW); digitalWrite(fazb_L,LOW);
}
void adim(){
  portlari_temizle();
  switch(siradaki_adim){
    case 0:
      digitalWrite(faza_H, HIGH); 
      if(h_koprusu || h_koprusu_degisken) { digitalWrite(fazb_L, HIGH);}
      break;
    case 1:
      digitalWrite(fazb_H, HIGH); 
      if(h_koprusu || h_koprusu_degisken) { digitalWrite(faza_L, HIGH);}
      break;
  }
}

void calis(){
  yeni_zaman = millis();
  periyot = (1000.0/frekans);
  if(yeni_zaman - eski_zaman >= periyot/2.0){
    eski_zaman = yeni_zaman;
    adim();
    siradaki_adim++;
    siradaki_adim %= 2;
    //Serial.println(periyot);
  }
}
void girisleri_kontrol_et(){
  h_koprusu = digitalRead(kopru_jumper);
  if (digitalRead(pot_aktif_pin)){
    frekans = map(analogRead(pot_pin),0,1023,frekans_min,frekans_maks);
  }
  else if(!(digitalRead(pot_aktif_pin))){
    frekans = frekans_sabit;
  }
}

void loop(){
  girisleri_kontrol_et();
  calis();
  Serial.print("frekans "); Serial.print(frekans); Serial.print("\t\tperiyot: "); Serial.println(periyot,6);
}
