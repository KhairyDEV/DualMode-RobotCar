# 🤖 Dual-Mode Robot Car: Bluetooth-Controlled + Autonomous Navigation

This project is an Arduino-based robot car that operates in two modes:
- **Manual Mode**: Controlled via Bluetooth using a customized Android app interface.
- **Autonomous Mode**: Automatically avoids obstacles using an ultrasonic sensor and follows a **left-hand wall-following rule**.

---

## 📷 Wiring Diagram

>![Wiring Diagram](images/circuit_image.png)
  
### 🔌 Pin Configuration

| Component         | Arduino Pin | Description                          |
|------------------|-------------|--------------------------------------|
| Left Motor IN1    | `2`         | Forward (HIGH)                       |
| Left Motor IN2    | `3`         | Backward (HIGH)                      |
| Right Motor IN3   | `4`         | Backward (HIGH)                      |
| Right Motor IN4   | `7`         | Forward (HIGH)                       |
| Left Motor Speed  | `6` (ENA)   | PWM speed control                    |
| Right Motor Speed | `5` (ENB)   | PWM speed control                    |
| Ultrasonic Echo   | `10`        | Echo pin of HC-SR04 (receiver)       |
| Ultrasonic Trig   | `11`        | Trigger pin of HC-SR04 (transmitter) |

---

## 📱 Bluetooth Control Interface

We used the **[Bluetooth Electronics App](https://bluetooth-electronics.en.softonic.com/android)** to build a custom controller layout on Android.

- Each button in the app sends a single character to the Arduino via serial.
- The Arduino reads these characters and maps them to actions.

### 🧭 Command Mapping

| App Button | Command | Action                      |
|------------|---------|-----------------------------|
| Forward    | `F`     | Move forward                |
| Backward   | `B`     | Move backward               |
| Left       | `L`     | Turn left                   |
| Right      | `R`     | Turn right                  |
| Stop       | `S`     | Stop all motors             |
| Auto Mode  | `D`     | Enable obstacle avoidance   |
| Manual Mode| `A`     | Return to Bluetooth control |

You can create these buttons inside the app and assign the characters manually.

---

## 🤖 Autonomous Mode: Obstacle Avoidance

When switched to automatic mode (via command `D`), the robot:

1. Uses the HC-SR04 ultrasonic sensor to detect objects.
2. If an obstacle is detected closer than a threshold distance (e.g. 10–30 cm), it:
   - Stops
   - Reverses briefly
   - Turns **left** (following the left-hand rule)
3. Then continues moving forward.

---

## 🧰 Hardware Requirements

- Arduino Uno R3  
- L298N Motor Driver  
- HC-SR04 Ultrasonic Sensor  
- HC-05 or HC-06 Bluetooth Module  
- 2x DC Motors + Wheels  
- Chassis + Battery Pack (9V or Li-ion)
- Android phone (with Bluetooth Electronics app)

---

## 📝 Notes

- If your robot drifts while moving forward, adjust PWM speed individually for each motor.
- Ensure correct pairing between your phone and the HC-05/HC-06 Bluetooth module.
- Test all directions manually using the Bluetooth app before switching to auto mode.

---

## 📄 License

This project is open source and free to use under the MIT License.
