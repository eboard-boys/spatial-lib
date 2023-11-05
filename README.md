# spatial-lib
Library for determining acceleration, velocity, speed, and arc length.

## Mathematic functionality
This library gives helper functions for preforming Euler's Method in 3D space.

For calculating arc length, the formula referenced is
$ s = \int_a^b{|{{d \vec r}\over {dt}}}|dt $
where $ \vec r $ is vector representing a function for position.

Because of the nature of accelerometers, acceleration is actually the initial measurement everything else is calculated from.
Thus, a more accurate representation of the calculations done internally may be
$ s = \int_a^b{|d \vec v}|dt $
where $ \vec v $ is a vector representing a function for position.

This mathematic functionality is intended to be decoupled from any hardware implementation details.
Drivers for initialization and retrieving values from the accelerometer are independent of this.

For testing the math functions, a dummy driver (will be made) available.
