// Motor A connections
int enL = 10;
int in4 = 9;
int in3 = 8;
// Motor B connections
int in2 = 7;
int in1 = 6;
int enR = 5;

//
int L5_Ir = 88;
int L4_Ir = 89;
int L3_Ir = 90;
int L2_Ir = 91;
int L1_Ir = 92;
int R1_Ir = 93;
int R2_Ir = 94;
int R3_Ir = 95;
int R4_Ir = 96;
int R5_Ir = 97;

int L5_read = 0;
int L4_read = 0;
int L3_read = 0;
int L2_read = 0;
int L1_read = 0;
int R1_read = 0;
int R2_read = 0;
int R3_read = 0;
int R4_read = 0;
int R5_read = 0;

float Lsum =0;
float Rsum =0;
int error = 0;
int last_error = 0;
int P_val = 0;
int I_val = 0;
int D_val = 0;

int bLine = 970;

float kp = 0.5; //0.5
float ki = 0.0008; // 0.0008
float kd = 0.5; // 0.5

int Rbase_speed = 200;
int Lbase_speed = 170;
int max_speed = 225; //225
int min_speed = 165; //165


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
  pinMode( A8, INPUT);
  pinMode( A9, INPUT);
  pinMode( A10, INPUT);
  pinMode( A11, INPUT);
  pinMode( A12, INPUT);
  pinMode( A13, INPUT);
  
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

  IR_line_set();
  delay(500);
  IR_line_set();
  delay(500);
  IR_line_set();
  delay(1000);

  
}

void loop() {
//  move_forward( 190);

//  Lm = map(0,255, 100, 255);
//  Rm = map(0,255, 100, 255);
// r 190, 250
// l 195, 255

  L5_read = analogRead(A11);
  L4_read = analogRead(A10);
  L3_read = analogRead(A9);
  L2_read = analogRead(A8);
  L1_read = analogRead(A7);
  R1_read = analogRead(A6);
  R2_read = analogRead(A5);
  R3_read = analogRead(A4);
  R4_read = analogRead(A3) + 90;
  R5_read = analogRead(A2);

  Lsum = 0.0*L5_read + 0.1*L4_read + 0.2*L3_read + 0.3*L2_read + 0.4*L1_read;
  Rsum = 0.5*R1_read + 0.6*R2_read + 0.7*R3_read + 0.8*R4_read + 0.9*R5_read;
//  Serial.print(" sum :");
//  Serial.print(Lsum);
//  Serial.print(" , ");
//  Serial.print(Rsum);
//  Serial.print(" , ");
  float IR_val1 = Lsum +Rsum;
//  Serial.print(val1);
//  Serial.print(" , ");
  int IR_val2 = L5_read + L4_read + L3_read + L2_read + L1_read + R1_read + R2_read + R3_read + R4_read+ R5_read;

//  Serial.print(val);
//  Serial.print(" , ");

  float IR_val = IR_val1*10000/IR_val2;

  Serial.print(" value :");
  Serial.print(IR_val);
  Serial.print(" , ");

//  IR_val = 4400;

//  Serial.print( L5_read);
//  Serial.print(" ");
//  Serial.print( L4_read);
//  Serial.print(" ");
//  Serial.print( L3_read);
//  Serial.print(" ");
//  Serial.print( L2_read);
//  Serial.print(" ");
//  Serial.print( L1_read);
//  Serial.print(" ");
//  Serial.print( R1_read);
//  Serial.print(" ");
//  Serial.print( R2_read);
//  Serial.print(" ");
//  Serial.print( R3_read);
//  Serial.print(" ");
//  Serial.print( R4_read);
//  Serial.print(" ");
//  Serial.print( R5_read);
//  Serial.print(" I_val");
//  Serial.print( I_val);
//  Serial.println();
  

  if ( L5_read < bLine && L4_read < bLine && L3_read < bLine && L2_read < bLine && L1_read < bLine && R1_read < bLine && R2_read < bLine && R3_read < bLine && R4_read < bLine && R5_read < bLine ) {
    if ( I_val < 0) {
      digitalWrite(38, LOW);
      digitalWrite(36, HIGH);
      error = 0;      
    }
    else if ( I_val > 0) {
      digitalWrite(38, HIGH);
      digitalWrite(36, LOW);
      error = 0;
    }
  }
  else{
    digitalWrite(38, HIGH);
    digitalWrite(36, HIGH);
    error = 4500 - IR_val;
  }

//  int error = 4400 - IR_val;
  P_val = error;
  I_val = I_val + error;
  D_val = error - last_error;
  last_error = error;

  

  int motor_speed = P_val*kp + I_val*ki + D_val*kd ;

  int Rmotor_speed = Rbase_speed + motor_speed;
  int Lmotor_speed = Lbase_speed - motor_speed;

  if ( Rmotor_speed < 0 ) {
    Rmotor_speed = 0;
  }
  if ( Lmotor_speed < 0) {
    Lmotor_speed = 0;
  }


  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  if ( Rmotor_speed >= max_speed) {
    digitalWrite(38, HIGH);
    digitalWrite(36, LOW);
    Rmotor_speed = max_speed;
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    
  }
  if ( Lmotor_speed >= max_speed) {
    digitalWrite(38, LOW);
    digitalWrite(36, HIGH);
    Lmotor_speed = max_speed;
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  if ( Rmotor_speed <= min_speed) {
    Rmotor_speed = (Rmotor_speed - 165)*-1  + 165;
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  if ( Lmotor_speed <= min_speed) {
    Lmotor_speed = (Lmotor_speed - 165)*-1 + 185;
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }

//  map(190, 225, )

  analogWrite(enR , Rmotor_speed);
  analogWrite(enL , Lmotor_speed);
  // Turn on motors F
//  digitalWrite(in1, HIGH);
//  digitalWrite(in2, LOW);
//  digitalWrite(in3, HIGH);
//  digitalWrite(in4, LOW);

  Serial.print(Rmotor_speed);
  Serial.print(" ");
  Serial.println(Lmotor_speed);
//
//  Serial.println(" ");
  
  delay(10);
}

void move_forward( int speed) {
  // 200 165
  // 255 230
  analogWrite(enR , 225);
  analogWrite(enL , 195);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}


void IR_line_set() {
  delay(500);
  
  L5_read = analogRead(A11);
  L4_read = analogRead(A10);
  L3_read = analogRead(A9);
  L2_read = analogRead(A8);
  L1_read = analogRead(A7);
  R1_read = analogRead(A6);
  R2_read = analogRead(A5);
  R3_read = analogRead(A4);
  R4_read = analogRead(A3) + 130;
  R5_read = analogRead(A2);

  int val[] = {L5_read, L4_read, L3_read, L2_read, L1_read, R5_read, R4_read, R3_read, R2_read, R1_read};

  int state = 1;
  int value =0;
  while ( state ==1) {
    state = 0;
    for ( int i=0; i<9; i=i+1) {
      if ( val[i] > val[i+1]) {
        value = val[i+1];
        val[i+1] = val[i];
        val[i] = value;
        state = 1;
      }
    }
  }
  Serial.print(" val ");
  Serial.print( val[0]);
  Serial.print("" );
  Serial.print( val[9]);
  Serial.print(" range ");
  Serial.println( val[9] - (val[9] - val[0])/6);
  bLine = val[9] - (val[9] - val[0])/6;
  
}
