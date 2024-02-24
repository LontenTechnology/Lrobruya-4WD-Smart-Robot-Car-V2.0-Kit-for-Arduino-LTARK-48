int M1_1 = 6;
int M1_2 = 10;
int M2_1 = 5;
int M2_2 = 9;
volatile int D_mix;
volatile int D_mid;
volatile int D_max;
volatile int Front_Distance;
volatile int Right_IR_Value;
volatile int Left_IR_Value;

void Ultrasonic_obstacle_avoidance() {
  if (Front_Distance <= D_mid) {
      back();
      delay(100);
      turnR();
      delay(300);
    }
  else{
    advance();
  }
}

void Infrared_Obstacle_Avoidance() {
  if (Left_IR_Value == 0 && Right_IR_Value == 1) {
    turnR();
    delay(300);
    stopp();
  } else if (Left_IR_Value == 1 && Right_IR_Value == 0) {
    turnL();
    delay(300);
    stopp();
  } else if (Left_IR_Value == 1 && Right_IR_Value == 1) {
    //There are no obstacles on either side
    Ultrasonic_obstacle_avoidance();
  }
}

float checkdistance() {
  digitalWrite(12, LOW);
  delayMicroseconds(2);
  digitalWrite(12, HIGH);
  delayMicroseconds(10);
  digitalWrite(12, LOW);
  float distance = pulseIn(13, HIGH) / 58.00;
  delay(10);
  return distance;
}

void Obstacle_Avoidance_Main() {
  Left_IR_Value = digitalRead(A1);
  Right_IR_Value = digitalRead(A0);
  Front_Distance = checkdistance();
//  Serial.println(Front_Distance);
  Infrared_Obstacle_Avoidance();
}

void setup() {
  pinMode(M1_1, OUTPUT);
  pinMode(M1_2, OUTPUT);
  pinMode(M2_1, OUTPUT);
  pinMode(M2_2, OUTPUT);
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(13, INPUT);
  D_mix = 5;
  D_mid = 10;
  D_max = 400;
  Front_Distance = 0;
  Right_IR_Value = 1;
  Left_IR_Value = 1;
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop() {
  Obstacle_Avoidance_Main();
}
void advance()    //  going forward
{
  digitalWrite(M1_1, LOW);
  analogWrite(M1_2, 100);
  digitalWrite(M2_1, LOW);
  analogWrite(M2_2, 100);
}
void back()         //back up
{
  analogWrite(M1_1, 100);
  digitalWrite(M1_2, LOW);
  analogWrite(M2_1, 100);
  digitalWrite(M2_2, LOW);
}
void turnR()         //turn right
{
  analogWrite(M1_1, 100);
  digitalWrite(M1_2, LOW);
  digitalWrite(M2_1, LOW);
  analogWrite(M2_2, 100);
}
void turnL()        //turn left
{
  digitalWrite(M1_1, LOW);
  analogWrite(M1_2, 100);
  analogWrite(M2_1, 100);
  digitalWrite(M2_2, LOW);
}
void stopp()        //stop
{
  digitalWrite(M1_1, LOW);
  digitalWrite(M1_2, LOW);
  digitalWrite(M2_1, LOW);
  digitalWrite(M2_2, LOW);
}
