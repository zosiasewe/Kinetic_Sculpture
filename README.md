#  Project of a robotic kinetic sculpture installation

A kinetic sculpture with a heart of **Arduino Uno**, designed and built as part of a Bachelor's thesis. The sculpture is controllable via a custom Android application, enabling dynamic, programmable motion. This project combines **robotics**, **3D printing**, and **mobile development** to create an interactive artistic installation.

##  Project Description

The goal of this project was to create a **robotic kinetic sculpture** driven by low-cost servomechanisms and controlled through a Bluetooth-enabled mobile app. The sculpture is capable of executing complex movement sequences in a visually engaging and programmable manner.

The system was designed with a **modular architecture**, featuring:

- **Arduino Uno Rev3** microcontroller
- **MG90S servos** (metal gear)
- **PCA9685 PWM controller**
- **HC-05 Bluetooth module**
- **MIT App Inventor Android app**
- **3D-printed mechanical components**

##  Hardware Overview

| Component            | Description                                           |
|----------------------|-------------------------------------------------------|
| Arduino Uno Rev3     | Main controller managing servo movement               |
| MG90S Servos         | 9g micro servos controlling sculpture articulation    |
| PCA9685              | 16-channel PWM driver for servo control               |
| HC-05 Bluetooth      | Module for wireless communication with Android app    |
| 3D Printed Parts     | Base and mounting structures for precise positioning  |

##  Software Overview

- Mobile app developed using **MIT App Inventor**
- Communication via **Bluetooth SPP**
- Arduino-side control loop parses app commands and sends PWM signals to servos

##  Key Features

-  Multiple servo motors working in coordinated motion
-  Real-time mobile control via Android app
-  Modular design (both mechanical and electrical)
-  Custom-designed 3D-printed parts for the servo mounts and platforms

##  Challenges Faced

- **Servo inconsistency**: Low-cost MG90S units exhibited inconsistent behavior, requiring careful calibration and, in some cases, replacement.
- **PWM range tuning**: Precise PWM signal boundaries had to be experimentally determined for each servo.
- **Stability issues**: Initial designs mounted caps directly on gears, which caused instability; later designs attached caps to servo arms, greatly improving accuracy.
- **Simultaneous servo control**: Though PCA9685 supports up to 16 channels, attempting to move many servos at once caused stability issues.

##  Achievements

- Developed a fully functional kinetic sculpture system
- Successfully integrated Android mobile app control
- Designed and printed mechanical components tailored to servo geometries
- Developed a robust algorithm to drive multiple servos based on real-time user input

##  Future Development Ideas

- **Custom motion sequencing**: Allow users to define and save custom movement patterns via the app
- **Improved mechanical precision**: Upgrade to higher-quality servos and redesign 3D parts for greater accuracy
- **Advanced interactivity**: Integrate sensors for environmental feedback (light, sound, motion)
- **Graphic pattern generation**: Using specialized servo movements to create dynamic visual patterns
- **Smart home integration**: Enable voice control or IoT-based scheduling via platforms like Google Home or Alexa


