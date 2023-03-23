// test for black ground with white line



void PID_IR_move() {

  Lsum = 0.0*L5_read + 0.1*L4_read + 0.2*L3_read + 0.3*L2_read + 0.4*L1_read;
  Rsum = 0.5*R1_read + 0.6*R2_read + 0.7*R3_read + 0.8*R4_read + 0.9*R5_read;

  float IR_val1 = Lsum +Rsum;

  int IR_val2 = L5_read + L4_read + L3_read + L2_read + L1_read + R1_read + R2_read + R3_read + R4_read+ R5_read;

  float IR_val = IR_val1*10000/IR_val2;

//  Serial.print(" value :");
//  Serial.print(IR_val);
//  Serial.print(" , ");
//
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
  
  

  if ( L5_read >= wLine && L4_read >= wLine && L3_read >= wLine && L2_read >= wLine && L1_read >= wLine && R1_read >= wLine && R2_read >= wLine && R3_read >= wLine && R4_read >= wLine && R5_read >= wLine ) {
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
    error = PID_MidLine_val - IR_val;
  }

//  int error = midLine_val - val;
  P_val = error;
  I_val = I_val + error;
  D_val = error - last_error;
  last_error = error;

  int motor_speed = P_val*kp + I_val*ki + D_val*kd ;

  int Rmotor_speed = Rbase_speed - motor_speed;
  int Lmotor_speed = Lbase_speed + motor_speed;

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
    Rmotor_speed = max_speed;
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    
  }
  if ( Lmotor_speed >= max_speed) {
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

  Serial.print(Rmotor_speed);
  Serial.print(" ");
  Serial.println(Lmotor_speed);
}
