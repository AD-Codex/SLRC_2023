

void D1_T1_movePath( char steps[] ) {
  turn_180_line();
  stop_move();
  delay(1000);
  
  for ( int i=0; i<strlen(steps); i=i+1){
    // move till junction detect
    state = true;
    while ( state == true) {
      IR_check();
      // junction detect
      if ( (L4_read <= wLine && L3_read <= wLine) || (R4_read <= wLine && R3_read <= wLine)) {
        stop_move();
        //delay(1000);
        state = false;
      }
      else {
        // else move PID
        PID_IR_move();
        delay(10);
      }
    }
    
    // move forward to turning point
    move_forward( 150);
    delay(650);
    stop_move();
    //delay(1000);
    
    // turing given direction
    turn_90_line( steps[i]);
    stop_move();
    //delay(1000);  
  }
  
  // move till end detect
  state = true;
  while ( state == true) {
    IR_check();
    // end of the path
    if ( (L4_read <= wLine && L3_read <= wLine) && (R4_read <= wLine && R3_read <= wLine)) {
      stop_move();
      state = false;
      delay(100000);
    }
    else {
      // else move PID
      PID_IR_move();
      delay(10);
    }
  }
}
