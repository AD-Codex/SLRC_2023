


void D1_T2(){
  //Serial.println(int(junction));
  
  // line follow mwthod
  if ( int( junction) == 80) {
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW); 
    IR_check();
    
    // junction checking
    if ( (L4_read <= wLine && L3_read <= wLine) || (R4_read <= wLine && R3_read <= wLine)) {
      digitalWrite(led1, HIGH);
      move_forward(150);
      delay( junction_delay);
      digitalWrite(led1, LOW);
      IR_check();
      
      // Turnning checking
      if ( L4_read <= wLine && L2_read <= wLine && R2_read <= wLine && R4_read <= wLine) {
        // 2 way joint
        digitalWrite(led2, HIGH);
        digitalWrite(led3, HIGH);
        junction = 'R';
      }
      else if ( L1_read <= wLine && R1_read <= wLine && R2_read <= wLine && R4_read <= wLine) {
        // right turn
        digitalWrite(led2, HIGH);
        digitalWrite(led3, LOW);
        junction = 'R';
      }
      else if ( R1_read <= wLine && L1_read <= wLine && L2_read <= wLine && L4_read <= wLine) {
        // left turn
        digitalWrite(led2, LOW);
        digitalWrite(led3, HIGH);
        junction = 'L';
      }
      else {
        // error
        digitalWrite(led99, HIGH);
      }
      // -------------------------------------------------------------   
    }
    else if (L1_read > wLine && R1_read > wLine) {
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      junction = 'D';
      stop_move();
    }
    else {
      // PID move forward fuction
      PID_IR_move();
    }
    // -----------------------------------------------------------------
  }
  else if ( int(junction) == 82) {
    digitalWrite(led2, HIGH);
    //stop_move();
    state = true;
    
    // move to end of junction
    while (state == true) {
      IR_check();
      
      if ( L4_read > wLine &&  R4_read > wLine) {
        digitalWrite(led2, LOW);
        stop_move();
        //delay(500);
        state = false;
      }
      else{
        move_forward(150);
      }
    }
    
    // move forward to turning
    move_forward( 150);
    delay(350);
    digitalWrite(led2, HIGH);
    
    // turn 90 until line detect
    turn_90_line('R');
    stop_move();
    //delay(500);
    junction = 'P';
  }
  else if ( int(junction) == 76) {
    digitalWrite(led3, HIGH);
    //stop_move();
    state = true;
    
    // move to end of junction
    while (state == true) {
      IR_check();
      
      if ( L4_read > wLine && R4_read > wLine) {
        digitalWrite(led3, LOW);
        stop_move();
        // delay(500);
        state = false;
      }
      else{
        move_forward(150);
      }
    }
    
    // move forward to turning
    move_forward( 150);
    delay(350);
    digitalWrite(led3, HIGH);
    
    // turn 90 until line detect
    turn_90_line('L');
    junction = 'P';  
  }
  else if ( int(junction) == 68) {
    turn_180_line();
    junction = 'P'; 
  }
  else {
    // error read
    digitalWrite(led99, HIGH);
  }
  // ----------------------------------------------------------------------
}
