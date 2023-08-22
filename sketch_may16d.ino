#define COUNT_LOW 1400
#define COUNT_HIGH 3300

 #define TIMER_WIDTH 16

#include "esp32-hal-ledc.h"

void setup() {
  pinMode(32, INPUT_PULLUP);
ledcSetup(1, 50, TIMER_WIDTH); // channel 1, 50 Hz, 16-bit width
ledcAttachPin(2, 1);
ledcSetup(2, 50, TIMER_WIDTH); // channel 1, 50 Hz, 16-bit width
ledcAttachPin(4, 2);
ledcSetup(3, 50, TIMER_WIDTH);
ledcAttachPin(21, 3);
ledcSetup(4, 50, TIMER_WIDTH);
ledcAttachPin(16, 4);
ledcSetup(5, 50, TIMER_WIDTH);
ledcAttachPin(17, 5);
ledcSetup(6, 50, TIMER_WIDTH);
ledcAttachPin(15, 6);
}

void loop() {
/*ledcWrite(1, 1638);
ledcWrite(2, 1638); 
ledcWrite(3, 1638); // pouce
ledcWrite(4, 1638); // pouce rotat
ledcWrite(5, 6000);
ledcWrite(6, 5000);*/
if(digitalRead(32) == 1){
  open();
} else {
  close();
}
}
void close(){
  ledcWrite(1, 4000);
  ledcWrite(2, 1638);
  ledcWrite(3, 1638);
  ledcWrite(4, 5000);
  ledcWrite(5, 1638);
  ledcWrite(6, 1638);
}
void open(){
  ledcWrite(1, 1638);
  ledcWrite(2, 7000);
  ledcWrite(3, 7000);
  ledcWrite(4, 1638);
  ledcWrite(5, 6000);
  ledcWrite(6, 6000);
}