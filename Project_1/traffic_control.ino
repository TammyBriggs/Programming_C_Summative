/*
 * Project 1: Smart Traffic Control & Monitoring System
 * Explicit Prototypes added to solve Compilation Errors
 */

#include <stdlib.h> 

// ==========================================
// 1. STRUCT DEFINITION (MUST BE AT THE TOP)
// ==========================================
struct TrafficLane {
  int id;
  int rPin, yPin, gPin;
  int sensorPin;
  int vehicleCount;
  int* vehicleLogs; 
  int logCapacity;  
};

// ==========================================
// 2. FUNCTION PROTOTYPES (THE FIX)
// These tell the compiler that these functions exist 
// and that they use the TrafficLane struct defined above.
// ==========================================
void setLights(TrafficLane* lane, int r, int y, int g);
void registerVehicle(TrafficLane* lane);
TrafficLane* createLane(int id, int r, int y, int g, int s);

// ==========================================
// 3. CONFIGURATION & GLOBALS
// ==========================================
const unsigned long DEFAULT_GREEN_TIME = 3000;
const unsigned long YELLOW_TIME = 1000;
const unsigned long LOG_INTERVAL = 5000; 

TrafficLane* laneA;
TrafficLane* laneB;

// State Machine Variables
int systemState = 0; 
unsigned long lastStateChange = 0;
unsigned long lastLogTime = 0;
bool emergencyMode = false;

// ==========================================
// 4. HELPER FUNCTIONS
// ==========================================

// Create Lane
TrafficLane* createLane(int id, int r, int y, int g, int s) {
  TrafficLane* lane = (TrafficLane*)malloc(sizeof(TrafficLane));
  if (lane == NULL) return NULL;
  
  lane->id = id;
  lane->rPin = r; lane->yPin = y; lane->gPin = g;
  lane->sensorPin = s;
  lane->vehicleCount = 0;
  lane->logCapacity = 2; 
  lane->vehicleLogs = (int*)malloc(lane->logCapacity * sizeof(int));
  
  pinMode(r, OUTPUT); pinMode(y, OUTPUT); pinMode(g, OUTPUT);
  pinMode(s, INPUT);
  return lane;
}

// Set Lights
void setLights(TrafficLane* lane, int r, int y, int g) {
  digitalWrite(lane->rPin, r);
  digitalWrite(lane->yPin, y);
  digitalWrite(lane->gPin, g);
}

// Register Vehicle
void registerVehicle(TrafficLane* lane) {
  lane->vehicleCount++;
  
  if (lane->vehicleCount >= lane->logCapacity) {
    lane->logCapacity += 2;
    int* temp = (int*)realloc(lane->vehicleLogs, lane->logCapacity * sizeof(int));
    if (temp != NULL) {
      lane->vehicleLogs = temp;
    } else {
      return; // Memory failure
    }
  }
  lane->vehicleLogs[lane->vehicleCount - 1] = millis() / 1000;
  Serial.print("Vehicle detected in Lane ");
  Serial.println(lane->id);
}

// ==========================================
// 5. MAIN SETUP & LOOP
// ==========================================
void setup() {
  Serial.begin(9600);
  Serial.println("System Initializing...");

  // Lane A: Pins 2(R), 3(Y), 4(G), Sensor 5
  laneA = createLane(1, 2, 3, 4, 5);
  // Lane B: Pins 6(R), 7(Y), 8(G), Sensor 9
  laneB = createLane(2, 6, 7, 8, 9);
  
  // Emergency Button: Pin 10
  pinMode(10, INPUT); 

  if (laneA == NULL || laneB == NULL) {
    Serial.println("CRITICAL: System Memory Failure");
    while(1); 
  }
  
  Serial.println("System Ready.");
}

void checkSensors() {
  static int lastStateA = LOW;
  static int lastStateB = LOW;
  
  int currentStateA = digitalRead(laneA->sensorPin);
  int currentStateB = digitalRead(laneB->sensorPin);

  if (currentStateA == HIGH && lastStateA == LOW) registerVehicle(laneA);
  if (currentStateB == HIGH && lastStateB == LOW) registerVehicle(laneB);

  // Emergency Button Logic
  if (digitalRead(10) == HIGH) {
    emergencyMode = !emergencyMode;
    Serial.print("Emergency Mode: ");
    Serial.println(emergencyMode ? "ON" : "OFF");
    delay(500); 
  }

  lastStateA = currentStateA;
  lastStateB = currentStateB;
}

void updateTrafficLights() {
  if (emergencyMode) {
    unsigned long currentMillis = millis();
    if ((currentMillis / 500) % 2 == 0) {
      setLights(laneA, 1, 0, 0); setLights(laneB, 1, 0, 0);
    } else {
      setLights(laneA, 0, 0, 0); setLights(laneB, 0, 0, 0);
    }
    return;
  }

  unsigned long currentMillis = millis();
  unsigned long duration = currentMillis - lastStateChange;
  
  unsigned long dynamicGreenA = DEFAULT_GREEN_TIME + (laneA->vehicleCount * 500);
  unsigned long dynamicGreenB = DEFAULT_GREEN_TIME + (laneB->vehicleCount * 500);
  if (dynamicGreenA > 8000) dynamicGreenA = 8000;
  if (dynamicGreenB > 8000) dynamicGreenB = 8000;

  switch (systemState) {
    case 0: // A Green
      setLights(laneA, 0, 0, 1); setLights(laneB, 1, 0, 0);
      if (duration > dynamicGreenA) { systemState = 1; lastStateChange = currentMillis; laneA->vehicleCount = 0; }
      break;
    case 1: // A Yellow
      setLights(laneA, 0, 1, 0); setLights(laneB, 1, 0, 0);
      if (duration > YELLOW_TIME) { systemState = 2; lastStateChange = currentMillis; }
      break;
    case 2: // B Green
      setLights(laneA, 1, 0, 0); setLights(laneB, 0, 0, 1);
      if (duration > dynamicGreenB) { systemState = 3; lastStateChange = currentMillis; laneB->vehicleCount = 0; }
      break;
    case 3: // B Yellow
      setLights(laneA, 1, 0, 0); setLights(laneB, 0, 1, 0);
      if (duration > YELLOW_TIME) { systemState = 0; lastStateChange = currentMillis; }
      break;
  }
}

void handleInterface() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastLogTime >= LOG_INTERVAL) {
    lastLogTime = currentMillis;
    Serial.println("--- LOG ENTRY ---");
    Serial.print("Time: "); Serial.println(currentMillis/1000);
    Serial.print("Lane A Traffic: "); Serial.println(laneA->vehicleCount);
    Serial.print("Lane B Traffic: "); Serial.println(laneB->vehicleCount);
  }
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == 's') {
      Serial.print("State: "); Serial.println(systemState);
    }
  }
}

void loop() {
  checkSensors();
  updateTrafficLights();
  handleInterface();
}
