# Programming in C Summative Assessment

**Student Name:** Tamunotonye Briggs  
**Video Presentation:** [Link to your video here]

## Overview
This repository contains five distinct projects demonstrating knowledge of C programming, system operations, memory management, and hardware simulation. Each project targets specific learning outcomes ranging from low-level pointer manipulation to high-level multi-threaded networking.

---

## 🚦 Project 1: Smart Traffic Control System
**Technology:** C++ (Arduino), Tinkercad Simulation  
**Key Concepts:** Embedded Systems, Bitwise Logic, Interrupt Simulation

A smart traffic intersection simulation that adjusts signal timing dynamically based on real-time traffic density.
* **Dynamic Timing:** Green light duration extends automatically based on sensor input (simulated vehicle count).
* **Memory Management:** Uses `malloc` and `realloc` to dynamically log vehicle timestamps.
* **Concurrency:** Non-blocking design using `millis()` allows simultaneous sensor reading and light control.

**📂 File:** `Project1_Smart_Traffic/traffic_control.ino`  
**🔗 Live Simulation:** [PASTE YOUR TINKERCAD LINK HERE]

---

## 🖥️ Project 2: Automated System Monitor
**Technology:** Bash Scripting  
**Key Concepts:** Linux Process Management, Cron/Loops, Redirection

A robust shell script for monitoring server health (CPU, Memory, Disk).
* **Periodic Monitoring:** Can run in a background loop (every 10s) or as a one-off scan.
* **Alerting:** Triggers visual alerts and logs events when user-defined thresholds are breached.
* **Input Validation:** Prevents invalid threshold settings (0-100 range checks).

**How to Run:**
```bash
cd Project2_System_Monitor
chmod +x monitor.sh
./monitor.sh
```

---

## 🎓 Project 3: Student Management System
**Technology:** C  
**Key Concepts:** Structs, File I/O, CRUD, Analytics

A full-featured database application for managing student records.

* **Architecture:** Modular design separating data definitions (`student.h`), operations (`student_ops.c`), and analytics (`analytics.c`).
* **Features:** Add, Update, Delete, Search (Linear), and Sort (Bubble Sort).
* **Analytics:** Generates reports for Class Average, Top Student Overall, and Top Student by Course.
* **Persistence:** Saves and loads data from a text file to ensure records aren't lost on exit.

**How to Compile & Run:**
```bash
cd Project3_Student_Management
gcc main.c student_ops.c analytics.c -o student_sys
./student_sys
```

---

## 🧮 Project 4: Dynamic Math Engine
**Technology:** C  
**Key Concepts:** Function Pointers, Dynamic Memory (`realloc`), void pointers

A data processing engine that selects operations at runtime.

* **Function Pointers:** Uses an array of function pointers to dispatch operations (Sum, Avg, Min, Max) dynamically.
* **Dynamic Arrays:** Data set grows automatically as the user adds numbers.
* **Operations:** Supports Searching, Deleting by index, and Modifying values dynamically.

**How to Compile & Run:**
```bash
cd Project4_Math_Engine
gcc main.c math_utils.c -o math_engine
./math_engine
```

---

## 🕸️ Project 5: Multi-threaded Web Scraper
**Technology:** C, POSIX Threads (pthread), libcurl  
**Key Concepts:** Concurrency, Parallel Processing, Network I/O

A high-performance scraper that downloads multiple websites simultaneously.

* **Parallelism:** Spawns a separate thread for each URL to eliminate blocking.
* **Independence:** No thread synchronization required (each thread writes to its own file).
* **Error Handling:** Manages HTTP errors (e.g., 404s) and connection failures gracefully.

**Prerequisites:**
```bash
sudo apt-get install libcurl4-openssl-dev
```

**How to Compile & Run:**
```bash
cd Project5_Web_Scraper
gcc scraper.c -o scraper -lcurl -lpthread
./scraper
```
