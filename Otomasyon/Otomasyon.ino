//#include <IRremote.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

String kullanici_adi = "Merthan Karaman";
int SDA_pin = 10, SCK_pin = 13, MOSI_pin = 11, MISO_pin = 12, RST_pin = 9, kart_gosterme=0;
MFRC522 kart_okuyucu(SDA_pin, RST_pin);
#define veri_boyut 3
int dogruluk=0,kart_veritabani[veri_boyut][4] = {{103,131,227,770}};

#define sicaklik_pin A0   
 //  LM35DZ Yazi on 5V Analog GND  \\

#define role_pin 2
int role_durum=0;

/*#define kizilotesi_pin 3 // X onde Sinyal GND 5V  \\

IRrecv kizilotesi(kizilotesi_pin);
decode_results kizilotesi_veriler;*/

LiquidCrystal_I2C ekran(0x27,16,2); //SDA A4 SCL A5 \\


#define pot_pin A1
int menu_sayisi = 3,pot_deger,secilen_menu,eski_secilen_menu=-2;

unsigned long eski_zaman,simdiki_zaman;
bool ilk_sefer = true;

char secim;


void setup() {
  Serial.begin(9600);
  ekran.init();
  ekran.backlight();
  //kizilotesi.enableIRIn();
  SPI.begin();
  kart_okuyucu.PCD_Init();
  pinMode(role_pin,OUTPUT);
  digitalWrite(role_pin,LOW);
  ekran.clear(); ekran.print("Lutfen Kart"); ekran.setCursor(7,1); ekran.print("Okutun");
  Serial.println("Lutfen Kart Okutun");

}
int kart_okuma(){
  if ( ! kart_okuyucu.PICC_IsNewCardPresent()){
    return 0;
  }
  if ( ! kart_okuyucu.PICC_ReadCardSerial()){
    return 0;
  }
  if(kart_gosterme >0){
    Serial.println("Kart kodu: ");
    for(int i=0;i<=4;i++){
      Serial.print(kart_okuyucu.uid.uidByte[i]); if(i<3)Serial.print(",");
    }
    Serial.print("\n");
  }
  for(int i=0;i<=veri_boyut;i++){
    dogruluk=0;
    for(int j=0;j<=4;j++){
      if(kart_okuyucu.uid.uidByte[j] == kart_veritabani[i][j]){
        dogruluk++;
      }
      if(dogruluk==4){
        //kart_gosterme=1;
        return 1;
      }
    }
  }
  kart_okuyucu.PICC_HaltA();
  return 0;
}

int zaman_tut(int sure){
  simdiki_zaman = millis();
  if(ilk_sefer == true){
    eski_zaman = simdiki_zaman;
    ilk_sefer = false;
  }
  if(simdiki_zaman - eski_zaman < sure){
    if(simdiki_zaman % 500 > 0 && simdiki_zaman % 500 < 300){
      if(kart_okuma() >0){
        ilk_sefer = true;
        return 1;
      }
    }
    
  }
  else{
    if(kart_okuma() >0){
      ilk_sefer = true;
      return 1;
    }
    ilk_sefer = true;}
  return 0;
  
}
void sicaklik_okuma(){
  float sicaklik = analogRead(sicaklik_pin)*0.48875;
  Serial.print(sicaklik); Serial.println(" C"); ekran.clear(); ekran.print("Sicaklik"); ekran.setCursor(0,1); ekran.print(sicaklik); ekran.print(" C"); delay(2000);
}
void role_degistirme(){
  if(role_durum == 0){
    role_durum=1;
    digitalWrite(role_pin,HIGH);
  }
  else{
    role_durum=0;
    digitalWrite(role_pin,LOW);
  }
}
int pot_okuma(){
  pot_deger = map(analogRead(pot_pin),0,1023,0,menu_sayisi+1); if(pot_deger ==menu_sayisi+1) pot_deger=menu_sayisi;
  return pot_deger;
}
void birkez_calis(){
  
}
void ekran_yazdir(){
  secilen_menu = pot_okuma();
  if(eski_secilen_menu != secilen_menu){
    ekran.clear();
  }
  eski_secilen_menu = secilen_menu;
  
  if(secilen_menu == 0){
    ekran.print("Ana Menu");
    if(zaman_tut(2000)){
      return 0;
    }
  }
  else if(secilen_menu == 1){
    ekran.print("Isik kontrolu");
    if(zaman_tut(2000)){
      role_degistirme();
      return 0;
    }
  }
  else if(secilen_menu == 2){
    ekran.print("Sicaklik");
    if(zaman_tut(2000)){
      sicaklik_okuma();
      return 0;
    }
  }
   ekran.setCursor(0,1); ekran.print("icin kart okutun"); delay(500);
   return secilen_menu;
}
void seri_yazdir(){
  Serial.println("Isik kontrolu icin 1'i tuslayin");
  Serial.println("Sicaklik bilgisi icin 2'i tuslayin");
  secim = (Serial.read());
  if(secim == '1'){
    Serial.println("Isik kontrolu");
    role_degistirme();
  }
  else if(secim == '2'){
    sicaklik_okuma();
  }
  
}

void loop() {


  if(kart_okuma()){
    ekran.clear(); ekran.print("   Hosgeldiniz"); Serial.print("Hosgeldiniz "); ekran.setCursor(0,1); ekran.print(kullanici_adi);  Serial.println(kullanici_adi);delay(1000);
    while(1){
      if(Serial.available()>0){
        seri_yazdir();
      }
      ekran_yazdir();
    }
  }

}
