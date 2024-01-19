// TCS230 or TCS3200 pins wiring to Arduino
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
#define pb 9

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int r[55];
int g[55];
int b[55];
bool tampilkan = 0;
int test = 0;

void setup() {
  for (int i = 0; i < 56; i++) {
    r[i] = 0;
    g[i] = 0;
    b[i] = 0;
  }
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
}
void loop() {
  if (digitalRead(pb) == LOW){
    tampilkan = 0;
    // Setting RED (R) filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);
    
    // Reading the output frequency
    redFrequency = pulseIn(sensorOut, LOW);
    r[redFrequency]++;
    
    // Printing the RED (R) value
    Serial.print("R = ");
    Serial.print(redFrequency);
    delay(100);
    
    // Setting GREEN (G) filtered photodiodes to be read
    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);
    
    // Reading the output frequency
    greenFrequency = pulseIn(sensorOut, LOW);
    g[greenFrequency]++;

    // Printing the GREEN (G) value  
    Serial.print(" G = ");
    Serial.print(greenFrequency);
    delay(100);
  
    // Setting BLUE (B) filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
    
    // Reading the output frequency
    blueFrequency = pulseIn(sensorOut, LOW);
    b[blueFrequency]++;
    // Printing the BLUE (B) value 
    Serial.print(" B = ");
    Serial.println(blueFrequency);
    test++;
    delay(50);
  } else {
    if (!tampilkan){
      Serial.print("\n----------------------------\n");
      Serial.println("Jumlah Tes = "+String(test)+"\n");
      test = 0;
      Serial.print("R = ");
      for (int i = 0; i < sizeof(r) / sizeof(r[0]); ++i) {
        if (r[i] > 0) {
          Serial.print(i);
          Serial.print("("+String(r[i])+")");
          Serial.print(",  ");
        }
      }
      Serial.println(" ");
      Serial.print("G = ");
      for (int i = 0; i < sizeof(g) / sizeof(g[0]); ++i) {
        if (g[i] > 0) {
          Serial.print(i);
          Serial.print("("+String(g[i])+")");
          Serial.print(",  ");
        }
      }
      Serial.println(" ");
      Serial.print("B = ");
      for (int i = 0; i < sizeof(b) / sizeof(b[0]); ++i) {
        if (b[i] > 0) {
          Serial.print(i);
          Serial.print("("+String(b[i])+")");
          Serial.print(",  ");
        }
      }
      Serial.print("\n----------------------------\n");
      for (int i = 0; i < 56; i++) {
        r[i] = 0;
        g[i] = 0;
        b[i] = 0;
      }
      tampilkan = 1;
    }
    
  }
}
