#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Patient {
public:
    int patientId;
    string name;

    Patient(int id, string n) : patientId(id), name(n) {}
};


class TreeNode {
public:
    Patient* patient;
    TreeNode *left, *right;
    bool isThreaded;

    TreeNode(Patient* p) : patient(p), left(nullptr), right(nullptr), isThreaded(false) {}
};


class ThreadedBST {
private:
    TreeNode* root;

public:
    ThreadedBST() : root(nullptr) {}

    
    void insert(Patient* patient) {
        if (!root) {
            root = new TreeNode(patient);
            return;
        }

        TreeNode* node = root;
        TreeNode* parent = nullptr;

        while (node) {
            parent = node;
            if (patient->patientId < node->patient->patientId) { 
                if (node->left) {
                    node = node->left;
                } else {
                    node->left = new TreeNode(patient);
                    break;
                }
            } else {
                if (node->right) {
                    node = node->right;
                } else {
                    node->right = new TreeNode(patient);
                    break;
                }
            }
        }
    }

    
    void inOrderTraversal() {
        TreeNode* current = root;
        while (current) {
            while (current->left) {
                current = current->left;
            }

            cout << "Patient ID: " << current->patient->patientId 
                 << ", Name: " << current->patient->name << endl;

            if (current->isThreaded) {
                current = current->right;
            } else {
                current = current->right;
                while (current && current->left) {
                    current = current->left;
                }
            }
        }
    }

    void displayPatients() {
        inOrderTraversal();
    }
};


class Department {
public:
    string name;
    vector<Patient*> patients;
    ThreadedBST patientTree;

    Department(string n) : name(n) {}

    void addPatient(int id, string name) {
        Patient* newPatient = new Patient(id, name);
        patients.push_back(newPatient);
        patientTree.insert(newPatient);
    }

    void displayPatients() {
        cout << "Department: " << name << endl;
        patientTree.displayPatients();
    }
};


class Hospital {
private:
    vector<Department*> departments;

public:
    void addDepartment(string name) {
        departments.push_back(new Department(name));
    }

    Department* getDepartment(string name) {
        for (auto dept : departments) {
            if (dept->name == name)
                return dept;
        }
        return nullptr;
    }

    void displayDepartments() {
        cout << "Departments in the Hospital: " << endl;
        for (auto dept : departments) {
            cout << dept->name << endl;
        }
    }
};


int main() {
    Hospital hospital;

    int choice;
    do {
        cout << "\nHospital Management System" << endl;
        cout << "1. To Add Department" << endl;
        cout << "2. To Add Patient" << endl;
        cout << "3. To Display Departments" << endl;
        cout << "4. Display Patients in a Department" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string deptName;
                cout << "Enter department name: ";
                cin.ignore();  // Clear input buffer
                getline(cin, deptName);
                hospital.addDepartment(deptName);
                cout << "Department '" << deptName << "' added successfully!" << endl;
                break;
            }
            case 2: {
                string deptName;
                int patientId;
                string patientName;
                
                cout << "Enter department name: ";
                cin.ignore();
                getline(cin, deptName);
                
                Department* dept = hospital.getDepartment(deptName);
                if (!dept) {
                    cout << "Department not found!" << endl;
                    break;
                }
                
                cout << "Enter patient ID: ";
                cin >> patientId;
                cin.ignore();  
                cout << "Enter patient name: ";
                getline(cin, patientName);
                
                dept->addPatient(patientId, patientName);
                cout << "Patient '" << patientName << "' added successfully!" << endl;
                break;
            }
            case 3: {
                hospital.displayDepartments();
                break;
            }
            case 4: {
                string deptName;
                cout << "Enter department name: ";
                cin.ignore();
                getline(cin, deptName);
                
                Department* dept = hospital.getDepartment(deptName);
                if (dept) {
                    dept->displayPatients();
                } else {
                    cout << "Department not found!" << endl;
                }
                break;
            }
            case 5:
                cout << "Exiting!" << endl;
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
