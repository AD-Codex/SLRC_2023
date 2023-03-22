


void Arm_Lift( char moving , int H_diff) { 
  if ( int( moving) == 85) {
    digitalWrite( dirpin, HIGH);
  }    
  else if ( int( moving) == 68) {
    digitalWrite( dirpin, LOW);
  }

  int H_val = 25 * H_diff;

  for ( int i=0; i<H_val; i=i+1) {
    digitalWrite(stepin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepin, LOW);
    delayMicroseconds(1000);
  }
  
}

void Gripper_set( int set) {
  if ( set == 1) {
    myservo.write(180);
    
    for ( int i=0; i< 180; i=i+1) {
      myservo.write(180 - i);
      delay(5);
    }
  }
  else {
    myservo.write(0);
    
    for ( int i=0; i< 180; i=i+1) {
      myservo.write(i);
      delay(5);
    }
  }
}
