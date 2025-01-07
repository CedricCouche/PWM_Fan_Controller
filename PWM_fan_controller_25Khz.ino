#include <Arduino.h> 

const int fan_control_pin = 9; //Blue wire on Fan (about 25kHz PWM)
int count = 0;
unsigned long start_time;
int rpm;

void setup(){
  TCCR1A = 0 ; // undo the configration done by ...
  TCCR1B = 0 ; // ... the arduino core library
  TCNT1 = 0 ; // reset timer
  TCCR1A =  _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11) ; // undo the default timer
  TCCR1B =  _BV(WGM13) | _BV(CS10); //for pin 9 & 10
  ICR1 = 320 ; // pwm will be 0 to 320 instead of 0 to 255
  pinMode(fan_control_pin, OUTPUT);
  OCR1A = 0; // set pwm to 0 out of 320 on pin 9
  OCR1B = 0; // set pwm to 0 out of 320 on pin 10
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), counter, RISING); //Yellow wire with 5V pullup
  
}

void loop(){

  for(int pwm = 0; pwm <= 320; pwm += 64){
    OCR1A = pwm;
    delay(5000);
    start_time = millis();
    count = 0;
    while((millis() - start_time ) < 1000){
    }
    rpm = count * 30; //60/2
    Serial.print("PWM = ");
    Serial.print(map(pwm, 0, 320, 0, 100));
    Serial.print("%, Speed = ");
    Serial.print(rpm);
    Serial.print("rpm");
    Serial.println();
    }
}

void counter(){
  count++;
}