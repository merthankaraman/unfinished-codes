//https://create.arduino.cc/projecthub/PSoC_Rocks/hacking-qualcomm-quick-charge-qc-2-0-3-0-with-attiny85-b7627d
//https://www.electroschematics.com/quick-charge-primer/
//QC 2.0
//12V D+ -> 0.6 D- -> 0.6
//9V  D+ -> 3.3 D- -> 0.6
//20V D+ -> 3.3 D- -> 3.3
//5V  D+ -> 0.6 D- -> 0
void QC_kurulum(){
    pinMode(Da_2k2, OUTPUT);
    pinMode(Da_10k, OUTPUT);
    digitalWrite(Da_2k2, LOW);
    digitalWrite(Da_10k, HIGH);
    delay(3000);
}

void QC_2.0(char voltaj){
  switch(voltaj){
    case 5:
      pinMode(Da_2k2, OUTPUT);
      pinMode(Da_10k, OUTPUT);
      digitalWrite(Da_10k, HIGH);
      digitalWrite(Da_2k2, LOW);
      pinMode(De_2k2, OUTPUT);
      pinMode(De_10k, OUTPUT);
      digitalWrite(De_2k2, LOW);
      digitalWrite(De_10k, LOW);
      break;
    case 9:
      pinMode(Da_2k2, OUTPUT);
      pinMode(Da_10k, OUTPUT);
      digitalWrite(Da_10k, HIGH);
      digitalWrite(Da_2k2, HIGH);
      pinMode(De_2k2, OUTPUT);
      pinMode(De_10k, OUTPUT);
      digitalWrite(De_2k2, LOW);
      digitalWrite(De_10k, HIGH);
      break;
    case 12:
      pinMode(Da_2k2, OUTPUT);
      pinMode(Da_10k, OUTPUT);
      pinMode(De_2k2, OUTPUT);
      pinMode(De_10k, OUTPUT);
      digitalWrite(De_2k2, LOW);
      digitalWrite(De_10k, HIGH);
      digitalWrite(Da_10k, HIGH);
      digitalWrite(Da_2k2, LOW);
      break;
    case 20:
      pinMode(Da_2k2, OUTPUT);
      pinMode(Da_10k, OUTPUT);
      digitalWrite(Da_10k, HIGH);
      digitalWrite(Da_2k2, HIGH);
      pinMode(De_2k2, OUTPUT);
      pinMode(De_10k, OUTPUT);
      digitalWrite(De_2k2, HIGH);
      digitalWrite(De_10k, HIGH);
  }
}
