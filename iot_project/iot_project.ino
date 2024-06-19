#define ENA1 9
#define in1 8
#define in2 7
#define ENA2 3
#define in3 6
#define in4 12
#define trig 10
#define echofront 2
#define echoback 4
#define danger 11
#define light 5
#define speed_forward 150
#define speed_backward 120
#define speed_left_right 200
#define buzzer 13


char m=0;
void move(int val1,int val2,int val3,int val4)
{
  digitalWrite(in1, val1);
  digitalWrite(in2, val2);
  digitalWrite(in3, val3);
  digitalWrite(in4, val4);
}
void speed(int val)
{
  analogWrite(ENA1, val);
  analogWrite(ENA2, val);
}
int dist_forward,dist_back,time_forward,time_back,count_front=0,count_back=0;
void setup()
{
  Serial.begin(9600);
  pinMode(ENA1, OUTPUT); 
  pinMode(ENA2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(danger, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(buzzer, OUTPUT);

}

void loop() 
{
  if (Serial.available())
  {
    m=Serial.read();
    if(m!='S')
    {
      Serial.println(m);
    }
  }
  if (m=='R')
  {
    move(1,0,0,1);
    speed(speed_left_right);
  }
  else if (m=='L')
  {
    move(0,1,1,0);
    speed(speed_left_right);
  }

  else if (m=='F')
  {
    digitalWrite(trig,HIGH);
    delay(10);
    digitalWrite(trig,LOW);
    time_forward=pulseIn(echofront,HIGH);
    dist_forward=(time_forward*0.034)/2.0;
    if(dist_forward>0 && dist_forward <= 30)
    {
      digitalWrite(danger, HIGH);
      digitalWrite(light, LOW);
      if(count_front<15)
      {
        move(0,1,0,1);
        speed(speed_backward);
        count_front++;
      }
      else
      {
        move(0,0,0,0);
        speed(0);
        tone(buzzer,1000);
      }  
      
    }
    else
    {
      noTone(buzzer);
      move(1,0,1,0);
      count_front=0;
      digitalWrite(light,HIGH);
      digitalWrite(danger,LOW);
      speed(speed_forward);
    }
  }
  else if (m=='B')
  {
    digitalWrite(trig,HIGH);
    delay(10);
    digitalWrite(trig,LOW);
    time_back=pulseIn(echoback,HIGH);
    dist_back=(time_back*0.034)/2.0;
    if(dist_back>0 && dist_back <= 20)
    {
      digitalWrite(danger, HIGH);
      digitalWrite(light, LOW);
      if(count_back<10)
      {
        move(1,0,1,0);
        speed(speed_forward);
        count_back++;
      }
      else
      {
        move(0,0,0,0);
        speed(0);
        tone(buzzer,1000);
      }
      
    }
    else
    {
      count_back=0;
      noTone(buzzer);
      digitalWrite(danger, LOW);
      digitalWrite(light, LOW);
      move(0,1,0,1);
      speed(speed_backward);
    }
  }
  else if (m=='G')
  {
    digitalWrite(light, HIGH);
    move(0,0,1,0);
    speed(speed_left_right);
  }
  else if (m=='I')
  {
    digitalWrite(light, HIGH);
    move(1,0,0,0);
    speed(speed_left_right);
  }
  else if (m=='H')
  {
    digitalWrite(light, HIGH);
    move(0,0,0,1);
    speed(speed_left_right);
  }
  else if (m=='J')
  {
    digitalWrite(light, HIGH);
    move(0,1,0,0);
    speed(speed_left_right);
  }
  else if (m=='S')
  {
    digitalWrite(light, LOW);
    move(0,0,0,0);
    speed(0);
  }
  else if(m=='V')
  {
    tone(buzzer, 500);
  }
  else if(m=='v')
  {
    noTone(buzzer);
  }
}