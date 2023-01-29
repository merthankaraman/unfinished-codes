#include <PubSubClient.h>


WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;


void callback(char* topic, byte* payload, unsigned int length) {
  
  String mqttmesaj = "";
  for (int i = 0; i < length; i++)
  {
    mqttmesaj = mqttmesaj + (char)payload[i];
  }
  Serial.print("topic: "); Serial.print(topic); Serial.print("\tmqttmesaj: "); Serial.println(mqttmesaj);
  if(topic == "pwm/min"){
    Serial.print("PWM min: "); Serial.println(mqttmesaj);
  }
}

void reconnect() {
  
  while (!client.connected()) {
    Serial.print("MQTT baglaniliyor...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str()), mqttUser, mqttPassword ) {
      Serial.println("baglandi");
    } else {
      Serial.print("basarisiz, rc=");
      Serial.print(client.state());
      delay(500);
    }
  }
}
void konular_gelen(){
  client.subscribe("pwm/min");
  client.subscribe("pwm/bas");
  client.subscribe("pwm/art");
  
  client.subscribe("pil/turusec");

  client.subscribe("cikis/min");
  client.subscribe("cikis/maks");
  client.subscribe("cikis/float");
}

void mqtt_setup() {
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  konular_gelen();
  /*for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      if((not(i == 1 and j == 1) and not(i == 1 and j == 2))){
        //Serial.print("i: "); Serial.print(i); Serial.print("\tj: "); Serial.println(j);
        client.subscribe(konular_gelen[i][j]);
      }
    }
  }*/
}
void konular_giden(){
  client.publish("SP/V", String(degerler[0][0]).c_str());
  client.publish("SP/A", String(degerler[0][1]).c_str());
  client.publish("SP/W", String(degerler[0][2]).c_str());

  client.publish("RT/V", String(degerler[1][0]).c_str());
  client.publish("RT/A", String(degerler[1][1]).c_str());
  client.publish("RT/W", String(degerler[1][2]).c_str());

  client.publish("BT/V", String(degerler[2][0]).c_str());
  client.publish("BT/A", String(degerler[2][1]).c_str());
  client.publish("BT/W", String(degerler[2][2]).c_str());

  client.publish("DR/pwm_durum", String(degerler[3][0]).c_str());
  client.publish("DR/sarj_durumu", String(degerler[3][1]).c_str());
}
unsigned long mqtt_eski_zaman = 0;

void mqtt_loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  //Serial.println("mqtt");
  if (millis() - mqtt_eski_zaman > 2000){
    konular_giden();
    //Serial.println("Gonderildi");
    //client.publish(konular_giden[0][0], String(degerler[0][0]).c_str());
    /*for(int i=0;i<4;i++){
      for(int j=0;j<3;j++){
        if (not(i == 3 and j == 2)){
          //Serial.print("i: "); Serial.print(i); Serial.print("\tj: "); Serial.println(j);
          client.publish(konular_giden[i][j], String(degerler[i][j]).c_str());
          //Serial.print(konular_giden[i][j]); Serial.print("\t"); Serial.println(degerler[i][j]);
        }
      }
    }*/
    mqtt_eski_zaman = millis();
  }
  
}
