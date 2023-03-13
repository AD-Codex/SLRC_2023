// Motor L connections
int enL = 5;
int in1 = 6;
int in2 = 7;
// Motor R connections
int in3 = 8;
int in4 = 9;
int enR = 10;

void setup() {
  // Set all the motor control pins to outputs
  pinMode(enL, OUTPUT);
  pinMode(enR, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {
  analogWrite(enL, 100);
  analogWrite(enR, 100);
  
//  // Turn on motor Forward
//  digitalWrite(in1, HIGH);
//  digitalWrite(in2, LOW);
//  digitalWrite(in3, HIGH);
//  digitalWrite(in4, LOW);
//  delay(2000);
//  
//  // Turn off motors
//  digitalWrite(in1, LOW);
//  digitalWrite(in2, LOW);
//  digitalWrite(in3, LOW);
//  digitalWrite(in4, LOW);
//  delay(100000);



  // Turn on motor Right
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(700);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(2000);

  // Turn on motor Left
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(700);
  
  // Turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(100000);




}
