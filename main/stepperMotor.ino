
//  stepper.step( STEPS_PER_REVOLUTION); // Down
//  stepper.step( -STEPS_PER_REVOLUTION); // up
//  delay(1000000);


void Arm_Lift( int H_diff) { 

  int H_stepper_value = H_diff - stepper_motor_pos;
  if ( H_stepper_value >= 0) {
    digitalWrite( DIR_PIN, HIGH);
  }    
  else {
    digitalWrite( DIR_PIN, LOW);
  }

  int H_val = 25 * H_stepper_value;

  for ( int i=0; i<H_val; i=i+1) {
    digitalWrite(PUL_PIN, HIGH);
    delayMicroseconds(500);
    digitalWrite(PUL_PIN, LOW);
    delayMicroseconds(500);
  }

  stepper_motor_pos = H_diff;
  
}

void Gripper_set( int set) {
  servo.attach(13);
  
  if ( set == 1) {
    servo.write(180);
    
    for ( int i=0; i< 180; i=i+1) {
      servo.write(180 - i);
      delay(5);
    }
  }
  else {
    servo.write(0);
    
    for ( int i=0; i< 180; i=i+1) {
      servo.write(i);
      delay(5);
    }
  }
}
