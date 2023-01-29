#define voltaj_pil_1 A0 //Pillerin voltaj değerini okuma
#define voltaj_pil_2 A1
#define voltaj_pil_3 A2
#define voltaj_pil_4 A3
#define voltaj_pil_5 A4
#define voltaj_pil_6 A5

#define voltaj_pil_7 A6
#define voltaj_pil_8 A7
#define voltaj_pil_9 A8
#define voltaj_pil_10 A9
#define voltaj_pil_11 A10
#define voltaj_pil_12 A11

#define voltaj_pil_13 A12

#define sicaklik_pini_1 A13
#define sicaklik_pini_2 A14
#define sicaklik_pini_3 A15


#define pil_1_anahtar 2
#define pil_2_anahtar 3
#define pil_3_anahtar 4
#define pil_4_anahtar 5
#define pil_5_anahtar 6
#define pil_6_anahtar 7

#define pil_7_anahtar 8
#define pil_8_anahtar 9
#define pil_9_anahtar 10
#define pil_10_anahtar 11
#define pil_11_anahtar 12
#define pil_12_anahtar 14

#define pil_13_anahtar 15

#define guc_pini 13

void pinler(){
  pinMode(guc_pini,OUTPUT); digitalWrite(guc_pini,LOW);
  pinMode(pil_1_anahtar,OUTPUT); digitalWrite(pil_1_anahtar,LOW);
  pinMode(pil_2_anahtar,OUTPUT); digitalWrite(pil_2_anahtar,LOW);
  pinMode(pil_3_anahtar,OUTPUT); digitalWrite(pil_3_anahtar,LOW);
  pinMode(pil_4_anahtar,OUTPUT); digitalWrite(pil_4_anahtar,LOW);
  pinMode(pil_5_anahtar,OUTPUT); digitalWrite(pil_5_anahtar,LOW);
  pinMode(pil_6_anahtar,OUTPUT); digitalWrite(pil_6_anahtar,LOW);

  pinMode(pil_7_anahtar,OUTPUT); digitalWrite(pil_7_anahtar,LOW);
  pinMode(pil_8_anahtar,OUTPUT); digitalWrite(pil_8_anahtar,LOW);
  pinMode(pil_9_anahtar,OUTPUT); digitalWrite(pil_9_anahtar,LOW);
  pinMode(pil_10_anahtar,OUTPUT); digitalWrite(pil_10_anahtar,LOW);
  pinMode(pil_11_anahtar,OUTPUT); digitalWrite(pil_11_anahtar,LOW);
  pinMode(pil_12_anahtar,OUTPUT); digitalWrite(pil_12_anahtar,LOW);

  pinMode(pil_13_anahtar,OUTPUT); digitalWrite(pil_13_anahtar,LOW);
}
