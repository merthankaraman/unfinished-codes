boolean h_koprusu = false;

unsigned long yeni_zaman=0, eski_zaman=0;
int siradaki_adim = 0;

void kare_adim(){
  portlari_temizle();
  switch(siradaki_adim){
    case 0:
      digitalWrite(faza_H, HIGH); 
      if(h_koprusu) { digitalWrite(fazb_L, HIGH);}
      break;
    case 1:
      digitalWrite(fazb_H, HIGH); 
      if(h_koprusu) { digitalWrite(faza_L, HIGH);}
      break;
  }

  
}
void kare_dalga_olustur(){
  verileri_al();
  yeni_zaman = millis();
  if(yeni_zaman - eski_zaman >= periyot/2.0){
    eski_zaman = yeni_zaman;
    kare_adim();
    siradaki_adim++;
    siradaki_adim %= 2;
  }
  
}
