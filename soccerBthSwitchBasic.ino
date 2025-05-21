#include "BluetoothSerial.h"

#define LED_PIN     5
#define NUM_LEDS    8
#define mtrA01      17
#define mtrA02      12
#define mtrB01      18
#define mtrB02      19
#define buzzer      25  
#define lampu       15
#define bttnA       26
#define bttnB       32

BluetoothSerial my_bluetooth;
const char* nama_bluetooth = "FoosBall KKSJ1";


void setup() {

//-- Motor KIRI
pinMode(mtrA01, OUTPUT);
pinMode(mtrA02, OUTPUT);
//-- Motor Kanan  F
pinMode(18, OUTPUT);
pinMode(mtrB02, OUTPUT);
pinMode(buzzer, OUTPUT);

pinMode(bttnA, INPUT);
pinMode(bttnB, INPUT);
 
Serial.begin(115200);
delay(100);

my_bluetooth.begin(nama_bluetooth);

}

void loop() {

int butangA = digitalRead(bttnA);
int butangB = digitalRead(bttnB);

Serial.println(bttnA);
Serial.println(bttnB);


if(my_bluetooth.available()> 0){
    //char dat = Serial.read();
    char dat = my_bluetooth.read();
    Serial.println(dat);
    
    if (dat=='B'){
      digitalWrite(mtrA01,HIGH);
      digitalWrite(mtrA02,LOW);
      digitalWrite(mtrB01,LOW);
      digitalWrite(mtrB02,HIGH);
      Serial.println(" Motor Gerak ke UNDUR");
    }
    
    if (dat=='F'){
      digitalWrite(mtrA01,LOW);
      digitalWrite(mtrA02,HIGH);
      digitalWrite(mtrB01,HIGH);
      digitalWrite(mtrB02,LOW);
      Serial.println(" Motor Gerak ke DEPAN ");
    }
    
    if (dat=='S'){
      digitalWrite(mtrA01,LOW);
      digitalWrite(mtrA02,LOW);
      digitalWrite(mtrB01,LOW);
      digitalWrite(mtrB02,LOW);
      Serial.println(" Motor HENTI");
    }

    else if (dat=='R'){
      digitalWrite(mtrA01,LOW);
      digitalWrite(mtrA02,HIGH);
      digitalWrite(mtrB01,LOW);
      digitalWrite(mtrB02,HIGH);
      Serial.println(" Motor Gerak ke KIRI");
    }

    else if (dat=='L'){
      digitalWrite(mtrA01,HIGH);
      digitalWrite(mtrA02,LOW);
      digitalWrite(mtrB01,HIGH);
      digitalWrite(mtrB02,LOW);
      Serial.println(" Motor Gerak ke KANAN");
    }
  }
}
