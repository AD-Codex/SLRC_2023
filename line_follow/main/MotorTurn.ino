


void turn_180_line() {
  turn_right(150);
  delay(800);
  state = true;   
  // turn to line detect
  while ( state == true) {
    IR_check();
    if ( L3_read > wLine && R3_read <= wLine && R2_read <= wLine && R4_read > wLine ) {
//    if ( L3_read > wLine && L1_read <= wLine && R1_read <= wLine && R2_read > wLine ) {
      stop_move();
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      state = false;  
    }
  }
}



void turn_90_line( char dir) {
  // turn right
  if ( int(dir) == 82 ) {
    turn_right(150);
    delay(450);
    state = true;
    // turn to line detect
    while ( state == true) {
      IR_check();
      if ( L3_read > wLine && L1_read <= wLine && R1_read <= wLine && R3_read > wLine ) {
        stop_move();
        digitalWrite(led2, LOW);
        state = false;  
      }
    }
  }
  // turn left
  else if ( int(dir) == 76) {
    turn_left(150);
    delay(450);
    state = true;

    // turn to line detect
    while ( state == true) {
      IR_check();
      if ( L3_read > wLine && L1_read <= wLine && R1_read <= wLine && R3_read > wLine) {
        stop_move();
        digitalWrite(led3, LOW);
        state = false;  
      }
    }
  }
  else if ( int(dir) == 83) {
    Serial.println(" S ");
  }
  else{
    Serial.println(" error");
  }
}
