#define solar_rolesi_pin 6
#define cikis_rolesi_pin 7
#define ruzgar_rolesi_pin 8

#define solar_volaj_pin A0
#define solar_akim_pin A1

#define ruzgar_volaj_pin A2
#define ruzgar_akim_pin A3

#define cikis_volaj_pin A4
#define cikis_akim_pin A5

#define mosfet_pwm 9
#define mosfet_digital 10

#define solar_kapat digitalWrite(solar_rolesi_pin,HIGH), solar_role_durum = false
#define solar_ac digitalWrite(solar_rolesi_pin,LOW), solar_role_durum = true;

boolean solar_role_durum = false, cikis_role_durum = false, ruzgar_role_durum = false;
void pinler_setup(){
  pinMode(solar_rolesi_pin,OUTPUT);
  digitalWrite(solar_rolesi_pin,LOW);
  
  pinMode(cikis_rolesi_pin,OUTPUT);
  digitalWrite(cikis_rolesi_pin,LOW);
  
  pinMode(ruzgar_rolesi_pin,OUTPUT);
  digitalWrite(ruzgar_rolesi_pin,LOW);

  pinMode(mosfet_digital,OUTPUT);
  digitalWrite(mosfet_digital,LOW);
}

const float direnc_ust = 22000.0, direnc_alt = 2200.0;
float voltaj_ref = 5.0;

float solar_V = 0, solar_A = 0, solar_W  = 0;
float ruzgar_V = 0, ruzgar_A = 0, ruzgar_W = 0;
float cikis_V = 0, cikis_A = 0, cikis_W = 0;

void degerleri_oku(){
  solar_V = analogRead(solar_volaj_pin) * (voltaj_ref/1023) * ((direnc_ust + direnc_alt) / direnc_alt);
  ruzgar_V = analogRead(solar_volaj_pin) * (voltaj_ref/1023) * ((direnc_ust + direnc_alt) / direnc_alt);
  cikis_V = analogRead(cikis_volaj_pin) * (voltaj_ref/1023) * ((direnc_ust + direnc_alt) / direnc_alt);

  solar_A = analogRead(solar_akim_pin) * (voltaj_ref/1023) * 0.185 - ((voltaj_ref / 2.0) * 0.185);
  ruzgar_A = analogRead(ruzgar_akim_pin) * (voltaj_ref/1023) * 0.185 - ((voltaj_ref / 2.0) * 0.185);
  cikis_A = analogRead(cikis_akim_pin) * (voltaj_ref/1023) * 0.185 - ((voltaj_ref / 2.0) * 0.185);

  solar_W = solar_V * solar_A;
  ruzgar_W = ruzgar_V * ruzgar_A;
  cikis_W = cikis_V * cikis_A;
}
