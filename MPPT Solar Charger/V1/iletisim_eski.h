#include <SoftwareSerial.h>
#include <ArduinoJson.h>

String mesaj = "";
bool mesaj_hazir = false;


#define rx 2
#define tx 3

#define wifi_ad "KARAMAN_2.4GHz_plus"
#define wifi_sifre ""


SoftwareSerial espserial(rx, tx);

void iletisim_setup(){
  espserial.begin(74880);
}

/*void seri_port_loop(){
  Serial.print("PV:"); Serial.print(solar_V); Serial.print("V;"); Serial.print(solar_A); Serial.print("A;"); Serial.print(solar_W); Serial.println("W");
  Serial.print("RT:"); Serial.print(ruzgar_V); Serial.print("V;"); Serial.print(ruzgar_A); Serial.print("A;"); Serial.print(ruzgar_W); Serial.println("W");
  Serial.print("Bat:"); Serial.print(cikis_V); Serial.print("V;"); Serial.print(cikis_A); Serial.print("A;"); Serial.print(cikis_W); Serial.println("W");
  Serial.print("PWM:"); if(sarj_durumu == kapali) {Serial.println("0");} else Serial.println(pwm,DEC);
  Serial.print("Durum:"); Serial.println(sarj_durumu);
}*/

void seri_port_cevap(){
  while(Serial.available()){
    mesaj = Serial.readString();
    mesaj_hazir = true;
  }
  while(espserial.available()){
    mesaj = espserial.readString();
    mesaj_hazir = true;
  }
  if(mesaj_hazir > 0){
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc,mesaj);
    if(error){
      Serial.print(F("hata"));
      Serial.println(error.c_str());
      mesaj_hazir = false;
      return;
    }
    if(doc["SP"] == "istek"){
      doc["SP"] = "Cevap";
      doc["V"] = solar_V; doc["A"] = solar_A; doc["W"] = solar_W;
      serializeJson(doc,espserial);
      serializeJson(doc,Serial);
    }
    else if(doc["RT"] == "istek"){
      doc["RT"] = "Cevap";
      doc["V"] = ruzgar_V; doc["A"] = ruzgar_A; doc["W"] = ruzgar_W;
      serializeJson(doc,espserial);
      serializeJson(doc,Serial);
    }
    else if(doc["BT"] == "istek"){
      doc["BT"] = "Cevap";
      doc["V"] = cikis_V; doc["A"] = cikis_A; doc["W"] = cikis_W;
      serializeJson(doc,espserial);
      serializeJson(doc,Serial);
    }
    else if(doc["DR"] == "istek"){
      doc["DR"] = "Cevap";
      int pwm_durum;
      sarj_durumu ? pwm_durum = pwm :pwm_durum = 0;
      doc["PWM"] = pwm_durum; doc["D"] = sarj_durumu;
      serializeJson(doc,espserial);
      serializeJson(doc,Serial);
    }
    mesaj_hazir = false;
  }
}

void seri_port_istek(){
  
}

void seri_port_loop(){
  seri_port_cevap();
  seri_port_istek();
}
