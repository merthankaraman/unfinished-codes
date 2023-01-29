#define gaz_pin A0
#define fren_pin A1


int gaz_seviyesi= 0, fren_seviyesi = 0, fren_az_sert= 1000, fren_fazla_sert=0, fazla_hiz = 0, az_hiz = 3000;
int yon = 1, tam_gaz = 0, tam_fren = 0;

void verileri_duzenle(){
  sensor_durum = digitalRead(sensor_pin);
  if((rpm_onceki_durum == LOW && sensor_durum == HIGH) && (rpm_oku == true)) {sensor_rpm++;  rpm_onceki_durum = HIGH; }
  else if ((rpm_onceki_durum == HIGH && sensor_durum == LOW) && (rpm_oku == true)){sensor_rpm++;  rpm_onceki_durum = LOW; }
  gaz_seviyesi = map(analogRead(gaz_pin),0,1023,az_hiz,fazla_hiz);
  if(gaz_seviyesi < fazla_hiz + 10) tam_gaz = 1;
  else tam_gaz = 0;
  fren_seviyesi = map(analogRead(fren_pin),0,1023,fren_az_sert,fren_fazla_sert);
  if(fren_seviyesi < fren_fazla_sert + 15) tam_fren = 1;
  else tam_fren = 0;
  yon = digitalRead(yon_pin);
  tork_modu = digitalRead(tork_modu_pin);
}
