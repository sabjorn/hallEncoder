#Hall Encoder

## Purpose
This code is designed to leverage two `US1881` Hall Latch Sensors to act as an [quadrature encoder](https://en.wikipedia.org/wiki/Rotary_encoder) for measuring the rotation of a wheel. Specifically it has been tested on the front sprocket of a bicycle.

This library includes an API which gives access to:
    * Direction of rotation
    * Average RPM
    * Position (with resolution based on number of magnets)
    * Time between rotation
    * Timeout (if the rotation has stopped for a set length of time)

There is example code which showcases most of these values.

## Theory
The `US1881` Hall Latch Sensor can detect magnetic polarity. This is leveraged by placing magnets on a rotating surface and placing the Hall Encoder circuit in a stationary position such that the magnets rotate across the field of the sensor.

[img]

Originally it was assumed that the magnets would have to be arranged in sequence with opposite polarities (side by side). This is not necessary since the orientation of the sensor board causes two state (HIGH/LOW) as a single magnet passes through the magnetic field. Thus the magnets should be oriented with the polarities in one direction.

**NOTE**: The polarity of the magnets does matter but I have not figured out which polarity should be used.

The library is setup to allow the user to use as many magnets in the system as desired. More magnets will yield a higher resolution in terms of steps and (probably) a greater accuracy with BPM. However, if the magnets are placed too close together the system may no longer work effectively.

By having two sensors on a single board the direction of rotation can be calculated (i.e. quadrature).

## Setup
There are two ways to use this code:
1 - Add the `src` directory to Arduino as a library, or;
2 - Make a symlink of the `.cpp` and `.h` files in the directory with your code. e.g. `ln -s src/* <directory with your .ino>`


