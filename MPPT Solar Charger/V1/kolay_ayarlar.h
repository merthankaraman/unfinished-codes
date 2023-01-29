                       //Batarya min Batarya maks Batarya float
int pil[pil_tur_sayisi][3] = {{11.0,14.1,13.6}};

void kolay_setup(){
  min_solar_W = 1.0, dusuk_solar_W = 5.0, min_ruzgar_W = 0;          
  pil_turu = 0;//12aku 24aku 36aku 1sli-ion
}

void pil_secimi(){
  
  min_cikis_V = pil[pil_turu][0];
  maks_cikis_V = pil[pil_turu][1];
  cikis_float_V = pil[pil_turu][2];

}
