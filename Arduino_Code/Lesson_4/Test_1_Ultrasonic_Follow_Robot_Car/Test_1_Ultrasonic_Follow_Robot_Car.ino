volatile int D_mix;
volatile int D_mid;
volatile int D_max;

int M1_1=6;             
int M1_2=10;             
int M2_1=5;          
int M2_2=9; 

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

void Ultrasonic_Follow() {
  int Infrared_Trigger_Flag = 0;
  int Front_Distance = 0;
  int Right_IR_Value = 1;
  int Left_IR_Value = 1;
  Left_IR_Value = digitalRead(A1);
  Right_IR_Value = digitalRead(A0);
  Front_Distance = checkdistance();
  if (Front_Distance < D_mix && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
    stopp();
  } else if (Front_Distance < D_mix && (Left_IR_Value == Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
    turnL();
  } else if (Front_Distance < D_mix && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value == Infrared_Trigger_Flag)) {
    turnR();
  } else if (Front_Distance > D_mid && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
    advance();
  } else if (Front_Distance > D_mid && (Left_IR_Value == Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
    turnL();
  } else if (Front_Distance > D_mid && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value == Infrared_Trigger_Flag)) {
    turnR();
  }
}

void setup(){
  D_mix = 5;
  D_mid = 10;
  D_max = 400;
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(12, OUTPUT);
  pinMode(13, INPUT);

  pinMode(M1_1,OUTPUT);  
  pinMode(M1_2,OUTPUT);  
  pinMode(M2_1,OUTPUT); 
  pinMode(M2_2,OUTPUT); 
}

void loop(){
  Ultrasonic_Follow();
}

void advance()    //  going forward
{
  digitalWrite(M1_1,LOW);  
  analogWrite(M1_2,100);
  digitalWrite(M2_1,LOW);  
  analogWrite(M2_2,100);
}
void back()         //back up
{
  analogWrite(M1_1,100);
  digitalWrite(M1_2,LOW);  
  analogWrite(M2_1,100);
  digitalWrite(M2_2,LOW);  
}
void turnR()         //turn right
{
  analogWrite(M1_1,100);
  digitalWrite(M1_2,LOW);   
  digitalWrite(M2_1,LOW);  
  analogWrite(M2_2,100);
}
void turnL()        //turn left
{
  digitalWrite(M1_1,LOW);  
  analogWrite(M1_2,100);
  analogWrite(M2_1,100);  
  digitalWrite(M2_2,LOW); 
}    
void stopp()        //stop
{
  digitalWrite(M1_1,LOW);  
  digitalWrite(M1_2,LOW);
  digitalWrite(M2_1,LOW);  
  digitalWrite(M2_2,LOW);
}
