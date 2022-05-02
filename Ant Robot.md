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
![Formiga (1)](https://user-images.githubusercontent.com/90531157/166230959-45118a2e-0fc9-4533-b6c1-b5906f98ac9d.jpg)

Up to now,  we have the following IO requirements for the GPIO (still need to verify availability on the Viola Base Board
  1. 3 Output - Slave sistems (control motors via PWM)
  2. 1 Input - Controls

### State Machine for the Software

- This version is the first idea of the group of how the sistem will work
