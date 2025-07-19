int in1 = 2; // Forward if HIGH
int in2 = 3; // Backward if HIGH
int in3 = 4; // Backward if HIGH
int in4 = 7; // Forward if HIGH, these may change depending on the wiring diagram
int ena = 6; // Left motor speed analog OUT pin
int enb = 5; // Right motor speed analog OUT pin
char Reading;
#define echo 10 // Receiver
#define trig 11 // Transmitter
int SPEED = 120; // Adjustable speed
int mode = 1; // 0 is ultrasonic (automatic), 1 is Bluetooth (manually controlled)
int distance;
long duration;

void setup() {
Serial.begin(9600);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
pinMode(ena, OUTPUT);
pinMode(enb, OUTPUT);
pinMode(echo, INPUT);
pinMode(trig, OUTPUT);
}

void loop() {
 if(Serial.available() > 0 && mode == 1 || Reading == 'A'){
  BLUETOOTH(); 
 }
 else if ( mode == 0 || Reading == 'D') {
  ULTRASONIC();
 }
}

void FORWARD() {
  Serial.println("FORWARD");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, SPEED);
  analogWrite(enb, SPEED); 
}

void BACKWARD() {
  Serial.println("BACKWARD");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, SPEED);
  analogWrite(enb, SPEED);
}

void BACKRIGHT() {
  Serial.println("BACKWARD RIGHT");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, SPEED);
  analogWrite(enb, SPEED -30);
}

void BACKLEFT() {
  Serial.println("BACKWARD LEFT");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, SPEED -30);
  analogWrite(enb, SPEED);
}

void LEFT() {
  Serial.println("LEFT");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, 0);
  analogWrite(enb, SPEED);
}

void FORLEFT(){
  Serial.println("FORWARD LEFT");
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, SPEED -30);
  analogWrite(enb, SPEED );
}

void RIGHT() {
  Serial.println("RIGHT");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(ena, SPEED);
  analogWrite(enb, 0);
}

void FORIGHT(){
  Serial.println("FRONT RIGHT");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, SPEED);
  analogWrite(enb, SPEED - 30);
}

void STOP() {
  Serial.println("STOP");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(ena, 0);
  analogWrite(enb, 0);
}

void BLUETOOTH(){
  Reading = Serial.read();

  switch(Reading){
    case 'F' : FORWARD(); Serial.println("F"); break;
    case 'B' : BACKWARD(); Serial.println("B"); break;
    case 'R' : RIGHT(); Serial.println("R"); break;
    case 'L' : LEFT(); Serial.println("L"); break;
    case 'S' : STOP(); Serial.println("S"); break;
    case 'G' : FORIGHT(); Serial.println("FR"); break;
    case 'H' : FORLEFT(); Serial.println("FL"); break;
    case 'J' : BACKRIGHT(); Serial.println("BR"); break;
    case 'K' : BACKLEFT(); Serial.println("BL"); break;
    case 'A': mode = 1; Serial.println("A"); break; // Bluetooth Activated
    case 'D': mode = 0; Serial.println("D"); break; // Bluetooth Deactivated
  }
}

void ULTRASONIC(){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration * 0.0343)/2;
  Serial.print(distance);
  Serial.println(" cm");
  Reading = Serial.read();

  if (distance < 10){
    STOP(); Serial.println("S");
    delay(200);
    BACKWARD(); Serial.println("B"); 
    delay(500);
    LEFT(); Serial.println("L");
    delay(800); // Adjustable delays
  }
  else if (Reading == 'D'){
    BLUETOOTH(); // If 'D' is called then switch to Bluetooth
  }
  else {
    FORWARD(); Serial.println("F");
  }
  delay(100);
}
