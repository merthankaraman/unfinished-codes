#include "baglantilar.h"
#define derece 180/PI
#define radyan PI/180

float suanki_konum[3] = {}, x[3] = {}, y[3] = {}, z[3] = {};
float istenen_koordinat[3] = {};
float istenen_konum[3] = {};
float kol_1_mesafe = 100, kol_2_mesafe = 100, govde_yukseklik = 50;
int servo_1_sifirlama_payi, servo_2_sifirlama_payi, servo_3_sifirlama_payi;
int ek_x_mesafe, ek_y_mesafe, ek_z_mesafe;
float servo_1_istenen_aci, servo_2_istenen_aci, servo_3_istenen_aci;

void acidan_koordinat_yap(){
  x[0] = 0;
  y[0] = kol_1_mesafe * cos((servo_2_aci + servo_2_sifirlama_payi) * radyan); //Servo 3 dirsek konumu aynı zamanda
  z[0] = kol_1_mesafe * sin((servo_2_aci + servo_2_sifirlama_payi) * radyan);


  x[1] = 0;
  y[1] = kol_2_mesafe * cos((servo_3_aci + servo_3_sifirlama_payi) * radyan); //
  z[1] = kol_2_mesafe * sin((servo_3_aci + servo_3_sifirlama_payi) * radyan);

  suanki_konum[1] = (y[0] + y[1] + ek_y_mesafe) * sin((servo_1_aci + servo_1_sifirlama_payi) * radyan);
  suanki_konum[0] = (suanki_konum[1] + x[0] + x[1] + ek_x_mesafe) * cos((servo_1_aci + servo_1_sifirlama_payi) * radyan);
  suanki_konum[2] = govde_yukseklik + z[0] +z[1] + ek_z_mesafe;
  

}

void istenen_koordinata_acila(){
  servo_3_istenen_aci = atan((z[0] + govde_yukseklik + ek_z_mesafe - istenen_koordinat[2])/(y[0] - istenen_koordinat[1])) * derece;
  suanki_konum[1] += kol_2_mesafe * cos((servo_3_istenen_aci + servo_3_sifirlama_payi) * radyan);
  suanki_konum[2] += kol_2_mesafe * sin((servo_3_istenen_aci + servo_3_sifirlama_payi) * radyan);

  servo_2_istenen_aci = atan((0 - istenen_koordinat[2])/(suanki_konum[1] - istenen_koordinat[1])) * derece;
  suanki_konum[1] += kol_1_mesafe * cos((servo_2_istenen_aci + servo_2_sifirlama_payi) * radyan);
  suanki_konum[2] += kol_1_mesafe * sin((servo_2_istenen_aci + servo_2_sifirlama_payi) * radyan);

  servo_1_istenen_aci = atan((0 - istenen_koordinat[1])/(0 - istenen_koordinat[0])) * derece;
  suanki_konum[1] += suanki_konum[1] * cos((servo_1_istenen_aci + servo_1_sifirlama_payi) * radyan);
  suanki_konum[0] += suanki_konum[1] * cos((servo_1_aci + servo_1_sifirlama_payi) * radyan);

  servo_1_aci = servo_1_istenen_aci;
  servo_2_aci = servo_2_istenen_aci;
  servo_3_aci = servo_3_istenen_aci;
  
}
