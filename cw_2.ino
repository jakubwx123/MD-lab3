//Kalkulator

void setup(){
  Serial.begin(9600); //prędkość transmisji
  Serial.println("Kalkulator umozliwia dodawanie, odejmowanie, mnozenie i dzielenie liczb."); //jednorazowe wypisanie linii
}

void loop() {
  int a,b,wynik;
  char dzialanie;
  
  if(Serial.available() > 0) { 
    a = Serial.parseInt();        //wczytanie do zmiennej "a" pierwszej liczby w strumieniu danych 
    do {
      dzialanie = Serial.read();    //wczytanie do zmiennej "działanie" znaku działania
    } while(isWhitespace(dzialanie)); //zabezpieczenie przed wpisaniem przez użytkownika spacji przed znakiem działania
    b = Serial.parseInt();        //wczytanie do zmiennej "b" drugiej liczby w strumieniu danych
    Serial.print(a);
    Serial.print(dzialanie);
    Serial.print(b);          //wypisanie wczytanego działania

    delay(50);
    
  switch(dzialanie) {         //wykonanie działania
    case '+':
        wynik=a+b;
        Serial.print("=");
      Serial.print(wynik);
    break;
    case '-':
        wynik=a-b;
        Serial.print("=");
      Serial.print(wynik);
    break;
    case '*':
        wynik=a*b;
        Serial.print("=");
      Serial.print(wynik);
    break;
    case '/':
        if(b==0)
            Serial.print("      Nie dziel przez zero!!!");
        else {
            wynik=a/b;
            Serial.print("=");
        Serial.print(wynik);
            }
    break;
    default:
        Serial.print("    Nie ma takiego dzialania lub dzialanie jest nieobslugiwane!");
    break;
  }
    Serial.println();   //nowa linia
  }
      
  delay(100);
}
