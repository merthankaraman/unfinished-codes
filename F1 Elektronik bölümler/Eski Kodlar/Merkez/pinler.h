#define direksiyon_pin A0
#define gaz_pin A1
#define fren_pin A2
#define yon_pin 4
#define tork_modu_pin 5

void pinler_setup(){
  pinMode(yon_pin,INPUT);
  pinMode(tork_modu_pin,INPUT);
}
