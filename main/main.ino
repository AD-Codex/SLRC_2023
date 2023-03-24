
#include <Servo.h>
# include <Stepper.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU6050_light.h>


Servo myservo;
MPU6050 mpu(Wire);

//# define STEPS_PER_REVOLUTION 800


// Motor A connections -------------------------------------------------------------------
const int enL = 10;
const int in3 = 8;
const int in4 = 9;
// Motor B connections
const int in1 = 6;
const int in2 = 7;
const int enR = 5;


// stepper motor -------------------------------------------------------------------------
const int PUL_PIN = 3;
const int DIR_PIN = 4;

//Stepper stepper( STEPS_PER_REVOLUTION, DIR_PIN, PUL_PIN);


// LED -----------------------------------------------------------------------------------
const int led1 = 35;
const int ledR = 25;
const int ledL = 27;
const int ledRed = 29;
const int ledGreen = 31;
const int ledBlue = 33;
const int led99 = 40;

// Buzzer --------------------------------------------------------------------------------
const int Buzzer_pin = 22;


// Limit switch -------------------------------------------------------------------------
const int Limit_switch = 50;



// PID -----------------------------------------------------------------------------------
float Lsum =0;
float Rsum =0;
int error = 0;
int last_error = 0;
int P_val = 0;
int I_val = 0;
int D_val = 0;

const float kp = 3;                 // 3
const float ki = 0.003;             // 0.003
const float kd = 0.9;               // 0.9

const int Rbase_speed = 220;    //220
const int Lbase_speed = 210;    //210
const int max_speed = 255; //255
const int min_speed = 185; //185

int PID_MidLine_val = 3480;   // less than 950 consider as white line set
int wLine = 930;
//int bLine = 1000;


// IR variables ------------------------------------------------------------------------------
//                  // mid white line
int L8_read = 0;
int L7_read = 0;

int L5_read = 0; 
int L4_read = 0;    // 1009
int L3_read = 0;    // 984  
int L2_read = 0;    // 928  
int L1_read = 0;    // 917
int R1_read = 0;    // 915 
int R2_read = 0;    // 957
int R3_read = 0;    // 998  
int R4_read = 0;    // 1009
int R5_read = 0;

//1010 880
//1008 837
//1008 845
//986 767
//1008 836
//1007 830
//974 685
//973 663


int R7_read = 0;
int R8_read = 0;


// Gyro variables ----------------------------------------------------------------------------
float Gyro_read_z = 0.0;


// color sensor pin ---------------------------------------------------------------------------
const int S0 = 37;
const int S1 = 35;
const int S2 = 41;
const int S3 = 39;
const int Color_sensor_in = 43;


// Color sensor variables ---------------------------------------------------------------------
int Sensor_redMin = 0;      // Red minimum value
int Sensor_redMax = 0;      // Red maximum value
int Sensor_greenMin = 0;    // Green minimum value
int Sensor_greenMax = 0;    // Green maximum value
int Sensor_blueMin = 0;     // Blue minimum value
int Sensor_blueMax = 0;     // Blue maximum value

int Sensor_redPW = 0;       // Variables for Color Pulse Width Measurements
int Sensor_greenPW = 0;
int Sensor_bluePW = 0;
int Sensor_colmean = ( Sensor_redPW + Sensor_greenPW + Sensor_bluePW)/3;

int Sensor_redValue;         // Variables for final Color values
int Sensor_greenValue;
int Sensor_blueValue;

int Sensor_color_value = 0;



// turing veriables ----------------------------------------------------------------------------
char junction = 'P';          // 80
boolean state = false;

int junction_delay = 60;       // 5


// D1 Task1 variables -------------------------------------------------------------------------
int R[3] = { 0, 0, 0};

int R_cube = 0;
int G_cube = 0;
int B_cube = 0;

int curr_pos = 3;
int mov_pos = 0;

int curr_box = 1;

char P1To2[] = "RR"; 
char P1To3[] = "RPR";
char P1To4[] = "P";
char P1To5[] = "RL";
char P1To6[] = "RPL";

char P2To1[] = "LL";
char P2To3[] = "RR";
char P2To4[] = "LR";
char P2To5[] = "P";
char P2To6[] = "RL";

char P3To1[] = "LPL";
char P3To2[] = "LL";
char P3To4[] = "LPR";
char P3To5[] = "LR";
char P3To6[] = "P";

char P4To5[] = "LL";
char P4To6[] = "LPL";

char P5To4[] = "RR";
char P5To6[] = "LL";

char P6To4[] = "RPR";
char P6To5[] = "RR";

// servo motors pin out --------

int servo1 = 11;
int servo2 = 12;

int stepper_motor_pos = 0;

int minArray[] = {1023, 1023, 1023,1023,1023,1023,1023,1023};
int maxArray[] = {0, 0, 0, 0, 0,0,0,0};


// ==================================== setup ==================================================
void setup() {
  
  Serial.begin(9600);
  Wire.begin();
  mpu.begin();
  mpu.calcGyroOffsets();

  // IRsensor reads
  pinMode( A0, INPUT);
  pinMode( A1, INPUT);
  pinMode( A2, INPUT);
  pinMode( A3, INPUT);
  pinMode( A4, INPUT);
  pinMode( A5, INPUT);
  pinMode( A6, INPUT);
//  pinMode( A7, INPUT);
  pinMode( A8, INPUT);
  pinMode( A9, INPUT);    // left
  pinMode( A10, INPUT);   // right
//  pinMode( A11, INPUT);
//  pinMode( A12, INPUT);
//  pinMode( A13, INPUT);
  
  
  // Set all the motor control pins to outputs
  pinMode(enR, OUTPUT);
  pinMode(enL, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  

  // Color sensor pin setup
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(Color_sensor_in, INPUT);

  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);


  // LED pin setup
  pinMode(ledR, OUTPUT);
  pinMode(ledL, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(led99, OUTPUT);

  // Buzzer
  pinMode( Buzzer_pin, OUTPUT);

  // limit 
  pinMode( Limit_switch, INPUT);
  
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  // Arm servo pin setup
//  myservo.attach(11);
//  myservo1.attach(12);
  myservo.attach(13);
  myservo.write(180);

//  myservo.write(150);
//  myservo1.write(90);

  

  // stepper pin
  pinMode(PUL_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

//  delay(3000);

//  IR_line_set();

//  digitalWrite(Buzzer_pin, HIGH);
//  delay( 50);
//  digitalWrite(Buzzer_pin, LOW);
//  delay( 50);
//  digitalWrite(Buzzer_pin, HIGH);
//  delay( 50);
//  digitalWrite(Buzzer_pin, LOW);



//for ( int i=0; i<200; i=i+1) {
//    digitalWrite(PUL_PIN, HIGH);
//    delayMicroseconds(500);
//    digitalWrite(PUL_PIN, LOW);
//    delayMicroseconds(500);
//    stepper_motor_pos = 0;
//  }
//  while ( digitalRead(Limit_switch) == LOW) {
//    digitalWrite( DIR_PIN, LOW);
//
//    digitalWrite(PUL_PIN, HIGH);
//    delayMicroseconds(500);
//    digitalWrite(PUL_PIN, LOW);
//    delayMicroseconds(500);
//    stepper_motor_pos = 0;
//  }

  

}

void loop() {

//  IR_line_set();
//  Serial.print( maxArray[0]);
//  Serial.print( " ");
//  Serial.print( maxArray[1]);
//  Serial.print( " ");
//  Serial.print( maxArray[2]);
//  Serial.print( " ");
//  Serial.print( maxArray[3]);
//  Serial.print( " ");
//  Serial.print( maxArray[4]);
//  Serial.print( " ");
//  Serial.print( maxArray[5]);
//  Serial.print( " ");
//  Serial.print( maxArray[6]);
//  Serial.print( " ");
//  Serial.println( maxArray[7]);
//  Serial.print( minArray[0]);
//  Serial.print( " ");
//  Serial.print( minArray[1]);
//  Serial.print( " ");
//  Serial.print( minArray[2]);
//  Serial.print( " ");
//  Serial.print( minArray[3]);
//  Serial.print( " ");
//  Serial.print( minArray[4]);
//  Serial.print( " ");
//  Serial.print( minArray[5]);
//  Serial.print( " ");
//  Serial.print( minArray[6]);
//  Serial.print( " ");
//  Serial.println( minArray[7]);
//
//  delay(100000);



//  IR_check();
//  PID_IR_move();
//
//  Serial.print( analogRead(A9));
//  Serial.print( " ");
//  Serial.println( analogRead(A10));

  
//  D1_T2();
//  delay(10);
//
//  analogWrite(enR , 200);
//  analogWrite(enL , 220);
//  digitalWrite(in1, HIGH);
//  digitalWrite(in2, LOW);
//  digitalWrite(in3, LOW);
//  digitalWrite(in4, HIGH);

//  move_forward();

//  char b[] = "RL";
//  Serial.print(b);
//  D1_T1_movePath( b);

  hanoiTower1( 5);

//  hanoiTower2( 4, 6);
//  Serial.println();
//  hanoiTower2( 4, 6);
//  delay(1000000);

//  move_forward();

//  delay(1000);
//  turn_90_line( 'R');
//  delay(1000);
//  turn_90_line( 'L');
//  delay(1000);
//  turn_180_line();
//  delay(1000);

//  analogWrite(enR , 200);
//  analogWrite(enL , 220);
//  digitalWrite(in1, HIGH);
//  digitalWrite(in2, LOW);
//  digitalWrite(in3, LOW);
//  digitalWrite(in4, HIGH);
  
//  delay(1000);
//  stop_move();
  
//  Gyro_read();
  

//  Box_color_detect();

//  Arm_Lift( 'U' , 30);
//  delay(100000);


}


void IR_check() {
  L5_read = analogRead(A9);
  
  L4_read = analogRead(A6);
  L3_read = analogRead(A5);
  
  L2_read = analogRead(A4);
  L1_read = analogRead(A3);
  R1_read = analogRead(A2);
  R2_read = analogRead(A8);
  R3_read = analogRead(A1);
  R4_read = analogRead(A0);

  R5_read = analogRead(A10);

//  Serial.print(analogRead(A9));


  int val[] = {L5_read, L4_read, L3_read, L2_read, L1_read, R1_read, R2_read, R3_read, R4_read ,R5_read};
  int max_val_set[] = { 989, 1008 ,1007 ,1007 ,985 ,1007 ,1007 ,974 ,973,750};
  int min_val_set[] = { 827, 847 ,819 ,845 ,712 ,835 ,821 ,699 ,676, 47};

  for ( int i=0; i<10; i=i+1) {
    val[i] = map( val[i] , min_val_set[i], max_val_set[i], 820 ,1023);
  }

  L5_read = val[0];
  L4_read = val[1];
  L3_read = val[2];
  L2_read = val[3];
  L1_read = val[4];
  R1_read = val[5];
  R2_read = val[6];
  R3_read = val[7];
  R4_read = val[8];
  R5_read = val[9];



//    // PID position setup
//  Lsum = 0.0*L4_read + 0.1*L3_read + 0.2*L2_read + 0.3*L1_read;
//  Rsum = 0.4*R1_read + 0.5*R2_read + 0.6*R3_read + 0.7*R4_read;
//
//  float IR_val1 = Lsum +Rsum;
//
//  int IR_val2 = L4_read + L3_read + L2_read + L1_read + R1_read + R2_read + R3_read + R4_read ;
//
//  float PID_MidLine_val = IR_val1*10000/IR_val2;
//
//  Serial.print(" PID_MidLine_val :");
//  Serial.print( PID_MidLine_val);
//
//  Serial.print(" ");
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
//  Serial.println();

  

}

void IR_line_set() {

  digitalWrite(Buzzer_pin, HIGH);
  delay( 50);
  digitalWrite(Buzzer_pin, LOW);
  delay( 500);
  digitalWrite(Buzzer_pin, HIGH);
  delay( 50);
  digitalWrite(Buzzer_pin, LOW);


  for ( int i=0; i<500; i=i+1) {
    IR_check();
    int val[] = {L4_read, L3_read, L2_read, L1_read, R1_read, R2_read, R3_read, R4_read};
    for ( int j=0; j<8; j=j+1){
      if ( val[j] > maxArray[j]) {
        maxArray[j] = val[j];
      }
      if ( val[j] < minArray[j]) {
        minArray[j] = val[j];
      }
    }
    delay(10);
  }

  digitalWrite(Buzzer_pin, HIGH);
  delay( 50);
  digitalWrite(Buzzer_pin, LOW);
  delay( 500);
  digitalWrite(Buzzer_pin, HIGH);
  delay( 50);
  digitalWrite(Buzzer_pin, LOW);
  
}

void stop_move() {
  digitalWrite(in1, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in4, LOW);
}

void move_forward() {
  // 210 165
  analogWrite(enR , 220);
  analogWrite(enL , 210);
  digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);  
  digitalWrite(in2, LOW);
  digitalWrite(in4, LOW);
  
  
}

void move_back(){
  analogWrite(enR , 220);
  analogWrite(enL , 210);
  digitalWrite(in2, HIGH);
  digitalWrite(in4, HIGH);  
  digitalWrite(in1, LOW);
  digitalWrite(in3, LOW);
}

void turn_right() {
  // 220 160
  analogWrite(enR , 195);
  analogWrite(enL , 195);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turn_left() {
  // 200 220
  analogWrite(enR , 195);
  analogWrite(enL , 195);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
