// test for black ground with white line



void PID_IR_move() {

  sum = 0*L4_read + 1*L3_read + 2*L2_read + 3*L1_read + 4*R1_read + 5*R2_read + 6*R3_read + 7*R4_read;
  val = sum*1000/(L4_read + L3_read + L2_read + L1_read + R1_read + R2_read + R3_read + R4_read );

//  Serial.print(" val:");
//  Serial.print(val);
//  Serial.print(" ");
//  
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
//  Serial.print(" I_val");
//  Serial.print( I_val);
//  Serial.println();

  if ( L4_read >= wLine && L3_read >= wLine && L2_read >= wLine && L1_read >= wLine && R1_read >= wLine && R2_read >= wLine && R3_read >= wLine && R4_read >= wLine ) {
    if ( I_val < 0) {
      digitalWrite(38, LOW);
      digitalWrite(36, HIGH);
      error = -10;      
    }
    else if ( I_val > 0) {
      digitalWrite(38, HIGH);
      digitalWrite(36, LOW);
      error = +10;
    }
  }
  else{
    digitalWrite(38, HIGH);
    digitalWrite(36, HIGH);
    error = midLine_val - val;
  }

//  int error = midLine_val - val;
  P_val = error;
  I_val = I_val + error;
  D_val = error - last_error;
  last_error = error;

  int motor_speed = P_val*kp + I_val*ki + D_val*kd ;

  int Rmotor_speed = base_speed - motor_speed;
  int Lmotor_speed = base_speed + motor_speed;

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
}
