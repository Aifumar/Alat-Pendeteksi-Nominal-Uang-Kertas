#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
#define pb 9

SoftwareSerial mySerial(10, 11);

int rf = 0;
int gf = 0;
int bf = 0;
int p1, p2, p5, p10, p20, p50, p100 = 0;

void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(pb, INPUT_PULLUP);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
   // Begins serial communication 
  Serial.begin(9600);
  mySerial.begin (9600);
  mp3_set_serial (mySerial);
  delay(1);
	mp3_set_volume (30);
  mp3_play (1);
  Serial.println("Alat siap digunakan...");
}
void loop() {
  if (digitalRead(pb) == LOW){
    mp3_play (2);
    delay(1500);
    for (int n=1; n<20; n++){
      // Setting RED (R) filtered photodiodes to be read
      digitalWrite(S2,LOW);
      digitalWrite(S3,LOW);
      
      // Reading the output frequency
      rf = pulseIn(sensorOut, LOW);
      delay(50);
      
      // Setting GREEN (G) filtered photodiodes to be read
      digitalWrite(S2,HIGH);
      digitalWrite(S3,HIGH);
      
      // Reading the output frequency
      gf = pulseIn(sensorOut, LOW);
      delay(50);
    
      // Setting BLUE (B) filtered photodiodes to be read
      digitalWrite(S2,LOW);
      digitalWrite(S3,HIGH);
      
      // Reading the output frequency
      bf = pulseIn(sensorOut, LOW);
      if ((rf>=30 && rf<=36 && gf>=32 && gf<=39 && bf>=25 && bf<=28)||(rf>=35 && rf<=38 && gf>=37 && gf<=41 && bf>=29 && bf<=32)){
        Serial.print("Nominal Uang : Rp. 10.000");
        p10++;
      } else if ((rf>=25 && rf<=27 && gf>=32 && gf<=35 && bf>=38 && bf<=41)||(rf>=28 && rf<=31 && gf>=33 && gf<=38 && bf>=37 && bf<=42)){
        Serial.print("Nominal Uang : Rp. 5.000");
        p5++;
      } else if ((rf>=32 && rf<=34 && gf>=32 && gf<=35 && bf>=30 && bf<=32)||(rf>=30 && rf<=32 && gf>=31 && gf<=33 && bf>=29 && bf<=31)){
        Serial.print("Nominal Uang : Rp. 2.000");
        p2++;
      } else if ((rf>=26 && rf<=28 && gf>=28 && gf<=30 && bf>=31 && bf<=33)||(rf>=28 && rf<=31 && gf>=29 && gf<=31 && bf>=32 && bf<=34)){
        Serial.print("Nominal Uang : Rp. 1.000");
        p1++;
      } else if ((rf>=31 && rf<=36 && gf>=29 && gf<=33 && bf>=25 && bf<=28)||(rf>=31 && rf<=33 && gf>=28 && gf<=29 && bf>=24 && bf<=25)){
        Serial.print("Nominal Uang : Rp. 50.000");
        p50++;
      } else if ((rf>=29 && rf<=36 && gf>=27 && gf<=33 && bf>=27 && bf<=36)||(rf>=33 && rf<=38 && gf>=29 && gf<=34 && bf>=28 && bf<=33)){
        Serial.print("Nominal Uang : Rp. 20.000");
        p20++;
      } else if ((rf>=27 && rf<=32 && gf>=37 && gf<=44 && bf>=31 && bf<=39)||(rf>=27 && rf<=28 && gf>=36 && gf<=38 && bf>=30 && bf<=32)){
        Serial.print("Nominal Uang : Rp. 100.000");
        p100++;
      }  /*else if (rf>15 && rf<27 && gf>24 && gf<40 && bf>19 && bf<37){
        Serial.print("Nominal Uang : Rp. 100.000");
        p100++;
      }*/
      Serial.print (rf);
      Serial.print(" - ");
      Serial.print(gf);
      Serial.print(" - ");
      Serial.println(bf);
    }
    Serial.print("\nNominal Uang : ");
    if(p1>10 || p2>10 || p5>10 || p10>10 || p20>10 || p50>10 || p100>10){
      if(p1>p2 && p1>p5 && p1>p10 && p1>p20 && p1>p50 && p1>p100){
        Serial.println("Rp. 1000\n");
        mp3_play (3);
      } else if (p2>p1 && p2>p5 && p2>p10 && p2>p20 && p2>p50 && p2>p100){
        Serial.println("Rp. 2000\n");
        mp3_play (4);
      } else if (p5>p1 && p5>p2 && p5>p10 && p5>p20 && p5>p50 && p5>p100){
        Serial.println("Rp. 5000\n");
        mp3_play (5);
      } else if (p10>p1 && p10>p2 && p10>p5 && p10>p20 && p10>p50 && p10>p100){
        Serial.println("Rp. 10.000\n");
        mp3_play (6);
      } else if (p20>p1 && p20>p2 && p20>p5 && p20>p10 && p20>p50 && p20>p100){
        Serial.println("Rp. 20.000\n");
        mp3_play (7);
      } else if (p50>p1 && p50>p2 && p50>p5 && p50>p10 && p50>p20 && p50>p100){
        Serial.println("Rp. 50.000\n");
        mp3_play (8);
      } else if (p100>p1 && p100>p2 && p100>p5 && p100>p10 && p100>p20 && p100>p50){
        Serial.println("Rp. 100.000\n");
        mp3_play (9);
      } else {
        Serial.println("Tidak terdeteksi...");
      }
    } else {
      Serial.println("Tidak terdeteksi2...");
      mp3_play (10);
    }
    Serial.println("Selesai mendeteksi...");
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);
    p1 = 0; p2 = 0; p5 = 0; p10 = 0; p20 = 0; p50 = 0; p100 = 0;
    //delay(5000);
  }
  //Serial.println(".");
}
