// Motor A connections
int enL = 10;
int in3 = 8;
int in4 = 9;
// Motor B connections
int in1 = 6;
int in2 = 7;
int enR = 5;
//

int led1 = 35;
int led2 = 36;
int led3 = 38;
int led4 = 39;
int led99 = 40;

float sum = 0.0;
float val= 0.0;
int error = 0;
int last_error = 0;
int P_val = 0;
int I_val = 0;
int D_val = 0;

float kp = 1;         //  1
float ki = 0.025;     // 0.025
float kd = 0.6;       // 0.6

int base_speed = 150;
int max_speed = 250;

//                  // mid white line
int L4_read = 0;    // 1009
int L3_read = 0;    // 984  
int L2_read = 0;    // 928  
int L1_read = 0;    // 917
int R1_read = 0;    // 915 
int R2_read = 0;    // 957
int R3_read = 0;    // 998  
int R4_read = 0;    // 1009
// less than 930 consider as white line
int midLine_val = 3500;
int wLine = 930;
int bLine = 1000;


char junction = 'P';          // 80
boolean state = false;

int junction_delay = 5;       // 5


void setup() {
  // put your setup code here, to run once:
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
  
//  IR_check();
//  PID_IR_move();
//  delay(100);
  
//  D1_T2();
//  delay(10);

  char b[] = "LR";
  Serial.print(b);
  D1_T1_movePath( b);

}


void IR_check() {
  L4_read = analogRead(A0);
  L3_read = analogRead(A1);
  L2_read = analogRead(A2);
  L1_read = analogRead(A3);
  R1_read = analogRead(A4);
  R2_read = analogRead(A5);
  R3_read = analogRead(A6);
  R4_read = analogRead(A7);

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
//  Serial.println();
}

void stop_move() {
  digitalWrite(in1, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in4, LOW);
}

void move_forward( int speed) {
  analogWrite(enR , speed);
  analogWrite(enL , speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turn_right( int speed) {
  analogWrite(enR , speed);
  analogWrite(enL , speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turn_left( int speed) {
  analogWrite(enR , speed);
  analogWrite(enL , speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
