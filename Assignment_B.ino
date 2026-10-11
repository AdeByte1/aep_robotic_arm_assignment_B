#include <Servo.h> // Imports the Servo library to generate PWM signals for the motor

Servo myServo; // Creates a servo object to control the physical motor

const int trigPin = 9;  // Assigns digital pin 9 to the ultrasonic sensor's trigger pin
const int echoPin = 10; // Assigns digital pin 10 to the ultrasonic sensor's echo pin
const int buzzerPin = 8; // Assigns digital pin 8 to control the active buzzer

long duration;  // Declares an integer variable to store the sound wave's round-trip travel time
float distance; // Declares a decimal variable to store the calculated distance in centimeters

void setup() {
  Serial.begin(9600); // Opens a serial communication channel to the computer at 9600 baud
  
  pinMode(trigPin, OUTPUT); // Configures the trigger pin to send outgoing electrical signals
  pinMode(echoPin, INPUT); // Configures the echo pin to listen for incoming electrical signals
  pinMode(buzzerPin, OUTPUT); // Configures the buzzer pin to send outgoing electrical power
  
  myServo.attach(6); // Links the servo control logic to digital pin 6 on the Arduino
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW); // Pulls the trigger pin LOW to clear any residual signal
  delayMicroseconds(2); // Waits 2 microseconds to ensure a clean start
  
  digitalWrite(trigPin, HIGH); // Pulls the trigger pin HIGH to fire the 40kHz sound burst
  delayMicroseconds(10); // Holds the pulse HIGH for exactly 10 microseconds as required by the sensor
  digitalWrite(trigPin, LOW); // Pulls the trigger pin LOW to stop firing the sound wave
  
  duration = pulseIn(echoPin, HIGH); // Measures the exact microsecond duration the echo pin stays HIGH
  
  distance = (duration * 0.0343) / 2; // Converts round-trip time to one-way distance using the speed of sound
  
  Serial.print("Distance: "); // Prints the text label to the serial monitor
  Serial.print(distance); // Prints the calculated decimal distance value
  Serial.println(" cm"); // Prints the unit and moves the cursor to a new line
  
  // Move servo and trigger buzzer according to distance
  if (distance <= 10) { 
    myServo.write(90); // Actuates the servo arm to the 90-degree position
    
    // Object is very close
    tone(buzzerPin, 1000); // Triggers a continuous, unbroken 1000Hz tone on the buzzer
    
  } else if (distance > 10 && distance <= 30) { // Checks if the object is at a moderate distance
    myServo.write(0); // Actuates the servo arm back to the 0-degree resting position
    
    // Two short warning beeps
    tone(buzzerPin, 1000); // Turns the buzzer on at 1000Hz
    delay(200); // Keeps the tone on for 200 milliseconds
    noTone(buzzerPin); // Silences the buzzer
    delay(200); // Keeps the buzzer silent for 200 milliseconds
    tone(buzzerPin, 1000); // Turns the buzzer back on at 1000Hz
    delay(200); // Keeps the tone on for 200 milliseconds
    noTone(buzzerPin); // Silences the buzzer
    
  } else { 
    // No object detected or out of range
    // Removed the beep code so that it stays silent when clear
    myServo.write(0); // Ensures the servo arm remains in the 0 degree resting position
    noTone(buzzerPin); // Ensures the buzzer is completely silenced
  }
  
  // Wait 2 seconds before the next measurement
  delay(2000);
}
