#!/bin/bash

# ===================================================================
# Project 2: Automated System Monitoring Shell Script
# Description: Monitors CPU, Memory, and Disk usage with alerts and logging.
# Author: [Your Name]
# ===================================================================

# Default Thresholds (Percentages)
CPU_THRESHOLD=80
MEM_THRESHOLD=80
DISK_THRESHOLD=90

# Log File Location
LOG_FILE="system_monitor.log"

# Function to get current timestamp
get_timestamp() {
    date "+%Y-%m-%d %H:%M:%S"
}

# Function: Log Messages
# Appends messages to the log file with a timestamp
log_message() {
    local message="$1"
    echo "$(get_timestamp) - $message" >> "$LOG_FILE"
}

# Function: Check System Metrics
monitor_system() {
    echo "---------------------------------"
    echo "Running System Scan..."
    
    # 1. CPU Usage calculation (using top in batch mode)
    # We grep the "Cpu(s)" line, take the idle time ($8 usually), and subtract from 100.
    CPU_IDLE=$(top -bn1 | grep "Cpu(s)" | awk '{print $8}' | cut -d. -f1)
    CPU_USAGE=$(( 100 - CPU_IDLE ))

    # 2. Memory Usage calculation (using free)
    MEM_TOTAL=$(free -m | grep Mem | awk '{print $2}')
    MEM_USED=$(free -m | grep Mem | awk '{print $3}')
    MEM_PERCENT=$(( 100 * MEM_USED / MEM_TOTAL ))

    # 3. Disk Usage calculation (using df for root /)
    DISK_USAGE=$(df -h / | awk 'NR==2 {print $5}' | tr -d '%')

    # Display Stats
    echo "CPU Usage: $CPU_USAGE%"
    echo "Memory Usage: $MEM_PERCENT%"
    echo "Disk Usage: $DISK_USAGE%"

    # Check Thresholds and Log Warnings
    if [ "$CPU_USAGE" -ge "$CPU_THRESHOLD" ]; then
        MSG="ALERT: High CPU Usage detected: $CPU_USAGE%"
        echo -e "\033[1;31m$MSG\033[0m" # Red text
        log_message "$MSG"
    else
        log_message "INFO: CPU Usage normal: $CPU_USAGE%"
    fi

    if [ "$MEM_PERCENT" -ge "$MEM_THRESHOLD" ]; then
        MSG="ALERT: High Memory Usage detected: $MEM_PERCENT%"
        echo -e "\033[1;31m$MSG\033[0m"
        log_message "$MSG"
    else
        log_message "INFO: Memory Usage normal: $MEM_PERCENT%"
    fi

    if [ "$DISK_USAGE" -ge "$DISK_THRESHOLD" ]; then
        MSG="ALERT: High Disk Usage detected: $DISK_USAGE%"
        echo -e "\033[1;31m$MSG\033[0m"
        log_message "$MSG"
    else
        log_message "INFO: Disk Usage normal: $DISK_USAGE%"
    fi
    echo "---------------------------------"
}

# Function: Update Thresholds
set_thresholds() {
    read -p "Enter new CPU Threshold (%): " new_cpu
    read -p "Enter new Memory Threshold (%): " new_mem
    read -p "Enter new Disk Threshold (%): " new_disk

    # Helper function to validate input is a number between 0 and 100
    is_valid() {
        # 1. Check if input is digits only (^[0-9]+$)
        # 2. Check if input is less than or equal to 100
        [[ "$1" =~ ^[0-9]+$ ]] && [ "$1" -le 100 ]
    }

    if is_valid "$new_cpu" && is_valid "$new_mem" && is_valid "$new_disk"; then
        CPU_THRESHOLD=$new_cpu
        MEM_THRESHOLD=$new_mem
        DISK_THRESHOLD=$new_disk
        echo "Thresholds updated successfully."
        log_message "NOTICE: User updated thresholds to CPU:$new_cpu, MEM:$new_mem, DISK:$new_disk"
    else
        echo -e "\033[1;31mError: Invalid input. Values must be integers between 0 and 100.\033[0m"
    fi
}

# Function: View Logs
view_logs() {
    if [ -f "$LOG_FILE" ]; then
        echo "Displaying last 20 lines of log file:"
        tail -n 20 "$LOG_FILE"
    else
        echo "No log file found yet."
    fi
}

# Function: Clear Logs
clear_logs() {
    > "$LOG_FILE"
    echo "Logs cleared."
    log_message "NOTICE: Log file cleared by user."
}

# Main Menu Loop
while true; do
    echo ""
    echo "=== AUTOMATED SYSTEM MONITORING MENU ==="
    echo "1. Run System Monitor (Scan Now)"
    echo "2. Set Alert Thresholds"
    echo "3. View Logs"
    echo "4. Clear Logs"
    echo "5. Exit"
    read -p "Select an option [1-5]: " choice

    case $choice in
        1) monitor_system ;;
        2) set_thresholds ;;
        3) view_logs ;;
        4) clear_logs ;;
        5) echo "Exiting Monitor. Goodbye!"; exit 0 ;;
        *) echo "Invalid option. Please try again." ;;
    esac
    
    # Small pause for readability
    sleep 1
done
