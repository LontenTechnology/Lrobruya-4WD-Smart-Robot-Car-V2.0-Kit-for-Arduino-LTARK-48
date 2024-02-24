#define SCL_Pin A5 //Set the clock pin to A5
#define SDA_Pin A4 //Set data pin to A4
//Array, used to store the data of pattern, can be calculated by yourself or obtained from the modulus tool
unsigned char start01[] =
{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
unsigned char front[] =
{0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x12, 0x09, 0x12, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char back01[] =
{0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x48, 0x90, 0x48, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char left[] =
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x28, 0x10, 0x44, 0x28, 0x10, 0x44, 0x28, 0x10, 0x00};
unsigned char right[] =
{0x00, 0x10, 0x28, 0x44, 0x10, 0x28, 0x44, 0x10, 0x28, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char STOP01[] =
{0x2E, 0x2A, 0x3A, 0x00, 0x02, 0x3E, 0x02, 0x00, 0x3E, 0x22, 0x3E, 0x00, 0x3E, 0x0A, 0x0E, 0x00};
unsigned char clear[] =
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char speed_a[] =
{0x00, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0xff, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00};
unsigned char speed_d[] =
{0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0xff, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00};
unsigned char smile[] = 
{0x00, 0x00, 0x1c, 0x02, 0x02, 0x02, 0x5c, 0x40, 0x40, 0x5c, 0x02, 0x02, 0x02, 0x1c, 0x00, 0x00};

int M1_1 = 6;
int M1_2 = 10;
int M2_1 = 5;
int M2_2 = 9;
int speeds = 150; //Set the initial speed to 150

#define SensorLeft    4   //sensor left pin of line tracking module 
#define SensorMiddle  11   //sensor middle pin of line tracking module
#define SensorRight   2  //sensor right pin of line tracking module

int inputPin = 13; // ultrasonic module   ECHO to 13
int outputPin = 12; // ultrasonic module  TRIG to 12
int Front_Distance = 0;
int Right_IR_Value = 1;
int Left_IR_Value = 1;

unsigned char bluetooth_data;

volatile float leftSensorValue;
volatile float rightSensorValue;

int flag = 0;

void Line_Tracking(void) //function of line tracking
{
  flag = 0;
  while (flag == 0)
  {
    int Left_Tra_Value = 1;
    int Center_Tra_Value = 1;
    int Right_Tra_Value = 1;
    int Black = 1;
    Left_Tra_Value = digitalRead(SensorLeft);
    Center_Tra_Value = digitalRead(SensorMiddle);
    Right_Tra_Value = digitalRead(SensorRight);
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
    } else if (Left_Tra_Value == Black && (Center_Tra_Value == Black && Right_Tra_Value == Black)) { //111
      stopp();
    }
    if (Serial.available())
    {
      bluetooth_data = Serial.read();
      if (bluetooth_data == 'S') {
        flag = 1;
      }
    }
  }
}

void Follow()
{
  flag = 0;
  while (flag == 0)
  {
    int Infrared_Trigger_Flag = 0;
    Left_IR_Value = digitalRead(A1);
    Right_IR_Value = digitalRead(A0);
    Front_Distance = checkdistance();
    if (Front_Distance < 5 && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
      stopp();
    } else if (Front_Distance < 5 && (Left_IR_Value == Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
      turnL();
    } else if (Front_Distance < 5 && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value == Infrared_Trigger_Flag)) {
      turnR();
    } else if (Front_Distance > 10 && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
      advance();
    } else if (Front_Distance > 10 && (Left_IR_Value == Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
      turnL();
    } else if (Front_Distance > 10 && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value == Infrared_Trigger_Flag)) {
      turnR();
    }
    if (Serial.available())
    {
      bluetooth_data = Serial.read();
      if (bluetooth_data == 'S') {
        flag = 1;
      }
    }
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

void Ultrasonic_obstacle_avoidance() {
  if (Front_Distance <= 10) {
    back();
    delay(100);
    turnR();
    delay(300);
  }
  else {
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
void Obstacle_Avoidance_Main() {
  flag = 0;
  while (flag == 0)
  {
    Left_IR_Value = digitalRead(A1);
    Right_IR_Value = digitalRead(A0);
    Front_Distance = checkdistance();
    Infrared_Obstacle_Avoidance();
    if (Serial.available())
    {
      bluetooth_data = Serial.read();
      if (bluetooth_data == 'S') {
        flag = 1;
      }
    }
  }
}

void Light_Seeking() {
  flag = 0;
  while (flag == 0)
  {
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
    if (Serial.available())
    {
      bluetooth_data = Serial.read();
      if (bluetooth_data == 'S') {
        flag = 1;
      }
    }
  }
}

void M_Control_IO_config(void)
{
  pinMode(M1_1, OUTPUT);
  pinMode(M1_2, OUTPUT);
  pinMode(M2_1, OUTPUT);
  pinMode(M2_2, OUTPUT);
}

void Sensor_IO_Config()     //IO initialized function of three line tracking , all setting at input
{
  pinMode(SensorLeft, INPUT);
  pinMode(SensorMiddle, INPUT);
  pinMode(SensorRight, INPUT);
  pinMode(inputPin, INPUT);      //starting receiving IR remote control signal
  pinMode(outputPin, OUTPUT);    //IO of ultrasonic module
  pinMode(SCL_Pin, OUTPUT); // Set the clock pin to output
  pinMode(SDA_Pin, OUTPUT); //Set the data pin to output
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
}

void setup()
{
  Serial.begin(9600);       //initialized serial port , using Bluetooth as serial port, setting baud
  M_Control_IO_config();     //motor controlling the initialization of IO
  Sensor_IO_Config();
  stopp();                       //stop
  delay(1000);
  Front_Distance = 0;
  leftSensorValue = 0;
  rightSensorValue = 0;
  matrix_display(clear);
  matrix_display(start01); //display start01 expression pattern
}
void loop()
{
  if (Serial.available() > 0)
  {
    bluetooth_data = Serial.read();
    Serial.println(bluetooth_data);
    matrix_display(clear);
  }
  switch (bluetooth_data) {
    case 'U':
      advance();
      matrix_display(front);
      break;
    case 'D':
      back();
      matrix_display(back01);
      break;
    case 'L':
      turnL();
      matrix_display(left);
      break;
    case 'R':
      turnR();
      matrix_display(right);
      break;
    case 'S':
      stopp();
      matrix_display(STOP01);
      break;
    case 'a' : speeds_a();
      matrix_display(speed_a);
      break;
    case 'd' : speeds_d();
      matrix_display(speed_d);
      break;
    case 'T':
      stopp();
      matrix_display(smile);
      Line_Tracking();
      break;
    case 'F':
      stopp();
      matrix_display(smile);
      Follow();
      break;
    case 'O':
      stopp();
      matrix_display(smile);
      Obstacle_Avoidance_Main();
      break;
    case 'G':
      stopp();
      matrix_display(smile);
      Light_Seeking();
      break;
    default:
      break;
  }
}


void advance()    //  going forward
{
  digitalWrite(M1_1, LOW);
  analogWrite(M1_2,  speeds);
  digitalWrite(M2_1, LOW);
  analogWrite(M2_2,  speeds);
}
void back()         //back up
{
  analogWrite(M1_1, speeds);
  digitalWrite(M1_2, LOW);
  analogWrite(M2_1, speeds);
  digitalWrite(M2_2, LOW);
}
void turnR()         //turn right
{
  analogWrite(M1_1, speeds + 30);
  digitalWrite(M1_2, LOW);
  digitalWrite(M2_1, LOW);
  analogWrite(M2_2, speeds + 30);
}
void turnL()        //turn left
{
  digitalWrite(M1_1, LOW);
  analogWrite(M1_2, speeds + 30);
  analogWrite(M2_1, speeds + 30);
  digitalWrite(M2_2, LOW);
}
void stopp()        //stop
{
  digitalWrite(M1_1, LOW);
  digitalWrite(M1_2, LOW);
  digitalWrite(M2_1, LOW);
  digitalWrite(M2_2, LOW);
}
void speeds_a() { //rapidly growing function
  while (1) {
    Serial.println(speeds);  //display speed information
    if (speeds < 255) { //Up to 255
      matrix_display(clear);
      matrix_display(speed_a);
      speeds++;
      delay(10);  //adjust the speed of growth
    }
    bluetooth_data = Serial.read();
    if (bluetooth_data == 'S') //Receive 'S',the car stops accelerating
      break;
  }
}
void speeds_d() { //velocity reduction function
  while (1) {
    Serial.println(speeds);  //display speed information
    if (speeds > 0) { //down to 0
      matrix_display(clear);
      matrix_display(speed_d);
      speeds--;
      delay(10);    //adjust the speed of deceleration
    }
    bluetooth_data = Serial.read();
    if (bluetooth_data == 'S') //Receive 'S',the car stops deceleration
      break;
  }
}
//this function is used for dot matrix display
void matrix_display(unsigned char matrix_value[])
{
  IIC_start();  //the function that calls the data transfer start condition
  IIC_send(0xc0);  //select address

  for (int i = 0; i < 16; i++) //the pattern data is 16 bytes
  {
    IIC_send(matrix_value[i]); //Transmit the data of the pattern
  }
  IIC_end();   //End pattern data transmission
  IIC_start();
  IIC_send(0x8A);  //Display control, select 4/16 pulse width
  IIC_end();
}
//Conditions under which data transmission begins
void IIC_start()
{
  digitalWrite(SDA_Pin, HIGH);
  digitalWrite(SCL_Pin, HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin, LOW);
  delayMicroseconds(3);
  digitalWrite(SCL_Pin, LOW);
}
//Indicates the end of data transmission
void IIC_end()
{
  digitalWrite(SCL_Pin, LOW);
  digitalWrite(SDA_Pin, LOW);
  delayMicroseconds(3);
  digitalWrite(SCL_Pin, HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin, HIGH);
  delayMicroseconds(3);
}
//transmit data
void IIC_send(unsigned char send_data)
{
  for (byte mask = 0x01; mask != 0; mask <<= 1) //Each byte has 8 bits and is checked bit by bit starting at the lowest level
  {
    if (send_data & mask) { //Sets the high and low levels of SDA_Pin depending on whether each bit of the byte is a 1 or a 0
      digitalWrite(SDA_Pin, HIGH);
    } else {
      digitalWrite(SDA_Pin, LOW);
    }
    delayMicroseconds(3);
    digitalWrite(SCL_Pin, HIGH); //Pull the clock pin SCL_Pin high to stop data transmission
    delayMicroseconds(3);
    digitalWrite(SCL_Pin, LOW); //pull the clock pin SCL_Pin low to change the SIGNAL of SDA
  }
}
