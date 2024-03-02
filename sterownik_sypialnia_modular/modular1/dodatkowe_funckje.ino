/*

void pomiar_napiecia(void){

  int odczytanaWartosc = 0;//Odczytana wartość z ADC
  float napiecie = 0;//Wartość przeliczona na napięcie w V


  odczytanaWartosc = analogRead(A5);//Odczytujemy wartość napięcia
  napiecie = odczytanaWartosc * (5.0/1024.0); //Przeliczenie wartości na napięcie
  Serial.println(napiecie);//Wysyłamy zmierzone napięcie
  delay(200);//Czekamy, aby wygodniej odczytywać wyniki  
}



void pomiar_napiecia_kanal(int kanal){

  int odczytanaWartosc = 0;//Odczytana wartość z ADC
  float napiecie = 0;//Wartość przeliczona na napięcie w V


  odczytanaWartosc = analogRead(kanal);//Odczytujemy wartość napięcia
  napiecie = odczytanaWartosc * (5.0/1024.0); //Przeliczenie wartości na napięcie
  Serial.println(napiecie);//Wysyłamy zmierzone napięcie
  delay(200);//Czekamy, aby wygodniej odczytywać wyniki  
}


*/