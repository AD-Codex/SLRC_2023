


void Arrow_follow() {

  move_forward();

  state = true;

  while ( state == true) {
    if( (L3_read <= wLine && L2_read <= wLine) || (R2_read <= wLine && R3_read <= wLine)) {
      state = false;
    }
  }
  
}
