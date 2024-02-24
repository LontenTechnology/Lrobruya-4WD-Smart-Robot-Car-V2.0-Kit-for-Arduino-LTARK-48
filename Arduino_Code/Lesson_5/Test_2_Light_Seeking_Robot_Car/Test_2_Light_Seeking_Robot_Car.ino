int M1_1=6;             
int M1_2=10;             
int M2_1=5;          
int M2_2=9;

volatile float leftSensorValue;
volatile float rightSensorValue;

void Light_Seeking() {
  leftSensorValue = analogRead(A3);
  rightSensorValue = analogRead(A2);
  if (leftSensorValue < 500 && rightSensorValue < 500) {
    // Light is detected on both sides, and the car is moving forward
    advance();
  } else if (leftSensorValue < 100) {
    // Light detected on the left side, car turning left
    turnL();
  } else if (rightSensorValue < 100) {
    // Light detected on the right side, car turning right
    turnR();
  } else {
    // No light detected on both sides, the car stopped
    stopp();
  }
}

void setup(){
  leftSensorValue = 0;
  rightSensorValue = 0;
  Serial.begin(9600);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(M1_1,OUTPUT);  
  pinMode(M1_2,OUTPUT);  
  pinMode(M2_1,OUTPUT); 
  pinMode(M2_2,OUTPUT); 
}

void loop(){
  Light_Seeking();

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

