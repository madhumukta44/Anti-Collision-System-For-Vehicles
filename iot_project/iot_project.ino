/*
*Autonomous Vehicle Safety System with Real-Time Ultrasonic Obstacle Detection and Avoidance
*
*This project features an autonomous vehicle safety system that utilizes ultrasonic sensors for *real-time obstacle detection and avoidance. It processes serial commands to control vehicle *movements, ensuring collision-free navigation. The system includes buzzer alerts and LED *indicators to signal when obstacles are detected, enhancing overall vehicle safety and *operational efficiency.
*
*/


/*These lines define constants for pin numbers connected to various components such as motors, sensors, LEDs, and buzzers. They also define speed values for different movements.*/

#define ENA1 9          // Motor A speed control pin
#define in1 8           // Motor A direction control pin 1
#define in2 7           // Motor A direction control pin 2
#define ENA2 3          // Motor B speed control pin
#define in3 6           // Motor B direction control pin 1
#define in4 12          // Motor B direction control pin 2
#define trig 10         // Ultrasonic sensor trigger pin
#define echofront 2     // Ultrasonic sensor echo pin for front distance measurement
#define echoback 4      // Ultrasonic sensor echo pin for back distance measurement
#define danger 11       // Pin for danger indicator (e.g., LED)
#define light 5         // Pin for light control
#define speed_forward 150  // Speed value for moving forward
#define speed_backward 120 // Speed value for moving backward
#define speed_left_right 200 // Speed value for turning left or right
#define buzzer 13       // Pin for buzzer control



char m=0; // Variable to store command input

// Function to control motor movement
void move(int val1,int val2,int val3,int val4)
{
  digitalWrite(in1, val1);
  digitalWrite(in2, val2);
  digitalWrite(in3, val3);
  digitalWrite(in4, val4);
}

// Function to control motor speed
void speed(int val)
{
  analogWrite(ENA1, val);
  analogWrite(ENA2, val);
}

// Variables to store distances and times for ultrasonic sensor readings
int dist_forward,dist_back,time_forward,time_back,count_front=0,count_back=0;


//////////START - MAIN FUNCTION///////////
void setup()
{
  Serial.begin(9600); // Initialize serial communication
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

//////////END - MAIN FUNCTION///////////


//////////START - LOOP FUNCTION///////////

void loop() 
{
  // Check if data is available on the serial port
  if (Serial.available())
  {
    m=Serial.read(); // Read the command
    if(m!='S') // If command is not 'S', print it
    {
      Serial.println(m);
    }
  }

  // Execute command based on input
  if (m=='R') // Turn righ
  { 
    move(1,0,0,1);
    speed(speed_left_right);
  }
  else if (m=='L') // Turn left
  {
    move(0,1,1,0);
    speed(speed_left_right);
  }

  else if (m=='F') // Move forward
  {
    digitalWrite(trig,HIGH);
    delay(10);
    digitalWrite(trig,LOW);
    time_forward=pulseIn(echofront,HIGH);
    dist_forward=(time_forward*0.034)/2.0;
    if(dist_forward>0 && dist_forward <= 30) // Obstacle detected within 30 cm
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
  else if (m=='B') // Move backward
  {
    digitalWrite(trig,HIGH);
    delay(10);
    digitalWrite(trig,LOW);
    time_back=pulseIn(echoback,HIGH);
    dist_back=(time_back*0.034)/2.0;
    
    if(dist_back>0 && dist_back <= 20) // Obstacle detected within 20 cm
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
  else if (m=='G') // Turn left at a lower speed
  {
    digitalWrite(light, HIGH);
    move(0,0,1,0);
    speed(speed_left_right);
  }
  else if (m=='I') // Move forward with only left motor
  {
    digitalWrite(light, HIGH);
    move(1,0,0,0);
    speed(speed_left_right);
  }
  else if (m=='H') // Move backward with only right motor
  {
    digitalWrite(light, HIGH);
    move(0,0,0,1);
    speed(speed_left_right);
  }
  else if (m=='J') // Turn right at a lower speed
  {
    digitalWrite(light, HIGH);
    move(0,1,0,0);
    speed(speed_left_right);
  }
  else if (m=='S') // Stop all movement
  {
    digitalWrite(light, LOW);
    move(0,0,0,0);
    speed(0);
  }
  else if(m=='V') // Turn on buzzer
  {
    tone(buzzer, 500);
  }
  else if(m=='v') // Turn off buzzer
  {
    noTone(buzzer);
  }
}

//////////END - LOOP FUNCTION//////////
