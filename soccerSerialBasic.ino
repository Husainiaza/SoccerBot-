#include "BluetoothSerial.h"
#include <Adafruit_NeoPixel.h>

#define LED_PIN     15
#define NUM_LEDS    8
#define mtrA01      17
#define mtrA02      12
#define mtrB01      18
#define mtrB02      19
#define buzzer      33  
#define lampu       4

BluetoothSerial my_bluetooth;
const char* nama_bluetooth = "KKSJ-01";

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Variables
  int i=0;
  int j=0;
  int state;
  int vSpeed=200;

void setup() {

//-- Motor KIRI
pinMode(mtrA01, OUTPUT);
pinMode(mtrA02, OUTPUT);
//-- Motor Kanan  F
pinMode(18, OUTPUT);
pinMode(mtrB02, OUTPUT);
pinMode(buzzer, OUTPUT);
pinMode(lampu, OUTPUT);
 
Serial.begin(115200);
delay(100);

my_bluetooth.begin(nama_bluetooth);

strip.begin();
strip.show(); 

}

void loop() {

if(Serial.available()> 0){
    char dat = Serial.read();
    Serial.println(dat);
    
    if (dat=='B'){
      digitalWrite(mtrA01,HIGH);
      digitalWrite(mtrA02,LOW);
      digitalWrite(18,LOW);
      digitalWrite(mtrB02,HIGH);
      Serial.println(" Motor Gerak ke UNDUR");
      
    }
    
    if (dat=='F'){
      digitalWrite(mtrA01,LOW);
      digitalWrite(mtrA02,HIGH);
      digitalWrite(18,HIGH);
      digitalWrite(mtrB02,LOW);
      Serial.println(" Motor Gerak ke DEPAN ");
    }
    if (dat=='S'){
      digitalWrite(mtrA01,LOW);
      digitalWrite(mtrA02,LOW);
      digitalWrite(18,LOW);
      digitalWrite(mtrB02,LOW);
      Serial.println(" Motor HENTI");
    }

    if (dat=='R'){
      digitalWrite(mtrA01,LOW);
      digitalWrite(mtrA02,HIGH);
      digitalWrite(18,LOW);
      digitalWrite(mtrB02,HIGH);
      Serial.println(" Motor Gerak ke KIRI");
      setColor(strip.Color(0, 0, 255));
    }

    if (dat=='L'){
      digitalWrite(mtrA01,HIGH);
      digitalWrite(mtrA02,LOW);
      digitalWrite(18,HIGH);
      digitalWrite(mtrB02,LOW);
      Serial.println(" Motor Gerak ke KANAN");
      setColor(strip.Color(0, 255, 0));
    }

      //If state is equal with letter 'W', turn leds on or of off
    else if (dat == 'W') {
      if (i==0){  
         digitalWrite(lampu, HIGH); 
         i=1;
      }
      else if (i==1){
         digitalWrite(lampu, LOW); 
         i=0;
      }
      state='n';
    }

    //If state is equal with letter 'V', play (or stop) horn sound
     else if (dat == 'V'){
      Serial.println(j);
      if (j==0){  
         digitalWrite(buzzer, HIGH);//Speaker on 
          Serial.println(" HON BERBUNYI");
         j=1;
      }
      else if (j==1){
         digitalWrite(buzzer, LOW);
         Serial.println(" HON STOP");
         j=0;
      }
      dat='n';  
    }
  }
}

void setColor(uint32_t color) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}
