void setup()
{
  Serial.begin(9600);
  pinMode(4, INPUT);//Left line tracking sensor is connected to the digital IO port D4
  pinMode(11, INPUT);//Center line patrol sensor is connected to the digital IO port D11
  pinMode(2, INPUT);//Right line tracking sensor is connected to the digital IO port D2
}

void loop()
{
  Infrared_Tracing();

}

/*Define a sub-function, 
 the function of this function is to read the output signal 
 of the infrared tracking sensor and print it to the serial monitor*/
void Infrared_Tracing() 
{
  int Left_Tra_Value = 1;
  int Center_Tra_Value = 1;
  int Right_Tra_Value = 1;
  Left_Tra_Value = digitalRead(4);
  Center_Tra_Value = digitalRead(11);
  Right_Tra_Value = digitalRead(2);
  Serial.print("Left Tracking value:");
  Serial.println(Left_Tra_Value);
  Serial.print("Center Tracking value:");
  Serial.println(Center_Tra_Value);
  Serial.print("Right Tracking value:");
  Serial.println(Right_Tra_Value);
  Serial.println("");
  delay(500);
}
