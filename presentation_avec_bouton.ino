#define COUNT_LOW 1638
#define COUNT_HIGH 7864


 #define TIMER_WIDTH 16

#include "esp32-hal-ledc.h"

const int button1Pin = 32;
const int button2Pin = 33;

void setup() {
  Serial.begin(115200);
   pinMode(button11Pin, INPUT_PULLUP);
   pinMode(button2Pin, INPUT_PULLUP);
   ledcSetup(1, 50, TIMER_WIDTH); // channel 1, 50 Hz, 16-bit width
   ledcAttachPin(21, 1);   // GPIO 22 assigned to channel 1
   ledcSetup(2, 50, TIMER_WIDTH);
   ledcAttachPin(16, 2);
   ledcSetup(3, 50, TIMER_WIDTH);
   ledcAttachPin(2, 3);
   ledcSetup(4, 50, TIMER_WIDTH);
   ledcAttachPin(4, 4);
   ledcSetup(5, 50, TIMER_WIDTH);
   ledcAttachPin(17, 5);
   ledcSetup(6, 50, TIMER_WIDTH);
   ledcAttachPin(15, 6);
}



void loop() {
  if(digitalRead(button1Pin) == 0){

  delay(5000);
  }
  else if (digitalRead(digitalRead(2Pin) == ){
  
  ledcWrite(3, 4800);
  ledcWrite(1, 1600);
  ledcWrite(2, 2000);
  ledcWrite(4, 6000);
  ledcWrite(5, 6000);
  ledcWrite(6, 6000);
  }
  ledcWrite(1, 6000);
  ledcWrite(3, 1700);
  ledcWrite(2, 5600);
  // put your main code here, to run repeatedly:
}
