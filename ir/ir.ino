int L1_read = 0;
int L2_read = 0;
int L3_read = 0;
int L4_read = 0;
int R1_read = 0;
int R2_read = 0;
int R3_read = 0;
int R4_read = 0;

float sum =0;
float val = 0.00;

void setup() {
  pinMode( A0, INPUT);
  pinMode( A1, INPUT);
  pinMode( A2, INPUT);
  pinMode( A3, INPUT);
  pinMode( A4, INPUT);
  pinMode( A5, INPUT);
  pinMode( A6, INPUT);
  pinMode( A7, INPUT);
  pinMode( 38, OUTPUT);
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(34, HIGH);
  
  L4_read = analogRead(A0);
  L3_read = analogRead(A1);
  L2_read = analogRead(A2);
  L1_read = analogRead(A3);
  R1_read = analogRead(A4);
  R2_read = analogRead(A5);
  R3_read = analogRead(A6);
  R4_read = analogRead(A7);

  sum = 0*L4_read + 1*L3_read + 2*L2_read + 3*L1_read + 4*R1_read + 5*R2_read + 6*R3_read + 7*R4_read;
  val = sum*1000/(L4_read + L3_read + L2_read + L1_read + R1_read + R2_read + R3_read + R4_read );
  Serial.print(" value :");
  Serial.print(val);
  Serial.print(" , ");

  Serial.print( L4_read);
  Serial.print(" ");
  Serial.print( L3_read);
  Serial.print(" ");
  Serial.print( L2_read);
  Serial.print(" ");
  Serial.print( L1_read);
  Serial.print(" ");
  Serial.print( R1_read);
  Serial.print(" ");
  Serial.print( R2_read);
  Serial.print(" ");
  Serial.print( R3_read);
  Serial.print(" ");
  Serial.print( R4_read);
  Serial.println();
  delay(100);
  
}
