const int motorFL=9;  // motor forward left in3
const int motorFR=10; // motor foward right in2
const int motorBL=6;  // motor back left in4
const int motorBR=11; // motor back right in1
const int MOTORSPEED = 255;
const int MOTORSTOP = LOW;

const int trigPin=12; // ultra sonic
const int echoPin=13;

const int ss1=7; // hong ngoai
const int ss2=2;
const int ss3=3;
const int ss4=4;
const int ss5=5;
const int DARK=0;  // dark color (not the led is light out)
const int LIGHT=1; // light color (not the led is light up)
int count = 0;

void setup() {
  pinMode(motorFL, OUTPUT);
  pinMode(motorFR, OUTPUT);
  pinMode(motorBL, OUTPUT);
  pinMode(motorBR, OUTPUT);
  
  pinMode(trigPin, OUTPUT);  //chan echo se nhan tin hieu
  pinMode(echoPin, INPUT);

  pinMode(ss1, INPUT);
  pinMode(ss2, INPUT);
  pinMode(ss3, INPUT);
  pinMode(ss4, INPUT);
  pinMode(ss5, INPUT);
  
  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  int sFLeft = MOTORSPEED, sFRight = MOTORSPEED;
  int sBLeft = MOTORSTOP, sBRight = MOTORSTOP;
  int rs1 = readSs(ss1);
  int rs2 = readSs(ss2);
  int rs3 = readSs(ss3);
  int rs4 = readSs(ss4);
  int rs5 = readSs(ss5);
  
  if (getDistance() > 20.0) {
    
    if (( // queo phai
        (rs2 == DARK) || (rs1 == DARK)
       )&& (
        (rs4 == LIGHT) || (rs5 == LIGHT)
       )) {
      sFLeft = MOTORSTOP;
      sFRight = MOTORSPEED;
      sBLeft = MOTORSPEED / 2;
    }
    
    if (( // queo trai
        (rs2 == LIGHT) || (rs1 == LIGHT)
       )&& (
        (rs4 == DARK) || (rs5 == DARK)
       )) {
      sFLeft = MOTORSPEED;
      sFRight = MOTORSTOP;
      sBRight = MOTORSPEED / 2;
    }

//    if ((rs3 == DARK) && (rs1 == rs2) && (rs2 == rs4) && (rs4 == rs5) && (rs1 == LIGHT)) {
//      sLeft = MOTORSPEED;
//      sRight = MOTORSPEED;
//    }
    if ((rs1 == rs2) && (rs2 == rs3) && (rs3 == rs4) && (rs4 == rs5) && (rs1 == LIGHT)) {
      if (count >= 5) {
        sFLeft = MOTORSTOP;
        sFRight = MOTORSTOP;
        sBLeft = MOTORSPEED/2;
        sBRight = MOTORSPEED/2;
      }
      count++;
      if (count > 20) count = -count;
    } else {
      count = 0;
    }
  } else {
    sFLeft = MOTORSTOP;
    sFRight = MOTORSTOP;
    sBLeft = MOTORSTOP;
    sBRight = MOTORSTOP;
  }
  Serial.print("sFLeft: ");
  Serial.println(sFLeft);
  Serial.print("sFRight: ");
  Serial.println(sFRight);
  Serial.print("sBLeft: ");
  Serial.println(sBLeft);
  Serial.print("sBRight: ");
  Serial.println(sBRight);
  Serial.println("-----------");
  runMotorF(sFLeft, sFRight);
  runMotorB(sBLeft, sBRight);
  delay(100);
}

void runMotorF(int left, int right) {
  analogWrite(motorFL, left);
  analogWrite(motorFR, right);
}

void runMotorB(int left, int right) {
  analogWrite(motorBL, left);
  analogWrite(motorBR, right);
}

int getDistance() {
  return 30;
//  long duration, inches;
//  double cm;
//  digitalWrite(trigPin,0);
//  delayMicroseconds(2);
//  digitalWrite(trigPin,1);
//  delayMicroseconds(5);
//  digitalWrite(trigPin,0);
//  duration = pulseIn(echoPin, HIGH);
//  // convert the time into a distance
//  inches = microsecondsToInches(duration);
//  cm = microsecondsToCentimeters(duration);
////  Serial.print(inches);
////  Serial.print("in, ");
////  Serial.print(cm);
////  Serial.print("cm");
////  Serial.println();
//  return cm;
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

double microsecondsToCentimeters(long microseconds) {
  return microseconds / 29.412 / 2;
}

int readSs(int ss) {
  return digitalRead(ss);
}
