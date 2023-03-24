


void D1_T2(){
  //Serial.println(int(junction));
  
  // line follow mwthod
  if ( int( junction) == 80) {
    digitalWrite(ledR, LOW);
    digitalWrite(ledL, LOW); 
    IR_check();
    
//    // junction checking
//    if ( (L4_read <= wLine && L2_read <= wLine && L1_read <= wLine && R1_read <= wLine) || (R4_read <= wLine && R2_read <= wLine && R1_read <= wLine && L1_read <= wLine)) {
//      digitalWrite(Buzzer_pin, HIGH);
//      move_forward();
//      delay( junction_delay);
//      digitalWrite(Buzzer_pin, LOW);
//      IR_check();
//
//      Serial.print(L5_read);
//      Serial.print(" ");
//      Serial.println(R5_read);
      
      // Turnning checking
//      if (L5_read <= wLine && L4_read <= wLine && L2_read <= wLine && R2_read <= wLine && R4_read <= wLine && R5_read <= wLine) {
//        // 2 way joint
//        stop_move();
//        delay(500);
//        
//        digitalWrite(ledR, HIGH);
//        digitalWrite(ledL, HIGH);
//
//        digitalWrite(Buzzer_pin, HIGH);
//        delay( 50);
//        digitalWrite(Buzzer_pin, LOW);
//        delay( 50);
//        digitalWrite(Buzzer_pin, HIGH);
//        delay( 50);
//        digitalWrite(Buzzer_pin, LOW);
//        
//        junction = 'R';
//        
//      }
      if ( R1_read <= wLine && R5_read <= wLine) {
        stop_move();
        digitalWrite(Buzzer_pin, HIGH);
        move_forward();
        delay( junction_delay);
        stop_move();
        digitalWrite(Buzzer_pin, LOW);
        IR_check();

        if ( R1_read <= wLine && L1_read <= wLine && L2_read <= wLine && L4_read <= wLine && L5_read <= wLine ) {
          stop_move();
          delay(500);
          
          digitalWrite(ledR, HIGH);
          digitalWrite(ledL, HIGH);
  
          digitalWrite(Buzzer_pin, HIGH);
          delay( 50);
          digitalWrite(Buzzer_pin, LOW);
          delay( 50);
          digitalWrite(Buzzer_pin, HIGH);
          delay( 50);
          digitalWrite(Buzzer_pin, LOW);
          
          junction = 'R';
        }
        else {
          // right turn
          stop_move();
          delay(500);
          
          digitalWrite(ledR, HIGH);
          digitalWrite(ledL, LOW);
  
          digitalWrite(Buzzer_pin, HIGH);
          delay( 50);
          digitalWrite(Buzzer_pin, LOW);
          
          junction = 'R';
        }
      
//        // right turn
//        stop_move();
//        delay(500);
//        
//        digitalWrite(ledR, HIGH);
//        digitalWrite(ledL, LOW);
//
//        digitalWrite(Buzzer_pin, HIGH);
//        delay( 50);
//        digitalWrite(Buzzer_pin, LOW);
//        
//        junction = 'R';
        
      }
      else if ( L1_read <= wLine && L5_read <= wLine) {
        
        digitalWrite(Buzzer_pin, HIGH);
        move_forward();
        delay( junction_delay);
        digitalWrite(Buzzer_pin, LOW);
        IR_check();

        if ( L1_read <= wLine && R1_read <= wLine && R2_read <= wLine && R4_read <= wLine && R5_read <= wLine ) {
          stop_move();
          delay(500);
          
          digitalWrite(ledR, HIGH);
          digitalWrite(ledL, HIGH);
  
          digitalWrite(Buzzer_pin, HIGH);
          delay( 50);
          digitalWrite(Buzzer_pin, LOW);
          delay( 50);
          digitalWrite(Buzzer_pin, HIGH);
          delay( 50);
          digitalWrite(Buzzer_pin, LOW);
          
          junction = 'R';
        }
        else {
          // left turn
          stop_move();
          delay(500);
  
          digitalWrite(ledR, LOW);
          digitalWrite(ledL, HIGH);
  
          digitalWrite(Buzzer_pin, HIGH);
          delay( 50);
          digitalWrite(Buzzer_pin, LOW);
          
          junction = 'L';
        }
//        // left turn
//        stop_move();
//        delay(500);
//
//        digitalWrite(ledR, LOW);
//        digitalWrite(ledL, HIGH);
//
//        digitalWrite(Buzzer_pin, HIGH);
//        delay( 50);
//        digitalWrite(Buzzer_pin, LOW);
//        
//        junction = 'L';

//      }
//      else {
//        // error
//        digitalWrite(led99, HIGH);
//      }
      // -------------------------------------------------------------   
    }
    else if (L4_read > wLine && L3_read > wLine && L1_read > wLine && R1_read > wLine && R3_read > wLine && R4_read > wLine) {
      stop_move();
      
      digitalWrite(ledR, HIGH);
      digitalWrite(ledL, HIGH);
      junction = 'D';
      digitalWrite(Buzzer_pin, HIGH);
    }
    else {
      // PID move forward fuction
      IR_check();
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
      
      if ( L5_read > wLine && L4_read > wLine && R4_read > wLine && R5_read > wLine) {
        digitalWrite(ledR, LOW);
        stop_move();
        delay(500);
        state = false;
      }
      else{
        move_forward();
      }
    }

    stop_move();
//    delay(200000);
    
    // move forward to turning
    move_forward();
    delay(700);     // 650 -----------------------------------------------------------------------------
    digitalWrite(ledR, HIGH);

    stop_move();
    digitalWrite(Buzzer_pin, HIGH);
    delay( 50);
    digitalWrite(Buzzer_pin, LOW);
    
    // turn 90 until line detect
    turn_90_line('R');
    stop_move();
    delay(500);
    junction = 'P';

    stop_move();
    delay(500);
  }
  else if ( int(junction) == 76) {
    digitalWrite(ledL, HIGH);
    //stop_move();
    state = true;
    
    // move to end of junction
    while (state == true) {
      IR_check();
      
      if (  L5_read > wLine && L4_read > wLine && R4_read > wLine && R5_read > wLine) {
        digitalWrite(ledL, LOW);
        stop_move();
        delay(500);
        state = false;
      }
      else{
        move_forward();
      }
    }
    
    // move forward to turning
    move_forward();
    delay(700);    // 700 -------------------------------------------------------------
    
    digitalWrite(ledL, HIGH);

    stop_move();
    digitalWrite(Buzzer_pin, HIGH);
    delay( 50);
    digitalWrite(Buzzer_pin, LOW);
    
    // turn 90 until line detect
    turn_90_line('L');
    junction = 'P';

    stop_move();
    delay(500);
  }
  else if ( int(junction) == 68) {
    stop_move();
    delay(500);
    
    turn_180_line();
    digitalWrite(Buzzer_pin, LOW);
    junction = 'P';

    stop_move();
    delay(500);
  }
  else {
    // error read
    digitalWrite(led99, HIGH);
  }
  // ----------------------------------------------------------------------
}
