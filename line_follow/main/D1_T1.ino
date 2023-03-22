
////int B_pos[6] = { 0, 0, 0, 0, 0, 0 };
//int R[3] = { 0, 0, 0};
//
//int R_cube = 0;
//int G_cube = 0;
//int B_cube = 0;
//
//int curr_pos = 3;
//int mov_pos = 0;
//
//int curr_box = 0;
//
////   boxs         tower place
////    1 -------- 4
////          |
////    2 -------- 5
////          |
////    3 -------- 6
////
//
//char P1To2[] = "RR"; 
//char P1To3[] = "RPR";
//char P1To4[] = "P";
//char P1To5[] = "RL";
//char P1To6[] = "RPL";
//
//char P2To1[] = "LL";
//char P2To3[] = "RR";
//char P2To4[] = "LR";
//char P2To5[] = "P";
//char P2To6[] = "RL";
//
//char P3To1[] = "LPL";
//char P3To2[] = "LL";
//char P3To4[] = "LPR";
//char P3To5[] = "LR";
//char P3To6[] = "P";
//
//char P4To5[] = "LL";
//char P4To6[] = "LPL";
//
//char P5To4[] = "RR";
//char P5To6[] = "LL";
//
//char P6To4[] = "RPR";
//char P6To5[] = "RR";


void hanoiTower1( int number1) {
  // move robot till box detect

  // detect box number by color check 3 plce box
//  curr_box = 2;
  Box_color_detect();
  curr_box = Sensor_color_value;

  //
  if ( curr_box == 3) {
    curr_pos = 3;
    R_cube = curr_pos;
    Serial.print(" R ");
    Serial.print( R_cube);
    
    // grip the box
    Gripper_set( 1);
    // lift arm
    Arm_Lift( 'U' , 5);
    
    mov_pos = number1;

    mov_path( curr_pos, mov_pos);
    curr_pos = mov_pos;

    // down arm
    Arm_Lift( 'D' , 5);
    // place box
    Gripper_set( 0);
    Arm_Lift( 'D' , 0);
    
    R_cube = curr_pos;

    if ( mov_pos == 6) {
      mov_pos = curr_pos -3 -1;
      mov_path( curr_pos, mov_pos);
      curr_pos = mov_pos;
      
    }
    else{
      mov_pos = curr_pos -3;
      mov_path( curr_pos, mov_pos);
      curr_pos = mov_pos;
    }

    // detect box number by color check if 3 place box is R and check 2 place
//    curr_box = 1;
    Box_color_detect();
    curr_box = Sensor_color_value;
    
    if ( curr_box == 2) {
      G_cube = curr_pos;
      if ( curr_pos == 2) {
        B_cube = 1;
      }
      else {
        B_cube = 2;
      }      
    }
    else if ( curr_box == 1) {
      B_cube = curr_pos;
      if ( curr_pos == 2) {
        G_cube = 1;
      }
      else {
        G_cube = 2;
      }
    }
    
  }
  else {
    if ( curr_box == 2) {
      curr_pos = 3;
      G_cube = curr_pos;
      Serial.print(" G ");
      Serial.print( G_cube);  
    }
    else if ( curr_box == 1) {
      curr_pos = 3;
      B_cube = curr_pos; 
      Serial.print(" B ");
      Serial.print( B_cube); 
    }
    else {
      Serial.println("error1");
    }

    mov_pos = 2;
    mov_path( curr_pos, mov_pos);
    curr_pos = mov_pos;

    // detect box number by color check if 3 plce box not 3 and move to 2 plce
//    curr_box = 3;
    Box_color_detect();
    curr_box = Sensor_color_value;
    
    if ( curr_box == 3) {
      R_cube = curr_pos;
      
      if ( G_cube == 0 ) {
        G_cube = 1;
      }
      else if ( B_cube == 0) {
        B_cube = 1;
      }
      
  
      // grip the box
      Gripper_set( 1);
      
      // lift arm
      Arm_Lift( 'U' , 5);
      
      mov_pos = number1;
      mov_path( curr_pos, mov_pos);
      curr_pos = mov_pos;
  
      // down arm
      Arm_Lift( 'D' , 5);
      
      // place box
      Gripper_set( 0);
      Arm_Lift( 'D' , 0);
      
      R_cube = curr_pos;
    }
    else {
      if ( G_cube == 0) {
        G_cube = 2;
      }
      else if ( B_cube == 0) {
        B_cube = 2;
      }
      R_cube = 1;
    }
    
  }


  Serial.print(" R ");
  Serial.print( R_cube);
  Serial.print(" G ");
  Serial.print( G_cube);
  Serial.print(" B ");
  Serial.print( B_cube);

  Serial.print(" curr pos ");
  Serial.print( curr_pos);


  Serial.print(" ---2-- ");
  
  if ( curr_pos == number1) {
    // move to G cube
    mov_pos = G_cube;
    mov_path( curr_pos, mov_pos);
    curr_pos = mov_pos;

    // get G cube
    Gripper_set( 1);
    Arm_Lift( 'U' , 35);

    // move to number1
    mov_pos = number1;
    mov_path( curr_pos, mov_pos);
    curr_pos = mov_pos;

    // place G cube
    Arm_Lift( 'D' , 30);
    Gripper_set( 0);
    Arm_Lift( 'D' , 0);

    // move to B cube
    mov_pos = B_cube;
    mov_path( curr_pos, mov_pos);
    curr_pos = mov_pos;

    // get B_cube
    Gripper_set( 1);
    Arm_Lift( 'U' , 65);

    // move to number1
    mov_pos = number1;
    mov_path( curr_pos, mov_pos);
    curr_pos = mov_pos;

    // place B cube 
    Arm_Lift( 'D' , 60);
    Gripper_set( 0);
    Arm_Lift( 'D' , 0);
  }
  else {
    if ( R_cube != 5) {
      // move to R cube
      mov_pos = R_cube;
      mov_path( curr_pos, mov_pos);
      curr_pos = mov_pos;
  
      // get R cube
      Gripper_set( 1);
      Arm_Lift( 'U' , 5);
  
      // move to number1
      mov_pos = number1;
      mov_path( curr_pos, mov_pos);
      curr_pos = mov_pos;

      // place R cube
      Arm_Lift( 'D' , 5);
      Gripper_set( 0);
      Arm_Lift( 'D' , 0);
    }

    if ( curr_pos != G_cube) {
      // move to G cube
      mov_pos = G_cube;
      mov_path( curr_pos, mov_pos);
      curr_pos = mov_pos;  
    }
    

    // get G cube
    Gripper_set( 1);
    Arm_Lift( 'U' , 35);

    // move to number1
    mov_pos = number1;
    mov_path( curr_pos, mov_pos);
    curr_pos = mov_pos;

    // place G cube
    Arm_Lift( 'D' , 30);
    Gripper_set( 0); 
    Arm_Lift( 'D' , 0);

    // move to B cube
    mov_pos = B_cube;
    mov_path( curr_pos, mov_pos);
    curr_pos = mov_pos;

    // get B_cube
    Gripper_set( 1);
    Arm_Lift( 'U' , 65);

    // move to number1
    mov_pos = number1;
    mov_path( curr_pos, mov_pos);
    curr_pos = mov_pos;

    // place B cube 
    Arm_Lift( 'D' , 5);
    Gripper_set( 0);
    Arm_Lift( 'D' , 60);
 
    
  }
  Serial.println();

//  Serial.print(" R ");
//  Serial.print( R_cube);
//  Serial.print(" G ");
//  Serial.print( G_cube);
//  Serial.print(" B ");
//  Serial.print( B_cube);
//
//  Serial.print(" curr pos ");
//  Serial.println( curr_pos);
  
}


void hanoiTower2( int number1, int number2) {
  int number3 = 0;
  if ( number1 == 4) {
    if ( number2 == 5) {
      number3 = 6;
    }
    else {
      number3 = 5;
    }
  }
  else if ( number1 == 5) {
    if ( number2 == 4) {
      number3 = 6;
    }
    else {
      number3 = 4;
    }
  }
  else {
    if ( number2 == 4) {
      number3 = 5;
    }
    else {
      number3 = 4;
    }
  }

  curr_pos = number1;

//  Serial.println( number1);
//  Serial.println( number2);
//  Serial.println( number3);

  // get B cube ( 3 lvl)
  Serial.print(" B ");
  Gripper_set( 0);
  Arm_Lift( 'U' , 60);
  Gripper_set( 1);
  Arm_Lift( 'U' , 5);   // 65

  // move to number2
  mov_pos = number2;
  mov_path( curr_pos, mov_pos);
  curr_pos = mov_pos;

  // place B cube ( 1 lvl)
  Serial.print(" B ");
  Arm_Lift( 'D' , 65);
  Gripper_set( 0);
  Arm_Lift( 'U' , 35);    // 35

  // move to number1
  mov_pos = number1;
  mov_path( curr_pos, mov_pos);
  curr_pos = mov_pos;

  // get G cube ( 2 lvl)
  Serial.print(" G ");
  Arm_Lift( 'D' , 5);
  Gripper_set( 1);
  Arm_Lift( 'U' , 5);   // 35

  // move to number3
  mov_pos = number3;
  mov_path( curr_pos, mov_pos);
  curr_pos = mov_pos;

  // place G cube (1 lvl)
  Serial.print(" G ");
  Arm_Lift( 'D' , 35);
  Gripper_set( 0);      // 0

  // move to B cube
  mov_pos = number2;
  mov_path( curr_pos, mov_pos);
  curr_pos = mov_pos;

  // get B cube ( 1 lvl)
  Serial.print(" B ");
  Gripper_set( 1);
  Arm_Lift( 'U' , 35);   // 35

  // move to number3
  mov_pos = number3;
  mov_path( curr_pos, mov_pos);
  curr_pos = mov_pos;

  // place B cube on G cube ( 2 lvl)
  Serial.print(" B ");
  Arm_Lift( 'D' , 5);
  Gripper_set( 0);
  Arm_Lift( 'U' , 5);     // 35

  // move to R cube
  mov_pos = number1;
  mov_path( curr_pos, mov_pos);
  curr_pos = mov_pos;

  // get R cube ( 1 lvl)
  Serial.print(" R ");
  Arm_Lift( 'D' , 35);
  Gripper_set( 1);
  Arm_Lift( 'U' , 5);     // 5 

  // move to number2
  mov_pos = number2;
  mov_path( curr_pos, mov_pos);
  curr_pos = mov_pos;

  // place R cube ( 1 lvl)
  Serial.print(" R ");
  Arm_Lift( 'D' , 5);
  Gripper_set( 0);
  Arm_Lift( 'U' , 35);    // 35 

  // move to number3
  mov_pos = number3;
  mov_path( curr_pos, mov_pos);
  curr_pos = mov_pos;

  // get B cube that on G cube ( 2 lvl)
  Serial.print(" B ");
  Arm_Lift( 'D' , 5);
  Gripper_set( 1);
  Arm_Lift( 'U' , 5);     // 35

  // move to number1
  mov_pos = number1;
  mov_path( curr_pos, mov_pos);
  curr_pos = mov_pos;

  // place B cube ( 1 lvl)
  Serial.print(" B ");
  Arm_Lift( 'D' , 35);
  Gripper_set( 0);        // 0

  // move to number3
  mov_pos = number3;
  mov_path( curr_pos, mov_pos);
  curr_pos = mov_pos;

  // get G cube ( 1 lvl)
  Serial.print(" G ");
  Gripper_set( 1);
  Arm_Lift( 'U' , 35);    // 35

  // move to number2
  mov_pos = number2;
  mov_path( curr_pos, mov_pos);
  curr_pos = mov_pos;

  // place G cube on R cube ( 2 lvl)
  Serial.print(" G ");
  Arm_Lift( 'D' , 5); 
  Gripper_set( 0);
  Arm_Lift( 'U' , 5);     // 35

  // move to number1
  mov_pos = number1;
  mov_path( curr_pos, mov_pos);
  curr_pos = mov_pos;

  // get B cube ( 1 lvl)
  Serial.print(" B ");
  Arm_Lift( 'D' , 35);
  Gripper_set( 1);
  Arm_Lift( 'U' , 65);     // 65

  // move to number2
  mov_pos = number2;
  mov_path( curr_pos, mov_pos);
  curr_pos = mov_pos;

  // place B cube on G cube  ( 3 lvl)
  Serial.print(" B ");
  Arm_Lift( 'D' , 5);
  Gripper_set( 0);
  Arm_Lift( 'U' , 5);
  
  
}



void mov_path( int start_point, int end_point) {
  Serial.print(" M:");
  Serial.print(start_point);
  Serial.print("-");
  Serial.print(end_point);
  Serial.print("; ");

  char path[] = "";

  if ( start_point == 1) {
    if ( end_point == 2) {
      D1_T1_movePath( P1To2 );
    }
    else if ( end_point == 3) {
      D1_T1_movePath( P1To3 );
    }
    else if ( end_point == 4) {
      D1_T1_movePath( P1To4 );
    }
    else if ( end_point == 5) {
      D1_T1_movePath( P1To5 );
    }
    else if ( end_point == 6) {
      D1_T1_movePath( P1To6 );
    }
  }
  else if ( start_point == 2) {
    if ( end_point == 1) {
      D1_T1_movePath( P2To1 );
    }
    else if ( end_point == 3) {
      D1_T1_movePath( P2To3 );
    }
    else if ( end_point == 4) {
      D1_T1_movePath( P2To4 );
    }
    else if ( end_point == 5) {
      D1_T1_movePath( P2To5 );
    }
    else if ( end_point == 6) {
      D1_T1_movePath( P2To6 );
    }
  }
  else if ( start_point == 3) {
    if ( end_point == 1) {
      D1_T1_movePath( P3To1 );
    }
    else if ( end_point == 2) {
      D1_T1_movePath( P3To2 );
    }
    else if ( end_point == 4) {
      D1_T1_movePath( P3To4 );
    }
    else if ( end_point == 5) {
      D1_T1_movePath( P3To5 );
    }
    else if ( end_point == 6) {
      D1_T1_movePath( P3To6 );
    }
  }
  else if ( start_point == 4) {
    if ( end_point == 1) {
      D1_T1_movePath( P1To4 );
    }
    else if ( end_point == 2) {
      D1_T1_movePath( P2To4 );
    }
    else if ( end_point == 3) {
      D1_T1_movePath( P3To4 );
    }
    else if ( end_point == 5) {
      D1_T1_movePath( P4To5 );
    }
    else if ( end_point == 6) {
      D1_T1_movePath( P4To6 );
    }
  }
  else if ( start_point == 5) {
    if ( end_point == 1) {
      D1_T1_movePath( P1To5 );
    }
    else if ( end_point == 2) {
      D1_T1_movePath( P2To5 );
    }
    else if ( end_point == 3) {
      D1_T1_movePath( P3To5 );
    }
    else if ( end_point == 4) {
      D1_T1_movePath( P5To4 );
    }
    else if ( end_point == 6) {
      D1_T1_movePath( P5To6 );
    }
  }
  else if ( start_point == 6) {
    if ( end_point == 1) {
      D1_T1_movePath( P1To6 );
    }
    else if ( end_point == 2) {
      D1_T1_movePath( P2To6 );
    }
    else if ( end_point == 3) {
      D1_T1_movePath( P3To6 );
    }
    else if ( end_point == 4) {
      D1_T1_movePath( P6To4 );
    }
    else if ( end_point == 5) {
      D1_T1_movePath( P6To5 );
    }
  }
  
}



void D1_T1_movePath( char steps[] ) {
  turn_180_line();
  stop_move();
  delay(500);
  
  for ( int i=0; i<strlen(steps); i=i+1){
    // move till junction detect
    state = true;
    while ( state == true) {
      IR_check();
      // junction detect
      if ( (L5_read <= wLine && L3_read <= wLine) || (R5_read <= wLine && R3_read <= wLine)) {
        stop_move();
        delay(500);
        state = false;
      }
      else {
        // else move PID
        PID_IR_move();
        delay(10);
      }
    }
    
    // move forward to turning point
    move_forward( 175);
    delay(650);
    stop_move();
    delay(500);
    
    // turing given direction
    turn_90_line( steps[i]);
    stop_move();
    delay(500);  
  }
  
  // move till end detect
  state = true;
  while ( state == true) {
    IR_check();
    // end of the path
    if ( (L5_read <= wLine && L3_read <= wLine) && (R5_read <= wLine && R3_read <= wLine)) {
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
