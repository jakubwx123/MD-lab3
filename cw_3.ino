

#define trigPin 11
#define echoPin 10
#include <Servo.h>

//Parametry regulatora PID
float Td=0.01;
float Ti=0.1;
float kp=0.4;

//sygnały 
float u=0; //wartość sygnału sterującego
float uchyb, uchyb_before;//uchyb , uchyb w chwili poprzedniej

float dystans_zadany=7;  // wartość w cm
float poz = 90;         // pozycja początkowa serwomechanizmu    
Servo serwomechanizm;

void setup() {

 Serial.begin (9600);
 pinMode(echoPin, INPUT); 
 pinMode(trigPin, OUTPUT); 
   serwomechanizm.attach(12); 
   serwomechanizm.write(poz); 
}


void loop() {


float dystans_aktual=dystans_SR04();
uchyb=dystans_zadany-dystans_aktual;
u=PID(uchyb,uchyb_before); //wartość sygnału sterujacego
uchyb_before=uchyb; //uchyb z biezacego cyku ustawiony uchybem z chwili poprzedniej

// Dane pomocnicze, informacyjne
 Serial.println("Dystans aktualny");
 Serial.println(dystans_aktual);
 Serial.println("Sterowanie");
 Serial.println(u);
 Serial.println("Pozycja");
 Serial.println(poz);
 Serial.println("Uchyb");
 Serial.println(uchyb);
 
poz=90+u*18;  //wartość przyblizona na bazie zaleznosci geometrycznych 
              // niedokładnosci wynikają z charakteru dzialania uzytego czujnika ultradzwiekowego
serwomechanizm.write(poz); 
delay(600);
}


 float dystans_SR04() {
  long czas;
  float dystans;
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  czas = pulseIn(echoPin, HIGH);
  //przeliczenie czasu trwania impulsu - nota katalogowa
  dystans = czas / 58;
  return dystans;
}

float PID(float e, float e_before)
{
float sterowanie = kp*(e + Td*(e - e_before)+Ti*(e +e_before)/2);
return sterowanie;
  }
