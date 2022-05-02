# ATTA
Embedded Systems Project

## Quick description
This project is about building and programing an ant-like robot

## Scope

### What the system must have:
- 3 motors for each leg
  - 1 for hight control
  - 2 for walking movement (lift + translation)

### What the system must do:
- Mimic the walking movement of a real ant

### Optionals (plus to the project):
- Control via bluetooth
- Installation of a tail to transform the robot into a scorpion
- Program new movements for the tail

### Architecture description
![Formiga](https://user-images.githubusercontent.com/90531157/166158713-8d33c4eb-a2b2-408f-9f1e-cdd1c7f62a88.jpg)

Up to now,  we have the following IO requirements for the GPIO (still need to verify availability on the Viola Base Board
  1. 3 Output - Slave sistems (control motors via PWM)
  2. 1 Input - Controls

### State Machine for the Software implementation of the Game
![Formiga (1)](https://user-images.githubusercontent.com/90531157/166229994-a4a08714-84fe-4515-930b-5301fd704b52.jpg)
- This version is the first idea of the group of how the sistem will work

### State Machine for the Software
