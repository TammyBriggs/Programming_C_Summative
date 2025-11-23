# C Programming in C Summative Assessment

**Student Name:** [Tamunotonye Briggs]  
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
