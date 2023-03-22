


void D1_T2(){
  //Serial.println(int(junction));
  
  // line follow mwthod
  if ( int( junction) == 80) {
    digitalWrite(ledR, LOW);
    digitalWrite(ledL, LOW); 
    IR_check();
    
    // junction checking
    if ( (L5_read <= wLine && L3_read <= wLine) || (R5_read <= wLine && R3_read <= wLine)) {
      digitalWrite(led1, HIGH);
      move_forward(175);
      delay( junction_delay);
      digitalWrite(led1, LOW);
      IR_check();
      
      // Turnning checking
      if ( L5_read <= wLine && L2_read <= wLine && R2_read <= wLine && R5_read <= wLine) {
        // 2 way joint
        digitalWrite(ledR, HIGH);
        digitalWrite(ledL, HIGH);
        junction = 'R';
      }
      else if ( L1_read <= wLine && R1_read <= wLine && R2_read <= wLine && R5_read <= wLine) {
        // right turn
        digitalWrite(ledR, HIGH);
        digitalWrite(ledL, LOW);
        junction = 'R';
      }
      else if ( R1_read <= wLine && L1_read <= wLine && L2_read <= wLine && L5_read <= wLine) {
        // left turn
        digitalWrite(ledR, LOW);
        digitalWrite(ledL, HIGH);
        junction = 'L';
      }
      else {
        // error
        digitalWrite(led99, HIGH);
      }
      // -------------------------------------------------------------   
    }
    else if (L1_read > wLine && R1_read > wLine) {
      digitalWrite(ledR, HIGH);
      digitalWrite(ledL, HIGH);
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
    digitalWrite(ledR, HIGH);
    //stop_move();
    state = true;
    
    // move to end of junction
    while (state == true) {
      IR_check();
      
      if ( L5_read > wLine &&  R5_read > wLine) {
        digitalWrite(ledR, LOW);
        stop_move();
        delay(500);
        state = false;
      }
      else{
        move_forward(175);
      }
    }
    
    // move forward to turning
    move_forward( 175);
    delay(350);
    digitalWrite(ledR, HIGH);
    
    // turn 90 until line detect
    turn_90_line('R');
    stop_move();
    delay(500);
    junction = 'P';
  }
  else if ( int(junction) == 76) {
    digitalWrite(ledL, HIGH);
    //stop_move();
    state = true;
    
    // move to end of junction
    while (state == true) {
      IR_check();
      
      if ( L5_read > wLine && R5_read > wLine) {
        digitalWrite(ledL, LOW);
        stop_move();
         delay(500);
        state = false;
      }
      else{
        move_forward(165);
      }
    }
    
    // move forward to turning
    move_forward( 175);
    delay(350);
    digitalWrite(ledL, HIGH);
    
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
