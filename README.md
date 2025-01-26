# Contactless self opeing automatic trash can

![automatic contactless trash can circuit](https://raw.githubusercontent.com/ishavya/automatic-trash-can/refs/heads/main/automatic%20contactless%20trash%20can%20circuit.png)

## How it works : 
The ultrasonic sensor is used to measure the distance of a trigger object (e.g. hand). If it is close by, the servo motor opens the lid.
Once the hand / object moves away, the lid will close after a few seconds. This time is programmable. The lid stays open (and extends the timeout) if the hand stays in front of the sensor or re-appears before the closing starts.

Features
- Touchless Operation
- Open time : programmable
- Open duration : programmable
- Power supply : 5V : battery or AC adapter (USB mobile)

Parts
- Arduino Uno 3 : A tiny computer, the size of a playing card. It's the brain that you can teach to do different things by writing instructions for it. You can connect various electronic components like lights, motors or sensors to it, and it will control them based on your instructions. It's perfect for beginners who want to learn about electronics and programming.

- HC-SR04 Ultrasonic Sensor : A pair of eyes that can measure distance using sound waves - just like how bats find their way in the dark ! It has two parts: one that sends out a special sound (so high-pitched that humans can't hear it), and another that listens for the echo when that sound bounces back. By measuring how long it takes for the sound to come back, it can tell you exactly how far away something is.
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

- SG-90 Servo Motor : It's commonly used in tiny robots, remote-controlled toys, and other projects where you need precise movement control. Unlike regular motors that just spin around and around, a servo motor can turn to exact positions that you tell it to. Think of it like the steering wheel of a remote control car - you can tell it to turn left 45 degrees or right 90 degrees,
  and it will move exactly that much.
  - Stall torque @4.8V : 1.2kg-cm
  - Stall torque @6.6V : 1.6kg-cm
  - Speed : 0.10sec/60°
