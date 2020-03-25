#include <EEPROM.h>
byte addr = 0;
byte val;
#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
byte  t;
float h;
byte sensorValue;
byte sensorValue2;

char comando;

void setup() {
  pinMode(12, OUTPUT);
  digitalWrite(12,LOW);
  pinMode(11, OUTPUT);
  digitalWrite(11,LOW);
  pinMode(10, OUTPUT);
  digitalWrite(10,LOW);
  pinMode(9, OUTPUT);
  digitalWrite(9,LOW);
  pinMode(8, OUTPUT);
  digitalWrite(8,LOW);
  pinMode(7, OUTPUT);
  digitalWrite(7,LOW);
  pinMode(6, OUTPUT);
  digitalWrite(6,LOW);
  pinMode(5, OUTPUT);
  digitalWrite(5,LOW);
  Serial.begin(115200);
  dht.begin();
  init_led();
}
    
void init_led() {
  for (byte j = 0; j < 4; j++) {
    digitalWrite((5 + j), EEPROM.read(j));
  }
  t = EEPROM.read(4);
  sensorValue = EEPROM.read(5);
  sensorValue2 = EEPROM.read(6);

   for(byte k = 7; k < 4; k++){
    digitalWrite((7 + k), EEPROM.read(k));
  }
}

void loop() {
  
    comando = Serial.read();

   sensorValue = analogRead(A0);
   sensorValue2 = analogRead(A1);

  t = dht.readTemperature();

   h = dht.readHumidity();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }


  switch (comando) {
    case '1' :
      if (digitalRead(9) == LOW) {
        digitalWrite(8, HIGH);
      } else {
        digitalWrite(8, HIGH);
        delay(1000);
        digitalWrite(8, LOW);
      }
      val = digitalRead(8);
      EEPROM.write(addr, val); delay(5);
      break;

    case '2' :
      digitalWrite(8, LOW);
      val = digitalRead(8);
      EEPROM.write(addr, val); delay(5);
      break;

    case '3' :
      if (digitalRead(10) == LOW) {
        digitalWrite(7, HIGH);
      } else {
        digitalWrite(7, HIGH);
        delay(1000);
        digitalWrite(7, LOW);
      }
      break;

    case '4' :
      digitalWrite(7, LOW);
      break;

    case '5' :
      if (digitalRead(11) == LOW) {
        digitalWrite(6, HIGH);
      } else {
        digitalWrite(6, HIGH);
        delay(1000);
        digitalWrite(6, LOW);
      }
      break;

    case '6' :
      digitalWrite(6, LOW);
      break;

    case '7' :
      if (digitalRead(12) == LOW) {
        digitalWrite(5, HIGH);
      } else {
        digitalWrite(5, HIGH);
        delay(1000);
        digitalWrite(5, LOW);
      }
      break;

    case '8' :
      digitalWrite(5, LOW);
      break;

    case 'a' :
      Serial.println(sensorValue);
      delay(1);
      break;

    case 'b' :
      Serial.print(t);
      Serial.print("*C");
      break;

    case 'c' :
      Serial.print(h);
      Serial.print("%");
      break;

    case 'd' :
      Serial.println(sensorValue2);
      delay(1);
      break;

    case 'e' :
      digitalWrite(9, HIGH);
      break;

    case 'f' :
      digitalWrite(9, LOW);
      break;

    case 'g' :
      digitalWrite(10, HIGH);
      break;

    case 'h' :
      digitalWrite(10, LOW);
      break;

    case 'i' :
      digitalWrite(11, HIGH);
      break;

    case 'l' :
      digitalWrite(11, LOW);
      break;

    case 'm' :
      digitalWrite(12, HIGH);
      break;

    case 'n' :
      digitalWrite(12, LOW);
      break;
    case 'p':
      memory();
      break;
    case 'z':
      readmemory();
      break; 
    case 'q':
      deletememory();
      break; 
  }
}

void memory() {
  for (byte j = 0; j < 4; j++) {
    EEPROM.write(j,digitalRead(5 + j));
  }
  EEPROM.write(4,t); 
  EEPROM.write(5,sensorValue);
  EEPROM.write(6,sensorValue2);
}

void readmemory(){
  for (byte j = 0; j < 4; j++) {
    Serial.print("Led");Serial.print(5+j);Serial.print(" = ");Serial.println(EEPROM.read(j));
  }
  
  Serial.print("Temp = ");Serial.print(EEPROM.read(4));Serial.println(" *C");
  Serial.print("Light = ");Serial.print(EEPROM.read(5));Serial.println("");
  Serial.print("Water Sensor = ");Serial.print(EEPROM.read(6));
}

void deletememory(){
  for (byte j = 0; j < 4; j++) {
    EEPROM.write(j,0);
  }
  EEPROM.write(4,0); 
  EEPROM.write(5,0);
  EEPROM.write(6,0);
}
