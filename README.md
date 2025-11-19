# Smart Chair Alert System 🪑🚨

## Project Overview
This project is an ergonomic alert system designed to prevent health issues caused by prolonged sitting. It uses a Force Sensitive Resistor (FSR) to detect when a person is sitting and triggers a buzzer/LED alert if they sit for too long without a break.

## Features
* **Presence Detection:** Detects user presence using an FSR sensor.
* **Timer Logic:** Tracks sitting duration in real-time.
* **Alert System:** Buzzes and lights up an LED after a set threshold (e.g., 30 minutes).
* **Reset:** Automatically resets the timer when the user stands up.

## Components Used
* Arduino UNO
* Force Sensitive Resistor (FSR)
* 10k Ohm Resistor (for voltage divider)
* Active Buzzer
* LED
* Breadboard & Jumper Wires

## How it Works
1.  The FSR sensor detects pressure changes on the chair seat.
2.  If pressure > threshold, the Arduino starts a timer.
3.  If the timer exceeds the limit (e.g., 45 mins), the Buzzer activates.
4.  If the user stands up (pressure < threshold), the timer resets to zero.

## Future Improvements
* Adding a vibrating motor for silent alerts.
* Integration with a mobile app via Bluetooth.
* 
