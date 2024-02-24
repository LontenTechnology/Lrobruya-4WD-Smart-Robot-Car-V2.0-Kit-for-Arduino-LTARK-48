int M1_1=6;             
int M1_2=10;             
int M2_1=5;          
int M2_2=9;           

void setup()
{
  pinMode(M1_1,OUTPUT);  
  pinMode(M1_2,OUTPUT);  
  pinMode(M2_1,OUTPUT); 
  pinMode(M2_2,OUTPUT); 
}
void loop()
{
  advance();
  delay(2000);//waiting 2 seconds
  
  back();
  delay(2000);
  
  turnL();
  delay(2000);
  
  turnR();
  delay(2000);
  
  stopp();
  delay(2000);
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
