// zdefiniowanie wejść cyfrowych
const int Switch_S1 = 2;
const int Switch_S2 = 3;
const int Switch_S3 = 4;

//zdefiniowanie wyjść cyfrowych
const int Enable =  8;
const int DirLeft = 9;
const int DirRight = 10;

//inicjalizacja wartości początkowych
int S1_Previous = HIGH;
int S2_Previous = HIGH;
int S3_Previous = HIGH;
int EnableSts = LOW;
int DirLeftSts = LOW;
int DirRightSts = LOW;
int S1_Counter = 0;

void setup() {
  pinMode(Switch_S1, INPUT_PULLUP); //softwarowe "podciągniecie" do wysokiego potencjału
  pinMode(Switch_S2, INPUT_PULLUP);
  pinMode(Switch_S3, INPUT_PULLUP);
  pinMode(Enable, OUTPUT);
  pinMode(DirLeft, OUTPUT);
  pinMode(DirRight, OUTPUT);
  Serial.begin(9600);
}

void loop() {

//sprawdzenie stanów na wejściach cyfrowych
  int S1_Current = digitalRead(Switch_S1);
  delay(50);
  int S2_Current = digitalRead(Switch_S2);
  delay(50);
  int S3_Current = digitalRead(Switch_S3);
  delay(50);


  if (S1_Current == LOW && S1_Previous == HIGH) {


    if (EnableSts == LOW) {
      EnableSts = HIGH;
      DirLeftSts = LOW;
      DirRightSts = LOW;
      S1_Counter++;
      Serial.print("Liczba uruchomień :  ");
      Serial.println(S1_Counter);
    }
    else {
      EnableSts = LOW;
    }

  }

//obsługa obrotów w prawo
  if (S2_Current == LOW && S2_Previous == HIGH && EnableSts == HIGH) {
    if (DirRightSts == LOW) {

      DirLeftSts = LOW;
      delay(500);
      DirRightSts = HIGH;
    }
    else
      DirRightSts = LOW;

  }

//obsługa obrotów w lewo
  if (S3_Current == LOW && S3_Previous == HIGH && EnableSts == HIGH ) {
    if (DirLeftSts == LOW) {

      DirRightSts = LOW;
      delay(500);
      DirLeftSts = HIGH;
    }
    else
      DirLeftSts = LOW;
  }
  //ustawienie stanów na wyjściach cyfrowych
  digitalWrite(Enable, EnableSts);
  digitalWrite(DirLeft, DirLeftSts);
  digitalWrite(DirRight, DirRightSts);

  //przypisanie stanów poprzednich na pinach
  S1_Previous = S1_Current;
  S2_Previous = S2_Current;
  S3_Previous = S3_Current;
}
