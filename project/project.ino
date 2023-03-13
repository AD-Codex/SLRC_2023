// Motor A connections
int enR = 5;
int in1 = 6;
int in2 = 7;
// Motor B connections
int in3 = 8;
int in4 = 9;
int enL = 10;

//
int L1_read = 0;
int L2_read = 0;
int L3_read = 0;
int L4_read = 0;
int R1_read = 0;
int R2_read = 0;
int R3_read = 0;
int R4_read = 0;


void setup() {
  Serial.begin(9600);
  // sensor reads
  pinMode( A0, INPUT);
  pinMode( A1, INPUT);
  pinMode( A2, INPUT);
  pinMode( A3, INPUT);
  pinMode( A4, INPUT);
  pinMode( A5, INPUT);
  pinMode( A6, INPUT);
  pinMode( A7, INPUT);
  
  // Set all the motor control pins to outputs
  pinMode(enR, OUTPUT);
  pinMode(enL, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(38, OUTPUT);
  pinMode(36, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {
  L4_read = analogRead(A0);
  L3_read = analogRead(A1);
  L2_read = analogRead(A2);
  L1_read = analogRead(A3);
  R1_read = analogRead(A4);
  R2_read = analogRead(A5);
  R3_read = analogRead(A6);
  R4_read = analogRead(A7);

  Serial.print( analogRead(A0));
  Serial.print(" ");
  Serial.print( analogRead(A1));
  Serial.print(" ");
  Serial.print( analogRead(A2));
  Serial.print(" ");
  Serial.print( analogRead(A3));
  Serial.print(" ");
  Serial.print( analogRead(A4));
  Serial.print(" ");
  Serial.print( analogRead(A5));
  Serial.print(" ");
  Serial.print( analogRead(A6));
  Serial.print(" ");
  Serial.print( analogRead(A7));
  Serial.println();

  if ( L3_read < 1000 && L2_read < 1000 && L1_read >= 1000 && R1_read >= 1000 && R2_read < 1000 && R3_read < 1000 ){
    digitalWrite(38, HIGH);
    digitalWrite(36, HIGH);
    
    analogWrite(enR, 200);
    analogWrite(enL, 200);
    // Turn on motors F
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    
  }
  else if ( L1_read >= 1000 && L2_read >= 1000){
    digitalWrite(38, HIGH);
    digitalWrite(36, LOW);

    analogWrite(enR, 120);
    analogWrite(enL, 60);
    // Turn on motors F
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if ( L1_read >= 1000 && L2_read <= 1000 && R1_read <= 1000){
    digitalWrite(38, HIGH);
    digitalWrite(36, LOW);

    analogWrite(enR, 120);
    analogWrite(enL, 70);
    // Turn on motors F
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if ( L1_read < 1000 && L2_read >= 1000 && L3_read >= 1000 && L4_read >= 1000){
    digitalWrite(38, HIGH);
    digitalWrite(36, LOW);

    analogWrite(enR, 120);
    analogWrite(enL, 20);
    // Turn on motors F
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if ( L1_read <= 1000 && L2_read >= 1000){
    digitalWrite(38, HIGH);
    digitalWrite(36, LOW);

    analogWrite(enR, 120);
    analogWrite(enL, 50);
    // Turn on motors F
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if ( L3_read >= 1000 && L4_read >= 1000){
    digitalWrite(38, HIGH);
    digitalWrite(36, LOW);

    analogWrite(enR, 100);
    analogWrite(enL, 50);
    // Turn on motors F
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if ( L3_read < 1000 && L4_read >= 950){
    digitalWrite(38, HIGH);
    digitalWrite(36, LOW);

    analogWrite(enR, 80);
    analogWrite(enL, 80);
    // Turn on motors F
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  /////////////////////////////////////////////////////////////////////////////////
  else if ( R1_read >= 1000 && R2_read >= 1000){
    digitalWrite(38, LOW);
    digitalWrite(36, HIGH);

    analogWrite(enR, 60);
    analogWrite(enL, 120);
    // Turn on motors F
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if ( R1_read >= 1000 && R2_read <= 1000 && L1_read <= 1000){
    digitalWrite(38, LOW);
    digitalWrite(36, HIGH);

    analogWrite(enR, 70);
    analogWrite(enL, 120);
    // Turn on motors F
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if ( R1_read < 1000 && R2_read >= 1000 && R3_read >= 1000 && R4_read >= 1000){
    digitalWrite(38, LOW);
    digitalWrite(36, HIGH);

    analogWrite(enR, 20);
    analogWrite(enL, 120);
    // Turn on motors F
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if ( R1_read <= 1000 && R2_read >= 1000){
    digitalWrite(38, LOW);
    digitalWrite(36, HIGH);

    analogWrite(enR, 50);
    analogWrite(enL, 120);
    // Turn on motors F
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if ( R3_read >= 1000 && R4_read >= 1000){
    digitalWrite(38, LOW);
    digitalWrite(36, HIGH);

    analogWrite(enR, 50);
    analogWrite(enL, 100);
    // Turn on motors F
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if ( R3_read < 1000 && R4_read >= 950){
    digitalWrite(38, LOW);
    digitalWrite(36, HIGH);

    analogWrite(enR, 80);
    analogWrite(enL, 80);
    // Turn on motors F
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else {
    digitalWrite(38, LOW);
    digitalWrite(36, LOW);
    
    analogWrite(enR, 80);
    analogWrite(enL, 80);
    // Turn on motors F
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }

}
