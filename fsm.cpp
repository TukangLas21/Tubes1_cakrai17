#include "fsm.hpp"
#include <time.h>
#include <thread>

using namespace std;

uint32_t millis() {
    return (uint32_t) (clock() * 1000 / CLOCKS_PER_SEC);
}

FSM::FSM() {
    this->currentState = SystemState::INIT;
    this->lastHeartbeat = 0;
    this->errorCount = 0;
    this->stateHistory = vector<pair<SystemState, uint32_t>>();
}

FSM::FSM(uint32_t delay) : FSM() {
    this->delay = delay;
}

FSM::~FSM() {
    stateHistory.clear();
}

SystemState FSM::getCurrentState() const {
    return currentState;
}

void FSM::transitionToState(SystemState newState) {
    currentState = newState;
    lastHeartbeat = millis();
}

void FSM::setDelay(uint32_t delay) {
    this->delay = delay;
}

void FSM::getDelay(uint32_t &delay) const {
    delay = this->delay;
}

void FSM::setErrorCount(int count) {
    errorCount = count;
}

int FSM::getErrorCount() const {
    return errorCount;
}

void FSM::setMoveCount(int count) {
    moveCount = count;
}

int FSM::getMoveCount() const {
    return moveCount;
}

void FSM::addStateToHistory(SystemState state, uint32_t time) {
    stateHistory.emplace_back(state, time); // emplace_back instead of push_back to construct pair in place
}

vector<pair<SystemState, uint32_t>> FSM::getStateHistory() const {
    return stateHistory;
}

uint32_t FSM::getLastHeartbeat() const {
    return lastHeartbeat;
}

void FSM::setLastHeartbeat(uint32_t time) {
    lastHeartbeat = time;
}

void FSM::start() {
    while (true) {
        update();
        this_thread::sleep_for(chrono::milliseconds(1000)); // Sleep for 1000 milliseconds
    }
}

void FSM::update() {
    switch (currentState) {
        case SystemState::INIT:
            performInit();
            break;
        case SystemState::IDLE:
            performProcess();
            break;
        case SystemState::MOVEMENT:
            performMovement();
            break;
        case SystemState::SHOOTING:
            performShooting();
            break;
        case SystemState::CALCULATION:
            performCalculation();
            break;
        case SystemState::ERROR:
            performErrorHandling();
            break;
        case SystemState::STOPPED:
            shutdown();
            break;
    }
    lastHeartbeat = millis(); 
    addStateToHistory(currentState, lastHeartbeat);
}

// Helper function to convert SystemState to string for printing
string stateToString(SystemState state) {
    switch (state) {
        case SystemState::INIT: return "INIT";
        case SystemState::IDLE: return "IDLE";
        case SystemState::MOVEMENT: return "MOVEMENT";
        case SystemState::SHOOTING: return "SHOOTING";
        case SystemState::CALCULATION: return "CALCULATION";
        case SystemState::ERROR: return "ERROR";
        case SystemState::STOPPED: return "STOPPED";
        default: return "UNKNOWN";
    }
}

void FSM::printStatus() {
    cout << "Current State: " << stateToString(currentState) << endl;
    cout << "Last Heartbeat: " << lastHeartbeat << " ms" << endl;
    cout << "Delay: " << delay << " ms" << endl;
    cout << "Error Count: " << errorCount << endl;
}

void FSM::printStateHistory() {
    cout << "State History:" << endl;
    for (const auto &entry : stateHistory) {
        cout << "State: " << stateToString(entry.first) << ", Time: " << entry.second << " ms" << endl;
    }
}

void FSM::performInit() {
    setDelay(1000);
    transitionToState(SystemState::IDLE);
    setLastHeartbeat(millis());
    cout << "Initializing system..." << endl;
    printStatus();
}

void FSM::performProcess() {
    int choice;

    do
    {
        cout << "Select a process: " << endl;
        cout << "1. Display status and state history (IDLE)" << endl;
        cout << "2. Move (MOVEMENT)" << endl;
        cout << "3. Shoot (SHOOTING)" << endl;
        cout << "4. Calculate (CALCULATION)" << endl;
        cin >> choice;
    } while (choice < 1 || choice > 4);

    switch (choice) {
        case 1:
            printStatus();
            printStateHistory();
            transitionToState(SystemState::IDLE);
            break;
        case 2:
            transitionToState(SystemState::MOVEMENT);
            break;
        case 3:
            transitionToState(SystemState::SHOOTING);
            break;
        case 4:
            transitionToState(SystemState::CALCULATION);
            break;
        default:
            break; // do nothing
    }
}

void FSM::performMovement() {
    cout << "Moving..." << endl;
    moveCount++;
    if (moveCount >= 3) {
        transitionToState(SystemState::SHOOTING);
    } else {
        transitionToState(SystemState::IDLE);
    }
    setLastHeartbeat(millis());
}

void FSM::performShooting() {
    cout << "Shooting..." << endl;
    moveCount = 0; 
    transitionToState(SystemState::IDLE);
    setLastHeartbeat(millis());
}

void FSM::performCalculation() {
    cout << "Performing calculation..." << endl;
    if (moveCount == 0) {
        transitionToState(SystemState::ERROR);
    } else {
        transitionToState(SystemState::IDLE);
    }
}

void FSM::performErrorHandling() {
    cout << "Error occurred! Move count is zero." << endl;
    errorCount++;
    if (errorCount > 3) {
        transitionToState(SystemState::STOPPED);
    } else {
        transitionToState(SystemState::IDLE);
    }
}

void FSM::shutdown() {
    cout << "System stopped, shutting down..." << endl;
    stateHistory.clear();
    setLastHeartbeat(millis());
}