//********************* BLDC CONTORLLER PROGRAM **********************//

// Arduino PWM-MOSFET PINS
int G1 = 11;
int G2 = 10;
int G3 = 9;
int G4 = 6;
int G5 = 5;
int G6 = 3;

// Arduino pwmn LED indicator pins
int redLED = 8; // > 0.7 Duty cycle 
int greenLED = 7; // Between 0.4 and 0.7 Duty cycle 
int blueLED = 4; // < 0.4 Duty cycle

// Arduino analog pin for throttle input
int PWM_Pin = A0; // PWM signal read from analog pin A0
int potValue = 0; // potentiometer used as the throttle 

float delayTime = 3; // delay to allow motor tpo spin

void setup() {
  // put your setup code here, to run once:
  pinMode(G1, OUTPUT);
  pinMode(G2, OUTPUT);
  pinMode(G3, OUTPUT);
  pinMode(G4, OUTPUT);
  pinMode(G5, OUTPUT);
  pinMode(G6, OUTPUT);
  pinMode(PWM_Pin, INPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // take the analog reading from the pot and convert to a pwm signal

  potValue = analogRead(PWM_Pin); // read the potentiometer value

  //    Display the pwm status 
  if (potValue < 410){
    digitalWrite(blueLED, HIGH); // turns on blue led if pwm duty cycle is less than 40%
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, LOW);
    }
  else if(potValue > 410 and potValue < 716){
    digitalWrite(blueLED, LOW); // turns on green led if pwm duty cycle is between 40 % and 70 %
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    }
   else if (potValue > 716){
    digitalWrite(blueLED, LOW); // turns on red led if pwm duty cycle is greater than 70 %
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    }

  // map the potentimeter reading to 8-bit Arduino digital output pins ADC values
  int pwmOutput = map(potValue,0,1023,0,255);

  // COMMUTATION STEP 1: G1 -> HIGH, G4 -> HIGH, G5 -> LOW
  analogWrite(G1, pwmOutput);
  digitalWrite(G4, HIGH);
  digitalWrite(G2, LOW);
  digitalWrite(G3, LOW);
  digitalWrite(G5, LOW);
  digitalWrite(G6, LOW);
  delay(delayTime); // dlay to allow motor to spin

  // COMMUTATION STEP 2: G4 -> LOW, G6 -> HIGH,
  digitalWrite(G4, LOW);
  digitalWrite(G6, HIGH);
  delay(delayTime);

  // COMMUTATION STEP 3: G1 -> LOW, G3 -> HIGH,
  digitalWrite(G1, LOW);
  analogWrite(G3, pwmOutput);
  delay(delayTime);

   // COMMUTATION STEP 4: G6 -> LOW, G2 -> HIGH,
  digitalWrite(G6, LOW);
  digitalWrite(G2, HIGH);
  delay(delayTime);

   // COMMUTATION STEP 5: G3 -> LOW, G5 -> HIGH,
  digitalWrite(G3, LOW);
  analogWrite(G5, pwmOutput);
  delay(delayTime);

   // COMMUTATION STEP 2: G2 -> LOW, G4 -> HIGH,
  digitalWrite(G2, LOW);
  digitalWrite(G4, HIGH);
  delay(delayTime);

}