/*

Automatic Motion Sensor Touchless Trash Can 

Description
The ultrasonic sensor is used to measure the distance of a trigger object (e.g. hand). If it is close by, the servo motor opens the lid.
Once the hand / object moves away, the lid will close after a few seconds. This time is programmable.
The lid stays open (and extends the timeout) if the hand stays in front of the sensor or re-appears before the closing starts.

# Plastic trash can with swivel lid

Features
- Touchless Operation
- Open time : programmable
- Open duration : programmable
- Power supply : 5V : battery or AC adapter (USB mobile)

Parts 
- Arduino Uno 3 : 
  A tiny computer, the size of a playing card. It's the brain that you can teach to do different things by writing instructions for it.
  You can connect various electronic components like lights, motors or sensors to it, and it will control them based on your instructions. 
  It's perfect for beginners who want to learn about electronics and programming.

- HC-SR04 Ultrasonic Sensor : 
  A pair of eyes that can measure distance using sound waves - just like how bats find their way in the dark! 
  It has two parts: one that sends out a special sound (so high-pitched that humans can't hear it), 
  and another that listens for the echo when that sound bounces back. 
  By measuring how long it takes for the sound to come back, it can tell you exactly how far away something is.
  - Weight: 9 gm
  - Operating Voltage : 5V
  - Current : 2mA
  - Freq : 40,000 Hz
  - Max sensing distance : 450cm
  - Advantages over infrared
    - More reliable in varying lighting
    - Better at detecting larger objects consistently
    - Wider detection angle (easier to trigger)
    - More accurate distance measurement helps prevent false triggers
  - Disadvantages (over infrared)
    - Slightly slower response time (not an issue for trash can)
    - Costs a bit more
    - Uses more power
  - reliability and user experience, ultrasonic is the better choice for this specific application

- SG-90 Servo Motor
  It's commonly used in tiny robots, remote-controlled toys, and other projects where you need precise movement control.
  Unlike regular motors that just spin around and around, a servo motor can turn to exact positions that you tell it to. 
  Think of it like the steering wheel of a remote control car - you can tell it to turn left 45 degrees or right 90 degrees, 
  and it will move exactly that much. 
  - Weight: 9 gm
  - Operating voltage: 3.0V~ 7.2V
  - Stall torque @4.8V : 1.2kg-cm
  - Stall torque @6.6V : 1.6kg-cm
  - Speed : 0.10sec/60°
  - Terminals : 
    RED – Positive
    Brown – Negative
    Orange – Signal

*/


#include <Servo.h>  // Servo motor header file

Servo myservo;      // servo motor control object

// pin number of the ultrasonic sensor's output:
const int trigPin = 7;
const int echoPin = 6;

const int buzzer = 11;

const int startPos = 60;          // starting position of servo motor (fully closed lid)
const int endPos = 125;           // final position of servo motor (full open lid)
const int servoStep = 2;          // rotation angle steps
const int distThreshold = 10;     // distance of hand from sensor to trigger the opening

enum lidState {
    CLOSED,     // Lid is fully closed
    OPENING,    // Lid is in process of opening
    OPEN,       // Lid is fully open
    CLOSING     // Lid is in process of closing
};

// initialize variables
int pos = startPos;                   // variable to store the last servo position
int lidTimeout = 3000;                // lid autocloses after this time
unsigned long lastProximityTime = 0;  // time at which hand was last seen close to the sensor

// Create a variable of type lidState
lidState currentLidState = CLOSED;  // Initialize to CLOSED

long duration;
int sensor_distance;

// Initialize the motor/sensor
void setup() {
  myservo.attach(8);  // attaches the servo on pin 9 to the servo object
  delay(15);
  myservo.write(pos);

  pinMode(buzzer, OUTPUT);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  Serial.begin(9600);       // Starts the serial communication
}

int get_distance() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  sensor_distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(sensor_distance);
  return sensor_distance;
}

void loop() {
  if (get_distance() <= distThreshold) {

    // Open the lid if needed
    if (currentLidState == CLOSED) {
      Serial.print("Opening lid\n");

      for(int b=0; b<=30; b++){
        digitalWrite(buzzer, HIGH);
        delay(5);
        digitalWrite(buzzer, LOW);
        delay(1);
      } 

      // rotate servo motor to open the lid
      for (pos = startPos; pos <= endPos; pos += servoStep) { // goes from startPos degrees to endPos degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
        currentLidState = OPENING;       // update the current state of the lid
      }
      currentLidState = OPEN;            // update the current state of the lid

    } else {
      Serial.print("Lid already open\n");
    }
    lastProximityTime = millis();         // track the time when the hand was last seen close to the sensor

  } else {

    Serial.print("No object nearby\n");

    // Close the lid if needed
    if (currentLidState == OPEN) {

      // Check if sufficient time has elapsed since the object was last seen close to the sensor
      if ((millis() - lastProximityTime) > lidTimeout) {

        Serial.print("Closing lid\n");

        for(int b=0; b<=20; b++){
          digitalWrite(buzzer, HIGH);
          delay(5);
          digitalWrite(buzzer, LOW);
          delay(2);
        } 
        delay(50);
        for(int b=0; b<=20; b++){
          digitalWrite(buzzer, HIGH);
          delay(5);
          digitalWrite(buzzer, LOW);
          delay(2);
        } 
        delay(50);
        for(int b=0; b<=20; b++){
          digitalWrite(buzzer, HIGH);
          delay(5);
          digitalWrite(buzzer, LOW);
          delay(2);
        } 

        // rotate the servo to close the lid
        for (pos = endPos; pos >= startPos; pos -= servoStep) {
          myservo.write(pos);            
          delay(15);                      
          currentLidState = CLOSING;        // update the current state of the lid
        }
        currentLidState = CLOSED;           // update the current state of the lid
      } else {
        Serial.print("Closing in : ");
        Serial.println(lidTimeout - (millis() - lastProximityTime));
      }
    } else {
      Serial.print("Lid already closed\n");
    }
  }

  delay(500);
}
