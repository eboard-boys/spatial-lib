# spatial-lib
Library for determining acceleration, velocity, speed, and arc length.

## Mathematic functionality
This mathematic functionality is intended to be decoupled from any hardware implementation details.
Drivers for initialization and retrieving values from the accelerometer are independent of this.
For testing the math functions, a dummy driver (will be made) available.

### Determining velocity, speed, and distance
This library gives helper functions for preforming Euler's Method in 3D space.

For calculating arc length (the distance traveled), the formula referenced is
```math
s = \int_a^b{|{{d \vec r}\over {dt}}}|dt
```
where $\vec r$ is vector representing a function for position.

Because of the nature of accelerometers, acceleration is actually the initial measurement everything else is calculated from.
Thus, a more accurate representation of the calculations done internally may be
```math
s = \int_a^b{|d \vec v}|dt
```
where $\vec v$ is a vector representing a function for position.

### Coordinate systems
Some calculations are better done with a change of coordinates, such the current incline on a hill.
Spherical coordinates are a generalization of polar coordinates that allow this library to more easily work with angles.
The covention for Spherical coordinates used is the ISO standard or "physics convention" as seen here:

![Andeggs, Public domain, via Wikimedia Commons](https://upload.wikimedia.org/wikipedia/commons/4/4f/3D_Spherical.svg "Spherical Coordinates Convention")

The following equations describe a change of coordinates from cartesian to spherical:
```math
\begin{align}
r &= \sqrt{x^2 + y^2 + z^2} \\
\theta &= \arccos\frac{z}{\sqrt{x^2 + y^2 + z^2}} = \arccos\frac{z}{r}=
\begin{cases}
 \arctan\frac{\sqrt{x^2+y^2}}{z} &\text{if } z > 0 \\
 \pi +\arctan\frac{\sqrt{x^2+y^2}}{z} &\text{if } z < 0 \\
 +\frac{\pi}{2} &\text{if } z = 0 \text{ and } xy \neq 0 \\
 \text{undefined} &\text{if } x=y=z = 0 \\
\end{cases} \\
\varphi &= sgn(y)\arccos\frac{x}{\sqrt{x^2+y^2}} =
\begin{cases}
 \arctan(\frac{y}{x}) &\text{if } x > 0, \\
 \arctan(\frac{y}{x}) + \pi &\text{if } x < 0 \text{ and } y \geq 0, \\
 \arctan(\frac{y}{x}) - \pi &\text{if } x < 0 \text{ and } y < 0, \\
 +\frac{\pi}{2} &\text{if } x = 0 \text{ and } y > 0, \\
 -\frac{\pi}{2} &\text{if } x = 0 \text{ and } y < 0, \\
 \text{undefined} &\text{if } x = 0 \text{ and } y = 0.
\end{cases}
\end{align}
```

The following equations describe a change of coordinates from spherical to cartesian:
```math
x &= r \sin (\theta) \cos (\phi)
y &= r \sin (\theta) \sin (\phi)
z &= r \cos (\theta)
```
