# 🚗 Car Black Box

This project implements a **Car Black Box System** using a **PIC microcontroller** to continuously monitor and record important vehicle events such as speed, gear position, and collision events.

## 📌 Description

The Car Black Box is a **PIC-based embedded system** designed to monitor vehicle parameters and maintain an event log for later analysis. The system uses an **ADC for speed measurement, DS1307 RTC for timekeeping, EEPROM for storing event records, CLCD for displaying information, and a matrix keypad for user interaction**.

The recorded events can be viewed through the LCD or downloaded through UART for analysis.

## ⭐ Features

🏎️ Monitor Vehicle Speed

⚙️ Monitor Gear Position

💥 Detect and Record Collision Events

⏰ Real-Time Date and Time using DS1307 RTC

💾 Store Vehicle Event Logs in EEPROM

📺 Display Vehicle Information on CLCD

🔐 Password-Protected Menu

🔑 Change Password

📋 View Stored Event Logs

🗑️ Clear Event Logs

📥 Download Logs through UART

⌨️ Matrix Keypad-Based User Interface

⏱️ Set and Modify RTC Time

## 🛠️ Technologies Used

**Programming Language:** Embedded C

**Microcontroller:** PIC

### Concepts / Peripherals Used

* ADC
* I2C Communication
* UART Communication
* DS1307 RTC
* EEPROM
* Character LCD (CLCD)
* Matrix Keypad
* Timer0
* Structures and Functions
* Modular Programming
* Embedded C Programming
* Data Logging

## 📁 Project Structure

Car-Black-Box

* │
* ├── main.c
* ├── main.h
* ├── adc.c
* ├── adc.h
* ├── clcd.c
* ├── clcd.h
* ├── ds1307.c
* ├── ds1307.h
* ├── i2c.c
* ├── i2c.h
* ├── eeprom.c
* ├── eeprom.h
* ├── matrix_keypad.c
* ├── matrix_keypad.h
* ├── sensor.c
* ├── sensor.h
* ├── password.c
* ├── menu.c
* ├── timer0.c
* └── Makefile

## ⚙️ How It Works

🚀 **Program starts and initializes the peripherals** such as CLCD, I2C, DS1307 RTC, ADC, matrix keypad, and UART.

📺 **Current time is obtained from the DS1307 RTC** and displayed on the CLCD.

🏎️ **Vehicle speed is measured using the ADC** and converted into a speed value between 0 and 99.

⚙️ **Gear position is controlled using the matrix keypad**, allowing the system to simulate gear-up and gear-down operations.

💥 **Collision event is triggered using the collision key** and recorded as a vehicle event.

💾 **Important vehicle information is stored in EEPROM**, including:

* Time
* Gear position
* Speed

🔐 **User authentication is performed using an 8-key password** before accessing the menu.

📋 **Stored logs can be viewed** on the CLCD using the menu.

🗑️ **Stored logs can be cleared** when required.

📥 **Event logs can be downloaded through UART** and viewed using a terminal such as Tera Term.

⏰ **RTC time can be modified** through the Set Time option.

❌ **User can exit the menu** and return to the main vehicle monitoring screen.

## 🎛️ User Controls

| Key    | Function                |
| ------ | ----------------------- |
| MK_SW1 | Gear Up / Scroll Up     |
| MK_SW2 | Gear Down / Scroll Down |
| MK_SW3 | Collision / Toggle      |
| MK_SW4 | Menu                    |
| MK_SW5 | Enter                   |
| MK_SW6 | Exit                    |

## 📚 Learning Outcomes

* Implemented a **PIC-based embedded system** using Embedded C.
* Learned to interface **ADC with a PIC microcontroller** for speed measurement.
* Worked with **DS1307 RTC** for real-time clock functionality.
* Implemented **I2C communication** with RTC and EEPROM.
* Learned **EEPROM-based event data logging**.
* Implemented **matrix keypad interfacing** for user input.
* Worked with **CLCD interfacing** for displaying vehicle information.
* Implemented **UART communication** for downloading stored logs.
* Implemented **password authentication and menu navigation**.
* Improved understanding of **modular programming and embedded system design**.
* Gained practical experience in developing a **vehicle monitoring and event logging system**.

## 👩‍💻 Author

**Dhanushree Reddy**
