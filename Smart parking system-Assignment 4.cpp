#include <bits/stdc++.h>
using namespace std;

class Vehicle {
public:
    string licensePlate;
    string type;
    time_t entryTime;
    time_t exitTime;

    Vehicle(string plate, string vehicleType) : licensePlate(plate), type(vehicleType) {
        entryTime = time(nullptr);
        exitTime = 0;
    }

    double calculateFee() {
        double rate = (type == "Emergency") ? 25.0 : (type == "VIP") ? 15.0 : 10.0;
        double duration = difftime(exitTime, entryTime) / 3600;
        return rate * duration;
    }
};

struct CompareVehicles {
    bool operator()(Vehicle a, Vehicle b) {
        if (a.type == "Emergency" && b.type != "Emergency") return true;
        if (a.type == "VIP" && b.type == "Normal") return true;
        return false;
    }
};

class SmartParkingSystem {
private:
    stack<Vehicle> parkingBay;
    queue<Vehicle> waitingQueue;
    priority_queue<Vehicle, vector<Vehicle>, CompareVehicles> priorityQueue;
    const int maxCapacity;
    double totalmoney;

public:
    SmartParkingSystem(int capacity) : maxCapacity(capacity), totalmoney(0.0) {}

    void vehicleEntry(string plate, string type) {
        Vehicle vehicle(plate, type);

        if (parkingBay.size() < maxCapacity) {
            parkingBay.push(vehicle);
            cout << "Vehicle " << plate << " parked in the bay." << endl;
        } else {
            if (type == "Emergency") {
                priorityQueue.push(vehicle);
                cout << "Emergency vehicle " << plate << " added to priority queue." << endl;
            } else {
                waitingQueue.push(vehicle);
                cout << "Vehicle " << plate << " added to waiting queue." << endl;
            }
        }
    }

    void vehicleExit(string plate) {
        if (parkingBay.empty()) {
            cout << "Parking bay is empty." << endl;
            return;
        }

        stack<Vehicle> tempStack;
        bool vehicleFound = false;

        while (!parkingBay.empty()) {
            Vehicle topVehicle = parkingBay.top();
            parkingBay.pop();

            if (topVehicle.licensePlate == plate) {
                topVehicle.exitTime = time(nullptr) + 3600;
                double fee = topVehicle.calculateFee();
                totalmoney += fee;
                cout << "Vehicle " << plate << " exited. Fee: $" << fee << endl;
                vehicleFound = true;
                break;
            } else {
                tempStack.push(topVehicle);
            }
        }

        while (!tempStack.empty()) {
            parkingBay.push(tempStack.top());
            tempStack.pop();
        }

        if (!vehicleFound) {
            cout << "Vehicle with license plate " << plate << " not found in the parking bay." << endl;
        }

        if (!priorityQueue.empty()) {
            Vehicle nextVehicle = priorityQueue.top();
            priorityQueue.pop();
            parkingBay.push(nextVehicle);
            cout << "Priority vehicle " << nextVehicle.licensePlate << " removed from priority queue. The vehicle was parked in Parking bay" << endl;
        } else if (!waitingQueue.empty()) {
            Vehicle nextVehicle = waitingQueue.front();
            waitingQueue.pop();
            parkingBay.push(nextVehicle);
            cout << "Waiting vehicle " << nextVehicle.licensePlate << " removed from waiting queue. The vehicle was parked in Parking bay" << endl;
        }
    }

    void displayStatus() {
        cout << "\n--- Parking System Status ---" << endl;
        cout << "Total Vehicles Parked: " << parkingBay.size() + waitingQueue.size() + priorityQueue.size() << endl;

        cout << "\nVehicles in Parking Bay: ";
        if (parkingBay.empty()) {
            cout << "None";
        } else {
            stack<Vehicle> temp = parkingBay;
            while (!temp.empty()) {
                cout << temp.top().licensePlate << " ";
                temp.pop();
            }
        }

        cout << "\nVehicles in Waiting Queue: ";
        if (waitingQueue.empty()) {
            cout << "None";
        } else {
            queue<Vehicle> temp = waitingQueue;
            while (!temp.empty()) {
                cout << temp.front().licensePlate << " ";
                temp.pop();
            }
        }

        cout << "\nVehicles in Priority Queue: ";
        if (priorityQueue.empty()) {
            cout << "None";
        } else {
            vector<Vehicle> temp;
            while (!priorityQueue.empty()) {
                temp.push_back(priorityQueue.top());
                priorityQueue.pop();
            }

            for (const auto& v : temp) {
                cout << v.licensePlate << " ";
                priorityQueue.push(v);
            }
        }

        cout << "\nTotal Money: $" << totalmoney << endl;
    }
};

int main() {
    int capacity;
    cout << "Enter parking capacity: ";
    cin >> capacity;

    SmartParkingSystem parkingSystem(capacity);

    int choice;
    do {
        cout << "\n1. Vehicle Entry\n2. Vehicle Exit\n3. Display Status\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string plate, type;
            cout << "Enter license plate: ";
            cin >> plate;
            cout << "Enter vehicle type (Normal/VIP/Emergency): ";
            cin >> type;
            parkingSystem.vehicleEntry(plate, type);
        } else if (choice == 2) {
            string plate;
            cout << "Enter license plate of vehicle to exit: ";
            cin >> plate;
            parkingSystem.vehicleExit(plate);
        } else if (choice == 3) {
            parkingSystem.displayStatus();
        }

    } while (choice != 4);

    return 0;
}
