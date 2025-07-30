//Improved readability, added wheel test function, custom wheel adjustments, some small fixes 
int in1 = 2; //BACKWARD if HIGH
int in2 = 3; //FORWARD if HIGH
int in3 = 4; //BACKWARD if HIGH
int in4 = 7;//FORWARD if HIGH, These may change depending on the wiring diagram
int ena = 6; //left motor speed analog OUT pin
int enb = 5; // right motor speed analog OUT pin
char Reading;
#define echo 10 //receiver 
#define trig 11 //transmitter 
int mode = 1; //0 is ultrasonic (automatic), 1 is bluetooth (manually controlled)
int distance;
long duration;
int leftspeed = 100;//custom adjustments for each wheel just incase on of the motors is weaker
int rightspeed = 130;
int SPEED = 100; //adjustable overall speeed

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
test(); //to test motors before starting

}


void loop() {
 if((Serial.available() > 0 && mode == 1 )|| Reading == 'A'){
  BLUETOOTH(); 

 }
 else if ( mode == 0 || Reading == 'D') {
  ULTRASONIC();
 }
  delay(100);

}
void motion (bool in1s, bool in2s, bool in3s, bool in4s, int enaS,int enbS)//s for state, S for speed
{
  digitalWrite(in1, in1s);
  digitalWrite(in2, in2s);
  digitalWrite(in3, in3s);
  digitalWrite(in4, in4s);
  analogWrite(ena, enaS);
  analogWrite(enb, enbS); 
}
void FORWARD() {

  Serial.println("FORWARD");
  motion(LOW, HIGH, LOW, HIGH, leftspeed, rightspeed);

}

void BACKWARD() {

  Serial.println("BACKWARD");
  motion(HIGH, LOW, HIGH, LOW, leftspeed, rightspeed);

}

void BACKRIGHT() {

   Serial.println("BACKWARD RIGHT");
  motion(HIGH, LOW, HIGH, LOW, leftspeed, rightspeed -30);

}

void BACKLEFT() {

  Serial.println("BACKWARD LEFT");
  motion(HIGH, LOW, HIGH, LOW, leftspeed -30 , rightspeed);

}
void LEFT() {

  Serial.println("LEFT");
  motion(LOW, LOW, LOW, HIGH, 30, rightspeed);

}

void FORLEFT(){

  Serial.println("FONT LEFT");
  motion(LOW, HIGH, LOW, HIGH, leftspeed -30, rightspeed );

}

void RIGHT() {
  
   Serial.println("RIGHT");
   motion(LOW, HIGH, LOW, LOW, leftspeed, 30);

}

 void FORIGHT(){ 

  Serial.println("FRONT RIGHT");
  motion(LOW, HIGH, LOW, HIGH, leftspeed, rightspeed-30);

}

 

void STOP() {

   Serial.println("STOP");
  motion(LOW, LOW, LOW, LOW, 0, 0);
}

void BLUETOOTH(){
  Reading = Serial.read();


  switch(Reading){
    case 'F' : FORWARD(); Serial.println("F");break;
    case 'B' : BACKWARD(); Serial.println("B");break;
    case 'R' : RIGHT(); Serial.println("R");break;
    case 'L' : LEFT(); Serial.println("L"); break;
    case 'S' : STOP(); Serial.println("S"); break;
    case 'G' : FORIGHT(); Serial.println("FR"); break;
    case 'H' : FORLEFT(); Serial.println("FL"); break;
    case 'J' : BACKRIGHT(); Serial.println("BR"); break;
    case 'K' : BACKLEFT(); Serial.println("BL"); break;
    case 'A': mode = 1;  Serial.println("A");  break; //Bluetooth Activated
    case 'D': mode = 0; Serial.println("D");  break; //Bluetooth Deactivated
 }
}


void ULTRASONIC(){
if(Serial.available()>0){
  Reading = Serial.read();
}
if (Reading == 'D') {
      mode = 1; // switch to Bluetooth mode

digitalWrite(trig,LOW);
delayMicroseconds(2);
digitalWrite(trig,HIGH);
delayMicroseconds(10);
digitalWrite(trig,LOW);
duration = pulseIn(echo,HIGH);
distance = (duration * 0.0343)/2;
Serial.print(distance);
Serial.println(" cm");



if ( distance < 10){
  STOP(); Serial.println("S");
  delay(200);
  BACKWARD(); Serial.println("B"); 
  delay(500);
  LEFT(); Serial.println("L");
  delay(800); //adjustable delays
  }

 else {
  FORWARD(); Serial.println("F");
 }
delay(100);
} }





  void test() {
  Serial.println("Testing Motors");

 
  motion(LOW, HIGH, LOW, LOW, SPEED, 0);
  delay(500);
  
 
  motion(LOW, LOW, LOW, HIGH, 0, SPEED);
  delay(500);

 
  motion(HIGH, LOW, LOW, LOW, SPEED, 0);
  delay(500);


  motion(LOW, LOW, HIGH, LOW, 0, SPEED);
  delay(500);

  STOP();
}

