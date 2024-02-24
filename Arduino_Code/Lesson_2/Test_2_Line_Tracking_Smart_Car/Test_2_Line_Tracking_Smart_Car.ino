int M1_1=6;             
int M1_2=10;             
int M2_1=5;          
int M2_2=9;  

void Infrared_Tracing() {
  int Left_Tra_Value = 1;
  int Center_Tra_Value = 1;
  int Right_Tra_Value = 1;
  int Black = 1;
  Left_Tra_Value = digitalRead(4);
  Center_Tra_Value = digitalRead(11);
  Right_Tra_Value = digitalRead(2);
  if (Left_Tra_Value != Black && (Center_Tra_Value == Black && Right_Tra_Value != Black)) {//010
    advance();
  } else if (Left_Tra_Value == Black && (Center_Tra_Value == Black && Right_Tra_Value != Black)) {//110
    turnL();
  } else if (Left_Tra_Value == Black && (Center_Tra_Value != Black && Right_Tra_Value != Black)) {//100
    turnL();
  } else if (Left_Tra_Value != Black && (Center_Tra_Value != Black && Right_Tra_Value == Black)) {//001
    turnR();
  } else if (Left_Tra_Value != Black && (Center_Tra_Value == Black && Right_Tra_Value == Black)) {//011
    turnR();
  } else if (Left_Tra_Value == Black && (Center_Tra_Value == Black && Right_Tra_Value == Black)){//111
    stopp();
  }
}

void setup(){
  Serial.begin(9600);
  pinMode(4, INPUT);//Left line tracking sensor is connected to the digital IO port D4
  pinMode(11, INPUT);//Center line patrol sensor is connected to the digital IO port D11
  pinMode(2, INPUT);//Right line tracking sensor is connected to the digital IO port D2
  pinMode(M1_1,OUTPUT);  
  pinMode(M1_2,OUTPUT);  
  pinMode(M2_1,OUTPUT); 
  pinMode(M2_2,OUTPUT); 
}

void loop(){
  Infrared_Tracing();

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
