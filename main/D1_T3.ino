int D1_T3_error = 0, D1_T3_L_dis, D1_T3_C_dis, D1_T3_R_dis;

char D1_T3_L = 'L';
char D1_T3_R = 'R';
char D1_T3_C = 'C';
char D1_T3_F = 'F';
char D1_T3_B = 'B';
int D1_T3_pause = 100; //pause for state transition
int D1_T3_del_f_dist_cm = 10;

int D1_T3_error_m;

long D1_T3_duration, D1_T3_cm, D1_T3_dis;


void D1_T3_stp() {
  D1_T3_motors(D1_T3_L, D1_T3_F, 0);
  D1_T3_motors(D1_T3_R, D1_T3_F, 0);
}

int D1_T3_go_for(int D1_T3_timee) {

  float D1_T3_fw_angle = D1_T3_gyro_acces(); //to take starting angle of gyro
  float D1_T3_fw_2 = D1_T3_gyro_acces(); //to take ending angleof gyro
  int D1_T3_T1 = millis(); //to get starting time for make 10 second goven forword
  int D1_T3_T2 = millis(); //to get ending time
  digitalWrite( Buzzer_pin, HIGH);
  while ( (D1_T3_T2 - D1_T3_T1) < D1_T3_timee) {
    D1_T3_fw_2 = D1_T3_gyro_acces(); //update new angle
    // D1_T3_motors(D1_T3_L, D1_T3_F, 165);
    // D1_T3_motors(D1_T3_R, D1_T3_F, 220);

    if (D1_T3_fw_2 < D1_T3_fw_angle) { // corecting the path of the linear motion
      D1_T3_motors(D1_T3_L, D1_T3_F, 220);
      D1_T3_motors(D1_T3_R, D1_T3_F, 130);
    }
    else if (D1_T3_fw_2 > D1_T3_fw_angle) {
      D1_T3_motors(D1_T3_L, D1_T3_F, 130);
      D1_T3_motors(D1_T3_R, D1_T3_F, 220);
    }
    else {
      D1_T3_motors(D1_T3_L, D1_T3_F, 165);
      D1_T3_motors(D1_T3_R, D1_T3_F, 220);
    }


    D1_T3_T2 = millis();
  }
  digitalWrite( Buzzer_pin, LOW);

  D1_T3_stp();
  delay(1000);

  while (abs(D1_T3_fw_2 - D1_T3_fw_angle) > 2) { // to correct starting angle and ending angle of gyro
    D1_T3_fw_2 = D1_T3_gyro_acces();
    if (D1_T3_fw_2 > D1_T3_fw_angle) {

      D1_T3_motors(D1_T3_L, D1_T3_B, 220);
      D1_T3_motors(D1_T3_R, D1_T3_F, 220);
    }
    else {

      D1_T3_motors(D1_T3_L, D1_T3_F, 220);
      D1_T3_motors(D1_T3_R, D1_T3_B, 220);
    }

  }

  D1_T3_stp();
  delay(1000);
}

void D1_T3_go_rev() {
  D1_T3_motors(D1_T3_L, D1_T3_B, 170);
  D1_T3_motors(D1_T3_R, D1_T3_B, 170);
}

float D1_T3_turn_left(float D1_T3_angle) {
//  stp();
//  delay(1000);
  float D1_T3_angle1 = D1_T3_gyro_acces();
  float D1_T3_angle2 = D1_T3_gyro_acces();

  while (abs(D1_T3_angle2 - D1_T3_angle1) < D1_T3_angle) { //turn untill 30 degree


    D1_T3_motors(D1_T3_L, D1_T3_B, 220);
    D1_T3_motors(D1_T3_R, D1_T3_F, 220);
    D1_T3_angle2 = D1_T3_gyro_acces();


  }
  D1_T3_stp();

  Serial.print("angle 1:");
  Serial.println(D1_T3_angle1);
  Serial.print("angle 2:");
  Serial.println(D1_T3_angle2);



}


float D1_T3_turn_right(float D1_T3_angle) {
  float D1_T3_angle3 = D1_T3_gyro_acces();
  float D1_T3_angle4 = D1_T3_gyro_acces();
  while (abs(D1_T3_angle3 - D1_T3_angle4) < D1_T3_angle) {

    D1_T3_motors( D1_T3_L, D1_T3_F, 220);
    D1_T3_motors( D1_T3_R, D1_T3_B, 220);

    D1_T3_angle4 = D1_T3_gyro_acces();

  }
  D1_T3_stp();

  Serial.print("angle 3:");
  Serial.println(D1_T3_angle3);
  Serial.print("angle 4:");
  Serial.println(D1_T3_angle4);


}


int D1_T3_wallFollow() {


  D1_T3_L_dis = D1_T3_getDistance(1, 150);//150 initial value
  D1_T3_C_dis = D1_T3_getDistance(2, 90);
  if (D1_T3_C_dis < 20){
    delay(200);
    D1_T3_C_dis = D1_T3_getDistance(2, 90);
    }
  D1_T3_R_dis = D1_T3_getDistance(3, 0);//0 initial value

/*

  Serial.print("left");
    Serial.println(L_dis);


    Serial.print("right");
    Serial.println(R_dis);
    Serial.print("center");
    Serial.println(C_dis);
*/  
  if ((D1_T3_L_dis < 5) || (D1_T3_R_dis < 5) || (D1_T3_C_dis < 5)) {
    D1_T3_stp();
    delay(1000);
    D1_T3_go_rev();
    delay(800);
  }

  else if (D1_T3_C_dis < 20) {
    D1_T3_stp();
    delay(100);
    D1_T3_L_dis = D1_T3_getDistance(1, 60); //150 ref point
    D1_T3_R_dis = D1_T3_getDistance(3, 90); // 0 ref point

    if (D1_T3_L_dis < D1_T3_R_dis) {
      D1_T3_turn_right(40);
      D1_T3_go_for(1500);
      D1_T3_turn_left(40);
      
      
    }
    else {
      D1_T3_turn_left(40);
      D1_T3_go_for(1500);
      D1_T3_turn_right(40);
      

    }
  }

  else if ( D1_T3_L_dis < 20) {
    D1_T3_stp();
    delay(1000);
    D1_T3_turn_right(30);
    D1_T3_go_for(1500);
    D1_T3_stp();
    delay(1000);
    D1_T3_turn_left(30);

  }

  else if ( D1_T3_R_dis < 20) {
    D1_T3_stp();
    delay(1000);
    D1_T3_turn_left(30);
    D1_T3_go_for(1500);
    D1_T3_stp();
    delay(1000);


    D1_T3_turn_right(30);

  }


  else {

    D1_T3_go_for(1000);

  }

}

int D1_T3_motors(char D1_T3_motor, char D1_T3_dirr, int D1_T3_spd) {
//  Serial.println(motor);
  if ( D1_T3_motor == 82 ){ //left
   // Serial.println("left");
    if ( D1_T3_dirr == 70 ){
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
    }
    else if ( D1_T3_dirr == 66 ){
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
    }
    else {
      D1_T3_error_m = -1;
    }
    analogWrite(enR, D1_T3_spd);
  }
  
  else if ( D1_T3_motor == 76 ){ //right
    //Serial.println("right");
    if ( D1_T3_dirr == 70 ){
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
    else if ( D1_T3_dirr == 66 ){
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    }
    else {
      D1_T3_error_m = -1;
    }
    analogWrite(enL, D1_T3_spd);
  }
  
}

float D1_T3_gyro_acces() {
  mpu.update();

  
  float D1_T3_z=mpu.getAngleZ();
  Serial.print("Z : ");
  Serial.println(D1_T3_z);                              // display data
  
  return(D1_T3_z);
  
  
}

void D1_T3_rotate(int D1_T3_pos){
  //Serial.println("ff");
  servo.write(D1_T3_pos);
}

long D1_T3_microsecondsToCentimeters(long D1_T3_microseconds) {
  //Serial.println("gg");
  return D1_T3_microseconds / 29 / 2;
}

long D1_T3_distance(int D1_T3_pingPin){

  //Serial.println("trigering pin");
  
  pinMode(D1_T3_pingPin, OUTPUT);
  digitalWrite(D1_T3_pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(D1_T3_pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(D1_T3_pingPin, LOW);

  pinMode(D1_T3_pingPin, INPUT);
  D1_T3_duration = pulseIn(D1_T3_pingPin, HIGH);

  D1_T3_cm = D1_T3_microsecondsToCentimeters(D1_T3_duration);

  return D1_T3_cm;
}

long D1_T3_getDistance(int D1_T3_sensor, int D1_T3_angle) {
  
  if (D1_T3_sensor == 1){
    servo.attach(11);
    D1_T3_rotate(D1_T3_angle);
    delay(300);
    D1_T3_dis = D1_T3_distance(uSensor1);
    return D1_T3_dis;
    //Serial.println("sensor 1 selected");
  }
  else if (D1_T3_sensor == 2){
    D1_T3_dis = D1_T3_distance(uSensor2);
    delay(100);
    return D1_T3_dis;
    //Serial.println("sensor 2 selected");
  }
  else if (D1_T3_sensor == 3){
    servo.attach(12);
    D1_T3_rotate(D1_T3_angle);
    delay(300);
    D1_T3_dis = D1_T3_distance(uSensor3);
    return D1_T3_dis;
    //Serial.println("sensor 2 selected");
  }
  else {
    return -1;
  }
}
