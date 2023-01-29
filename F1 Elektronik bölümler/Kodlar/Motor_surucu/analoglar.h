void verileri_duzenle(){
  yon = digitalRead(A4);
  yon ? yon = 1: yon = -1;
  tork_modu = digitalRead(A3);
  delayMicroseconds(10);
  if (tork_modu) digitalWrite(13,1);
  else digitalWrite(13,0);
}
