

const int fan_control_pin = 9; //Blue wire on Fan (about 490Hz PWM)
const int signal_pin = 2;
int count = 0;
unsigned long start_time;
int rpm;

void setup(){
  
  
  
  pinMode(fan_control_pin, OUTPUT);
  pinMode(signal_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), counter, RISING); //Yellow wire with 5V pullup
  
  Serial.begin(9600);

  Serial.println("PWN Fan controller - Default frequency of Arduino Uno R4");

  analogWrite(fan_control_pin, 255);
  delay(2000);
 
}

void loop(){

  for(int pwm = 0; pwm <= 255; pwm += 51){
    analogWrite(fan_control_pin, pwm);
    delay(5000);
    start_time = millis();
    count = 0;
    while((millis() - start_time ) < 1000){}
    
    rpm = count * 15 ; //60/2

    Serial.print("PWM = ");
    Serial.print(map(pwm, 0, 255, 0, 100));
    Serial.print("%, Speed = ");
    Serial.print(rpm);
    Serial.print("rpm");
    Serial.println();
    }
}

void counter(){
  count++;
}
