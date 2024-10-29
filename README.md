# Anti-Collision-System-For-Vehicles
**Anti-Collision System For Vehicles**  This project implements an anti-collision system for vehicles using ultrasonic sensors to detect obstacles and adjust movement to prevent collisions. The system can be controlled via serial commands and includes features like automatic obstacle avoidance, buzzer alerts, and LED indicators.<br>

**Project Setup**
<br>**Visual References**
Here’s a look at the setup from multiple angles:
<br>[Side View](References/sideView.jpg)
<br>[Top View](References/topView.jpg)
<br>[Front View](References/frontView.jpg)

**Demonstration Video**
<br>[Click here](References/videoReference.mp4) to watch a demonstration of the automatic braking system in action.


## How the Code Works
Upon inspecting the provided code, it is first seen defining constants for pin assignments and speed values necessary for controlling the robot’s motors and sensors. The setup function initializes serial communication and configures the pins as outputs. Moving on to the loop function, the code checks for serial input and assigns commands to control the robot's movements.

The robot's movement is determined by serial commands such as 'R' for right, 'L' for left, 'F' for forward, and 'B' for backward. For forward and backward movements, the ultrasonic sensor is used to measure distance. The ultrasonic sensor works by sending an ultrasonic pulse via the trig pin and measuring the time it takes for the echo to return to the echo pin. This duration is then multiplied by the speed of sound and divided by 2 to calculate the distance in centimeters.

In detail, the forward command triggers the ultrasonic sensor to measure the time for the echo to return (`time_forward`), which is then used to compute the distance (`dist_forward`). If an obstacle is detected within 30 cm, the danger LED is activated, and the robot moves backward to avoid a collision. If the obstacle persists, the robot stops and activates the buzzer. For backward movement, a similar process is followed using the `echoback` pin to detect obstacles behind the robot.

Additional commands like 'G', 'I', 'H', and 'J' control individual wheel movements to navigate the robot in specific directions. The 'S' command stops the robot, and 'V' and 'v' commands control the buzzer for audible alerts.

This setup allows the robot to navigate its environment while avoiding collisions through simple serial commands, providing a flexible and responsive control system. The use of distance measurement ensures the robot can react to obstacles and prevent accidents, similar to how braking systems adjust based on speed and distance to avoid collisions.

<br>Thanks 
