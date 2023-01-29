
/* PWM in pin - D8
 * High A - D9
 * LOW A - D5
 * HIGH B - D10
 * LOW B - D4
 * HIGH C - D11
 * LOW C - D3
 * Comparator - D6
 * Fren kontrol - D7
 * FAZ A Karşılaştırıcı - A2
 * FAZ B Karşılaştırıcı - A1
 * FAZ C Karşılaştırıcı - A0
*/

#define pwm_giris_pin 8
#define fren_giris_pin 12

#define a_yuksek_pin 9
#define a_dusuk_pin 5

#define b_yuksek_pin 10
#define b_dusuk_pin 4

#define c_yuksek_pin 11
#define c_dusuk_pin 3

#define yuksekpinler int(pow(2,a_yuksek_pin-8) + pow(2,b_yuksek_pin-8) + pow(2,c_yuksek_pin-8))
#define dusukpinler int(pow(2,a_dusuk_pin) + pow(2,b_dusuk_pin) + pow(2,c_dusuk_pin))

float gaz_seviyesi= 0, gaz_seviye_tersi = 0, gaz_maks_seviyesi = 2000, gaz_min_seviyesi = 1000, fren_seviyesi = 0;
boolean tam_gaz = 0, tam_fren = 0;

int siradaki_adim = 0, yon = 1;

unsigned long guncel_zaman=0, sayici_1 = 0, sayici_2 = 0, eski_zaman = 0;

boolean tork_modu = true, ilk_defa_tork_modu = true, frende_sarj_modu = true, sensor_durum = false, ters_ema = true, motor_calis = false;
int tork_disi_guc = 255;

#define PWM_maks_deger     255
#define PWM_min_deger      35
#define PWM_baslangic_deger    35


//int PWM_IN_MAX = 2000;
//int PWM_IN_MIN = 1000;
byte motor_speed;
unsigned int i;
byte d8_son_durum, d12_son_durum;
int motor_kapatma_sayaci = 0;
