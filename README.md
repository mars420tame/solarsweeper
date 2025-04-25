## Solar Sweeper

The **Solar Sweeper** is an autonomous robot designed to clean solar panels, equipped with sensors for obstacle avoidance and distance measurement. It can navigate autonomously and make decisions based on environmental feedback. The robot uses an ESP32 as its main controller and includes various sensors to help it navigate and operate efficiently.

## Components

- **ESP32**: The brain of the project that controls all sensors, motors, and logic.
- **4 IR Sensors**: Used for line following or obstacle detection.
- **1 Ultrasonic Sensor**: Measures the distance to obstacles in front of the robot to avoid collisions.
- **MPU6050**: A gyroscope/accelerometer module for balancing, tilt detection, and motion sensing.
- **Relay**: Used to control high power devices such as motors or other electronics.
- **L298N Motor Driver**: Drives the four motors that control the movement of the robot.
- **4 × 6V Motors**: Provide movement to the robot, enabling it to move forward, backward, or turn.

## Features

- **Obstacle Avoidance**: Uses ultrasonic and IR sensors to detect obstacles and avoid collisions.
- **Autonomous Navigation**: Can move autonomously based on sensor input.
- **Motor Control**: Four 6V motors control the movement of the robot, driven by the L298N motor driver.
- **Sensor Feedback**: The robot uses feedback from the sensors to make decisions and navigate through environments.

## Setup

### Hardware
![robo_bb](https://github.com/user-attachments/assets/6142f447-c21d-48d9-9c4f-35c1758cc1b9)

1. Connect the **ESP32** to the L298N motor driver to control the four 6V motors.
2. Wire the **IR sensors** to the ESP32 for detecting obstacles.
3. Connect the **ultrasonic sensor** to measure distance from objects.
4. Attach the **MPU6050** for balancing and motion sensing.
5. Use the **relay** to manage high-power devices if necessary.
[5375a66e-c5a3-476f-bf6d-5707b830bf7a.dxf-0001.pdf](https://github.com/user-attachments/files/19902290/5375a66e-c5a3-476f-bf6d-5707b830bf7a.dxf-0001.pdf)


### Software
![image](https://github.com/user-attachments/assets/73c28cd5-7a9b-4f80-a646-61fccd9d5168)
![Screenshot 2025-04-25 061650](https://github.com/user-attachments/assets/98695f0f-43b7-4760-a5a3-0f85b71c97b2)


1. Install the necessary libraries for the ESP32 and sensors.
2. Use the provided code to upload to the ESP32.
3. Configure the motor driver and sensor pins as per your setup.

## License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.
