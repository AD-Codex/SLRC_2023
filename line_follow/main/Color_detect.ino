


void Box_color_detect() {
  // Read Red value
  Sensor_redPW = Sensor_getRedPW();
  Sensor_bluePW = Sensor_getBluePW();
  Sensor_greenPW = Sensor_getGreenPW();
  int Sensor_colmean=( Sensor_redPW + Sensor_greenPW + Sensor_bluePW)/3;
  
  Serial.print("redPW=");
  Serial.println(Sensor_redPW);
  Serial.print("bluePW=");
  Serial.println(Sensor_bluePW);
  Serial.print("greenPW=");
  Serial.println(Sensor_greenPW);
  if(( Sensor_bluePW < Sensor_redPW) && ( Sensor_bluePW < Sensor_greenPW) && ( Sensor_colmean > 60) && ( Sensor_colmean < 200)){
    Sensor_color_value = 1;
    digitalWrite( ledRed, LOW);
    digitalWrite( ledGreen, LOW);
    digitalWrite( ledBlue, HIGH);
    Serial.println("blue");
  }
  else if(( Sensor_redPW < Sensor_bluePW) && ( Sensor_redPW < Sensor_greenPW) && ( Sensor_colmean > 60) && ( Sensor_colmean < 200)){
    Sensor_color_value = 3;
    digitalWrite( ledRed, HIGH);
    digitalWrite( ledGreen, LOW);
    digitalWrite( ledBlue, LOW);    
    Serial.println("red");
  }
  else if(( Sensor_greenPW < Sensor_bluePW) && ( Sensor_greenPW < Sensor_redPW) && ( Sensor_colmean>60) && ( Sensor_colmean < 200)){
    Sensor_color_value = 2;
    digitalWrite( ledRed, LOW);
    digitalWrite( ledGreen, HIGH);
    digitalWrite( ledBlue, LOW);
    Serial.println("green");
  }
  else{
    Sensor_color_value = 0;
    digitalWrite( ledRed, LOW);
    digitalWrite( ledGreen, LOW);
    digitalWrite( ledBlue, LOW); 
    Serial.print( curr_box);
    Serial.println("ERROR");
  }
 
}


// Function to read Red Pulse Widths
int Sensor_getRedPW() {
  // Set sensor to read Red only
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int Sensor_PW;
  // Read the output Pulse Width
  Sensor_PW = pulseIn(Color_sensor_in, LOW);
  // Return the value
  return Sensor_PW;
}

// Function to read Green Pulse Widths
int Sensor_getGreenPW() {
  // Set sensor to read Green only
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int Sensor_PW;
  // Read the output Pulse Width
  Sensor_PW = pulseIn(Color_sensor_in, LOW);
  // Return the value
  return Sensor_PW;
}

// Function to read Blue Pulse Widths
int Sensor_getBluePW() {
  // Set sensor to read Blue only
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int Sensor_PW;
  // Read the output Pulse Width
  Sensor_PW = pulseIn(Color_sensor_in, LOW);
  // Return the value
  return Sensor_PW;
}
