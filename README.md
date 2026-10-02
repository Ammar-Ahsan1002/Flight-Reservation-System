# ✈️ Flight Management System

A console-based **Flight Management System** developed in **C++** as a first-semester programming project. The system allows users to view available flights, book and cancel reservations, manage passenger bookings, and provides an admin portal for managing flight information.

The project also uses **file handling** to store flight and booking information so that data can be loaded and saved between program executions.

---

## 📌 Project Overview

The **Flight Management System** is designed to simulate a basic airline reservation system through a command-line interface.

The system provides two main types of functionality:

* **Passenger/User Operations**
* **Administrator Operations**

Flight information and booking records are stored in text files using C++ file handling.

---

## ✨ Features

### 👤 User Features

* View available flights by destination and date
* View flights for the selected date and the following date
* Book a flight
* Select Business or Economy class
* View available seat layout
* Prevent booking an already occupied seat
* Enter passenger information
* Calculate flight fare
* Apply passenger-type discount
* Calculate 5% tax
* Generate a boarding-pass-style booking summary
* View all existing bookings
* Cancel an existing booking

### 🛠️ Admin Features

The system includes a password-protected Admin Portal.

Administrators can:

* Add new flights
* Cancel existing flights
* Update/delay flight timings
* Manage flight information

### 💺 Seat Management

The system provides:

* **5 Business Class seats**

  * B1
  * B2
  * B3
  * B4
  * B5

* **10 Economy Class seats**

  * E1 to E10

Already booked seats are displayed as unavailable.

---

## 💰 Fare & Discount System

The system calculates the final ticket price using:

**Final Fare = Base Fare − Discount + Tax**

### Discount

Passengers classified as:

* Student
* Military
* Senior

receive a **5% discount** on the base fare.

Normal passengers do not receive a discount.

### Tax

A **5% tax** is applied to the base fare.

The system displays:

* Base Fare
* Discount
* Tax
* Total Fare

---

## 📅 Date Validation

The system accepts dates in the following format:

```text
DD-MM-YYYY
```

It validates:

* Date format
* Valid month
* Valid day
* Leap years
* Minimum supported date

The current implementation accepts dates from **09-01-2026 onwards**.

---

## 📂 Project Structure

```text
Flight-Management-System/
│
├── FlightManagementSystem.cpp
├── flights.txt
├── bookings.txt
├── FlightManagementSystem.exe
└── README.md
```

### File Description

| File                         | Description                          |
| ---------------------------- | ------------------------------------ |
| `FlightManagementSystem.cpp` | Main C++ source code                 |
| `flights.txt`                | Stores flight information            |
| `bookings.txt`               | Stores passenger booking information |
| `FlightManagementSystem.exe` | Compiled executable                  |
| `README.md`                  | Project documentation                |

---

## 💾 Data Storage

The project uses text files for persistent data storage.

### `flights.txt`

Flight records contain:

```text
Flight Number
Departure
Destination
Time
Economy Fare
Business Fare
```

The program automatically loads flight information when it starts and saves changes when flights are added, cancelled, or updated.

### `bookings.txt`

Booking records contain:

```text
Flight Number
Passenger Name
Passport Number
Class
Seat
Date
Passenger Type
```

Booking information is separated using the `|` character.

---

## 🖥️ Main Menu

When the program starts, users are presented with the following menu:

```text
===== FLIGHT RESERVATION SYSTEM =====

1. View Flights
2. Book Flight
3. Cancel Booking
4. View Bookings
5. Admin Portal
6. Exit
```

---

## 🔐 Admin Login

The Admin Portal is protected by login credentials.

### Default Credentials

```text
Username: admin
Password: admin123
```

> **Note:** These credentials are hard-coded in the current version of the project and are intended for demonstration/academic purposes.

---

## 🛠️ Technologies Used

* **C++**
* **Object-oriented programming concepts**
* **Structures**
* **Arrays**
* **Functions**
* **File Handling**
* **String Manipulation**
* **Loops and Conditional Statements**
* **Input/Output Streams**

### C++ Libraries Used

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
```

---

## ⚙️ How to Run

### Option 1 — Run the Executable

If the executable is included in the repository:

1. Download or clone the repository.
2. Make sure the `.exe`, `.cpp`, and `.txt` files are in the correct project folder.
3. Run:

```text
FlightManagementSystem.exe
```

> The `.txt` files should remain in the same directory as the executable because the program reads and writes them using relative filenames.

---

### Option 2 — Compile from Source

If you have a C++ compiler such as **g++**, open a terminal in the project directory and run:

```bash
g++ FlightManagementSystem.cpp -o FlightManagementSystem
```

Then run:

### Windows

```bash
FlightManagementSystem.exe
```

### Linux/macOS

```bash
./FlightManagementSystem
```

---

## 🔄 System Workflow

```text
                 ┌──────────────────────┐
                 │   Program Starts     │
                 └──────────┬───────────┘
                            │
                            ▼
                 ┌──────────────────────┐
                 │ Load Flight &        │
                 │ Booking Data         │
                 └──────────┬───────────┘
                            │
                            ▼
                 ┌──────────────────────┐
                 │     Main Menu        │
                 └──────────┬───────────┘
                            │
          ┌─────────────────┼─────────────────┐
          ▼                 ▼                 ▼
    View Flights       Book Flight      Cancel Booking
          │                 │                 │
          │                 ▼                 │
          │            Seat Selection         │
          │                 │                 │
          │                 ▼                 │
          │          Passenger Details        │
          │                 │                 │
          │                 ▼                 │
          │        Fare + Discount + Tax      │
          │                 │                 │
          │                 ▼                 │
          │          Boarding Pass            │
          │                                   │
          └─────────────────┬─────────────────┘
                            │
                            ▼
                     View Bookings
                            │
                            ▼
                      Admin Portal
```

---

## 🧑‍💻 Learning Objectives

This project was developed as a first-semester C++ project to practice fundamental programming concepts, including:

* Designing a menu-driven console application
* Working with structures
* Using arrays to manage records
* Creating reusable functions
* Reading and writing files
* Processing and validating user input
* Performing calculations
* Managing records dynamically within fixed-size arrays
* Implementing basic authentication
* Building a practical application around real-world requirements

---

## 🚀 Possible Future Improvements

The current system can be further improved by adding:

* Graphical User Interface (GUI)
* Database integration
* Dynamic data structures
* Multiple user accounts
* Secure password handling
* Passenger account registration
* Flight search by departure and destination
* More advanced date handling
* Automatic seat assignment
* Ticket printing/exporting
* Email/SMS booking confirmation
* Payment processing
* Flight status tracking
* Better input validation
* Improved error handling

---

## 👨‍💻 Project Information

**Project:** Flight Management System
**Language:** C++
**Type:** Console-Based Application
**Level:** First Semester / Beginner C++ Project

---

## 📜 License

This project was created for **educational and academic purposes**.

You are welcome to explore the source code and use it for learning purposes.

