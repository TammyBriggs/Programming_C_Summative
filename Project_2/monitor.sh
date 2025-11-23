#!/bin/bash

# ===================================================================
# Project 2: Automated System Monitoring Shell Script
# Description: Monitors CPU, Memory, and Disk usage with alerts and logging.
# ===================================================================

# Default Thresholds (Percentages)
CPU_THRESHOLD=80
MEM_THRESHOLD=80
DISK_THRESHOLD=90

# Log File Location
LOG_FILE="system_monitor.log"

get_timestamp() {
    date "+%Y-%m-%d %H:%M:%S"
}

log_message() {
    local message="$1"
    echo "$(get_timestamp) - $message" >> "$LOG_FILE"
}

monitor_system() {
    # 1. CPU Usage
    CPU_IDLE=$(top -bn1 | grep "Cpu(s)" | awk '{print $8}' | cut -d. -f1)
    CPU_USAGE=$(( 100 - CPU_IDLE ))

    # 2. Memory Usage
    MEM_TOTAL=$(free -m | grep Mem | awk '{print $2}')
    MEM_USED=$(free -m | grep Mem | awk '{print $3}')
    MEM_PERCENT=$(( 100 * MEM_USED / MEM_TOTAL ))

    # 3. Disk Usage
    DISK_USAGE=$(df -h / | awk 'NR==2 {print $5}' | tr -d '%')

    echo "--- System Status at $(get_timestamp) ---"
    echo "CPU: $CPU_USAGE% | Mem: $MEM_PERCENT% | Disk: $DISK_USAGE%"

    # Check Thresholds
    if [ "$CPU_USAGE" -ge "$CPU_THRESHOLD" ]; then
        MSG="ALERT: High CPU Usage detected: $CPU_USAGE%"
        echo -e "\033[1;31m$MSG\033[0m"
        log_message "$MSG"
    fi

    if [ "$MEM_PERCENT" -ge "$MEM_THRESHOLD" ]; then
        MSG="ALERT: High Memory Usage detected: $MEM_PERCENT%"
        echo -e "\033[1;31m$MSG\033[0m"
        log_message "$MSG"
    fi

    if [ "$DISK_USAGE" -ge "$DISK_THRESHOLD" ]; then
        MSG="ALERT: High Disk Usage detected: $DISK_USAGE%"
        echo -e "\033[1;31m$MSG\033[0m"
        log_message "$MSG"
    fi
}

# === Function: Periodic Execution ===
run_periodic_mode() {
    echo "Starting Periodic Monitoring (Ctrl+C to stop)..."
    log_message "NOTICE: Periodic monitoring started."
    while true; do
        monitor_system
        sleep 10 # Runs every 10 seconds
    done
}

set_thresholds() {
    read -p "Enter new CPU Threshold (%): " new_cpu
    read -p "Enter new Memory Threshold (%): " new_mem
    read -p "Enter new Disk Threshold (%): " new_disk

    # Updated Validation: Checks for Empty AND Number range 0-100
    is_valid() {
        if [[ -z "$1" ]]; then return 1; fi # Check if empty
        if ! [[ "$1" =~ ^[0-9]+$ ]]; then return 1; fi # Check if number
        if [ "$1" -lt 0 ] || [ "$1" -gt 100 ]; then return 1; fi # Check range
        return 0
    }

    if is_valid "$new_cpu" && is_valid "$new_mem" && is_valid "$new_disk"; then
        CPU_THRESHOLD=$new_cpu
        MEM_THRESHOLD=$new_mem
        DISK_THRESHOLD=$new_disk
        echo "Thresholds updated successfully."
        log_message "NOTICE: Updated thresholds - CPU:$new_cpu MEM:$new_mem DISK:$new_disk"
    else
        echo -e "\033[1;31mError: Inputs must be numbers between 0 and 100 and cannot be empty.\033[0m"
    fi
}

view_logs() {
    if [ -f "$LOG_FILE" ]; then
        echo "Last 20 log entries:"
        tail -n 20 "$LOG_FILE"
    else
        echo "No log file found."
    fi
}

clear_logs() {
    > "$LOG_FILE"
    echo "Logs cleared."
}

# Main Menu
while true; do
    echo ""
    echo "=== SYSTEM MONITOR ==="
    echo "1. Run Scan Once"
    echo "2. Start Periodic Monitor (Every 10s)"
    echo "3. Set Alert Thresholds"
    echo "4. View Logs"
    echo "5. Clear Logs"
    echo "6. Exit"
    read -p "Select [1-6]: " choice

    case $choice in
        1) monitor_system ;;
        2) run_periodic_mode ;;
        3) set_thresholds ;;
        4) view_logs ;;
        5) clear_logs ;;
        6) 
            echo "Exiting Monitor. Goodbye!"
            exit 0 
            ;;
        *) echo "Invalid option." ;;
    esac

    echo ""
    read -p "Press Enter to continue..." 
done
