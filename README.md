# Sprinkio Sprinkler Controller

### Overview

Sprinkio is a smart, WiFi-connected household sprinkler controller. Sprinkio gives users the ability to control their sprinklers and reduce their water bills, all from a smartphone app. The controller uses environmental temperature and moisture sensor inputs to build a custom schedule that waters just the right amount. 

The controller was built as part of a senior capstone project. The hardware combines an Atmel ATmega 328p microcontroller and a Raspberry Pi to provide manual zone controls, zone status, WiFi connectivity, and a real-time clocking mechanism. The project also utilizes an iOS app to give users control of zone status remotely, on a shared WiFi network. 

This project utilizes three repositories: 

- [sprinkio-atmel-firmware](https://github.com/nikhilnrng/sprinkio-atmel-firmware): the firmware for the Atmel ATmega 328p microcontroller
- [sprinkio-raspberry-pi-firmware](https://github.com/nikhilnrng/sprinkio-atmel-firmware): the firmware for the Raspberry Pi
- [sprinkio-iphone-app](https://github.com/nikhilnrng/sprinkio-iphone-app): an iOS app that provides user with zone control over WiFi

### Raspberry Pi Firmware

The Raspberry Pi firmware is comprised of a C-code repository that is compiled and run on the Raspberry Pi. The role of the Raspberry Pi in the system is to deal with user inputs locally via the on-board button and rotary encoder and remotely via the iphone app. The Pi processes local user inputs in order to modify a menu displayed on the controller LCD. Additionally, the Pi communicates with the ATmega328p microcontroller over a serial connection in order to transfer settings and scheduling information or manually turn zones on and off.

Button presses and rotary encoder state changes occur randomly and unexpectedly, so special interrupt handlers were written to handle such event occurrences. A button press or rotary encoder turn triggers individual interrupt service handlers that update button and rotary encoder states to indicate an input event has occurred. Additionally, software-level de-bouncing is performed to clean up the event signals, ignoring unintentional button presses or rotary encoder turns and giving the user a more natural interaction with the LCD menu. 

The Raspberry Pi also runs a TCP server-side script upon being powered ON and connected to WiFi. The script waits for clients on the same network to connect to the Pi through the iPhone app and processes manual zone changes from the client. 

For a detailed report on the system operation, message me at nikhilnrng@gmail.com. 
