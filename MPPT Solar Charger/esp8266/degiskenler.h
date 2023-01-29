const char* ssid =  "KARAMAN_2.4GHz_plus";
const char* password =  "K4R4M4N_61";


const char* mqttServer = "pi-sunucu.duckdns.org";
const int mqttPort = 1883;

const char* mqttUser = "esp8266mppt";
const char* mqttPassword = "12345";


//char* konular_giden[4][3] = {{"SP/V","SP/A","SP/W"}, {"RT/V","RT/A","RT/W"}, {"BT/V","BT/A","BT/W"}, {"DR/pwm_durum","DR/sarj_durumu"}};
//char* konular_giden[4][3] = {{{"SP/V"},{"SP/A"},{"SP/W"}}, {{"RT/V"},{"RT/A"},{"RT/W"}}, {{"BT/V"},{"BT/A"},{"BT/W"}}, {{"DR/pwm_durum"},{"DR/sarj_durumu"}}};
//char* konular_gelen[3][3] = {{"pwm/min","pwm/bas","pwm/art"},{"pil/turusec","",""},{"cikis/min","cikis/maks","cikis/float"}};
int adim = 0;


float degerler[4][3] = {};
int pwm_durum = 0;

String solarV, ruzgarV, cikisV;

enum sarj_modu {kapali, acik, bulk, batarya_float} sarj_durumu;
