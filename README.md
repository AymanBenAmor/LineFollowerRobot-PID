# PID Line Follower Robot

This project is a simple line-following robot built with an Arduino-compatible microcontroller (e.g., ESP32). The robot uses a PID (Proportional-Integral-Derivative) controller to follow a black line on a white surface. The sensors detect the line, and the motor speed is adjusted to keep the robot on track.

## Features

- **PID Control**: Uses a PID controller to control the motor speed and direction, improving line-following performance.
- **8-Line Sensors**: 8 infrared sensors (CP1 to CP8) are placed along the robot to detect the line's position.
- **Motor Control**: Controls two DC motors (Motor 1 and Motor 2) for movement using PWM (Pulse Width Modulation).
- **Speed Adjustment**: Adjusts motor speeds to stay on the line based on sensor readings.

## Components Used

- **Microcontroller**: ESP32 or Arduino compatible board.
- **Motors**: Two DC motors (Motor 1 and Motor 2) with H-Bridge drivers.
- **Sensors**: 8 infrared sensors for line detection.
- **Motor Driver Pins**: 
  - Motor 1: `av_m1`, `re_m1`, `vitt_1`
  - Motor 2: `av_m2`, `re_m2`, `vitt_2`

## Wiring

- **Motor 1**: Connected to pins `av_m1` (forward), `re_m1` (reverse), `vitt_1` (PWM speed).
- **Motor 2**: Connected to pins `av_m2` (forward), `re_m2` (reverse), `vitt_2` (PWM speed).
- **Sensors**: Connected to pins `cp1` to `cp8` (input pins for sensor readings).

## PID Tuning

The PID controller parameters are adjustable for fine-tuning:
- **Kp**: Proportional constant (`1.9`)
- **Ki**: Integral constant (`0.05`)
- **Kd**: Derivative constant (`1`)

These parameters can be adjusted to optimize the robot's response to line-following.

## Code Explanation

- **PID Algorithm**: 
  - The robot calculates an error value based on the sensor readings (`cp1` to `cp8`). The sensor values are multiplied by predefined weights (`values[]`), and the error is used in the PID calculation.
  - The Proportional term (P) is calculated directly from the error.
  - The Derivative term (D) is based on the change in error since the last cycle.
  - The motor speeds are adjusted based on the PID output to keep the robot following the line.
  
- **Motor Control**:
  - The robot uses PWM to control the speed of the motors (`ledcWrite()`), adjusting the speeds to follow the line while avoiding obstacles.

## How to Use

1. **Upload the code**: Upload the provided code to your ESP32 or Arduino-compatible board.
2. **Connect the hardware**: Connect the motors, sensors, and microcontroller as described in the wiring section.
3. **Power up**: Once the hardware is set up and powered on, the robot will start following the line.

## Troubleshooting

- **PID Tuning**: If the robot does not follow the line smoothly, adjust the PID constants (`Kp`, `Ki`, `Kd`) to fine-tune the response.
- **Sensor Issues**: Ensure that the infrared sensors are aligned correctly and that the line is clearly visible to the sensors.
- **Motor Speed**: If the motors are not spinning as expected, check the PWM values and the wiring of the motor drivers.

## License

This project is licensed under the MIT License.
