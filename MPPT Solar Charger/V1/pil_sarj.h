float min_solar_W = 0, dusuk_solar_W = 0, min_ruzgar_W = 0, min_cikis_V = 0, maks_cikis_V = 0, cikis_float_V = 0, eski_solar_W = 0;
const int pil_tur_sayisi = 3;
int pil_turu = 0;

enum sarj_modu {kapali, acik, bulk, batarya_float} sarj_durumu;

void sarj_baslat(){
  
  static int kapali_sayaci = kapali;

  switch (sarj_durumu){
    case acik:                                        
      if (solar_W < min_solar_W){
        sarj_durumu = kapali;
        kapali_sayaci = kapali;
        solar_kapat;
      }
      else if (cikis_V > (cikis_float_V - 0.1)){
        sarj_durumu = batarya_float;
      }
      else if (solar_W < dusuk_solar_W){
        pwm = pwm_maks;
        pwm_ayarla();
      }
      else {                                          
        pwm = ((cikis_V * 10) / (solar_V / 10)) + 5;
        sarj_durumu = bulk;
      }
      break;
    case bulk:
      if (solar_W < min_solar_W){
        sarj_durumu = kapali;
        kapali_sayaci = kapali;
        solar_kapat;
      }
      else if (cikis_V > cikis_float_V){
        sarj_durumu = batarya_float;
      }
      else if (solar_W < dusuk_solar_W){
        sarj_durumu = acik;
        solar_ac;
      }
      else {
        if (eski_solar_W >= solar_W){
          pwm_artis = -pwm_artis;
        }
        pwm += pwm_artis;
        eski_solar_W = solar_W;
        pwm_ayarla();
      }
      break;
    case batarya_float:

      if (solar_W < min_solar_W){
        sarj_durumu = kapali;
        kapali_sayaci = kapali;
        solar_kapat;
        pwm_ayarla();       
      }
      else if (cikis_V > cikis_float_V){
        solar_kapat;
        pwm = pwm_maks;
        pwm_ayarla();
      }
      else if (cikis_V < cikis_float_V){
        pwm = pwm_maks;
        pwm_ayarla();
        solar_ac;    
        if (cikis_V < (cikis_float_V - 0.1)){
        sarj_durumu = bulk;
        }
      }
      break;
    case kapali:
      solar_kapat;
      if (kapali_sayaci > 0){
        kapali_sayaci--;
      }
      else if ((cikis_V > cikis_float_V) && (solar_V > cikis_V)){
        sarj_durumu = batarya_float;
        solar_ac;
      }
      else if ((cikis_V > min_cikis_V) && (cikis_V < cikis_float_V) && (solar_V > cikis_V)) {
        sarj_durumu = bulk;
        solar_ac;
      }
      break;
    default:
      solar_kapat; 
      break;
  }
}
