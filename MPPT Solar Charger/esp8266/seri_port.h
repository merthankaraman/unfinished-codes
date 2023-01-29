#include <ArduinoJson.h>
//#include <SoftwareSerial.h>

#define rx 13
#define tx 12

//SoftwareSerial sof_seri;
void sof_serial_setup(){
  sof_seri.begin(74880, SWSERIAL_8N1, rx, tx, false);
}

bool mesaj_hazir = false, gonderildi = true, istek_gonderildi = false;
String mesaj = "";
unsigned long zaman = 0;
void seri_port_istek(){
  DynamicJsonDocument doc(512);
  
  if(not(istek_gonderildi)){
    doc["MQTT"] = "istek";
    //serializeJson(doc,sof_seri);
    serializeJson(doc,Serial);
    digitalWrite(LED_BUILTIN, LOW);
    istek_gonderildi = true;
    }
  if(mesaj_hazir){
    istek_gonderildi = false;
    digitalWrite(LED_BUILTIN, HIGH);
    DeserializationError error = deserializeJson(doc,mesaj);
    mesaj = "";
    istek_gonderildi = false;
    if(error){
      Serial.print(F("hata"));
      Serial.println(error.c_str());
      gonderildi = true;
      return;
    }
    gonderildi = doc["MQTT"];
    degerler[0][0] = doc["SP/V"]; degerler[0][1] = doc["SP/A"]; degerler[0][2] = doc["SP/W"];
    degerler[1][0] = doc["RT/V"]; degerler[1][1] = doc["RT/A"]; degerler[1][2] = doc["RT/W"];
    degerler[2][0] = doc["BT/V"]; degerler[2][1] = doc["BT/A"]; degerler[2][2] = doc["BT/W"];
    degerler[3][0] = doc["DR/PWM"]; degerler[3][1] = doc["DR/D"];
  }
  
}

/*void seri_port_cevap(){
  
}*/
char gecici_char;
unsigned long seri_zaman = 0;
void seri_port_loop(){
  //seri_port_cevap();
  if(Serial.available()){
      gecici_char = char(Serial.read());
      mesaj += gecici_char;
      mesaj_hazir = false;
      
  }
  if(not(sof_seri.available()) and gecici_char == '}'){
    //Serial.print("mesaj "); Serial.println(mesaj);
    gecici_char = ' ';
    mesaj_hazir = true;
    
  }
  if (millis() - seri_zaman > 2000 ) {
    seri_port_istek();
    seri_zaman = millis();
  }
}
