// Motor A connections
int enL = 10;
int in4 = 9;
int in3 = 8;
// Motor B connections
int in2 = 7;
int in1 = 6;
int enR = 5;

//
int L1_read = 0;
int L2_read = 0;
int L3_read = 0;
int L4_read = 0;
int R1_read = 0;
int R2_read = 0;
int R3_read = 0;
int R4_read = 0;

float sum =0;
float val = 0.00;
int error = 0;
int last_error = 0;
int P_val = 0;
int I_val = 0;
int D_val = 0;

float kp = 1; //1
float ki = 0.025; // 0.8
float kd = 0.6; // 0.6

int base_speed = 125;
int max_speed = 250;


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

  sum = 0*L4_read + 1*L3_read + 2*L2_read + 3*L1_read + 4*R1_read + 5*R2_read + 6*R3_read + 7*R4_read;
  val = sum*1000/(L4_read + L3_read + L2_read + L1_read + R1_read + R2_read + R3_read + R4_read );

  Serial.print(" value :");
  Serial.print(val);
  Serial.print(" , ");

  Serial.print( L4_read);
  Serial.print(" ");
  Serial.print( L3_read);
  Serial.print(" ");
  Serial.print( L2_read);
  Serial.print(" ");
  Serial.print( L1_read);
  Serial.print(" ");
  Serial.print( R1_read);
  Serial.print(" ");
  Serial.print( R2_read);
  Serial.print(" ");
  Serial.print( R3_read);
  Serial.print(" ");
  Serial.print( R4_read);
  Serial.print(" I_val");
  Serial.print( I_val);
  Serial.println();
  

  if ( L4_read < 1000 && L3_read < 1000 && L2_read < 1000 && L1_read < 1000 && R1_read < 1000 && R2_read < 1000 && R3_read < 1000 && R4_read < 1000 ) {
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
    error = 3500 - val;
  }

//  int error = 3500 - val;
  P_val = error;
  I_val = I_val + error;
  D_val = error - last_error;
  last_error = error;

  

  int motor_speed = P_val*kp + I_val*ki + D_val*kd ;

  int Rmotor_speed = base_speed + motor_speed;
  int Lmotor_speed = base_speed - motor_speed;

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
  if ( Rmotor_speed <= 0) {
    Rmotor_speed = Rmotor_speed * -1 + 20;
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  if ( Lmotor_speed <= 0) {
    Lmotor_speed = Lmotor_speed * -1 + 20;
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }

  analogWrite(enR , Rmotor_speed);
  analogWrite(enL , Lmotor_speed);
  // Turn on motors F
//  digitalWrite(in1, HIGH);
//  digitalWrite(in2, LOW);
//  digitalWrite(in3, HIGH);
//  digitalWrite(in4, LOW);
  
  delay(50);
}
