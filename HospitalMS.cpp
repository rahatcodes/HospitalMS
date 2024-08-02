#include <iostream>
#include <queue>
#include <string>
#include <fstream>
using namespace std;

// Patient Node
struct Patient {
    int id;
    string name;
    int age;
    Patient* next;
};

Patient* head = nullptr;

void addPatient(int id, const string& name, int age) {
    Patient* newPatient = new Patient{id, name, age, nullptr};
    if (!head) {
        head = newPatient;
    } else {
        Patient* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newPatient;
    }
    cout << "Add successful: Patient ID " << id << " added." << endl;
}

void displayPatients() {
    Patient* temp = head;
    while (temp) {
        cout << "ID: " << temp->id << ", Name: " << temp->name << ", Age: " << temp->age << endl;
        temp = temp->next;
    }
}

void loadPatientsFromFile() {
    ifstream infile("patients.txt");
    if (infile.is_open()) {
        int id, age;
        string name;
        while (infile >> id >> ws && getline(infile, name) && infile >> age) {
            addPatient(id, name, age);
        }
        infile.close();
    }
}

void savePatientsToFile() {
    ofstream outfile("patients.txt");
    if (outfile.is_open()) {
        Patient* temp = head;
        while (temp) {
            outfile << temp->id << endl << temp->name << endl << temp->age << endl;
            temp = temp->next;
        }
        outfile.close();
    }
}

// Queue for Appointment Management with File Handling
queue<int> q;

void addPatientToQueue(int patientId) {
    q.push(patientId);
    cout << "Add successful: Patient ID " << patientId << " added to appointment queue." << endl;
}

void processNextPatient() {
    if (!q.empty()) {
        int patientId = q.front();
        q.pop();
        cout << "Processing successful: Patient ID " << patientId << " processed." << endl;
    } else {
        cout << "No patients in queue." << endl;
    }
}

void showAppointmentList() {
    if (q.empty()) {
        cout << "No patients in queue." << endl;
        return;
    }

    queue<int> tempQueue = q;
    while (!tempQueue.empty()) {
        cout << "Patient ID: " << tempQueue.front() << endl;
        tempQueue.pop();
    }
}

void loadAppointmentsFromFile() {
    ifstream infile("appointments.txt");
    if (infile.is_open()) {
        int patientId;
        while (infile >> patientId) {
            q.push(patientId);
        }
        infile.close();
    }
}

void saveAppointmentsToFile() {
    ofstream outfile("appointments.txt");
    if (outfile.is_open()) {
        queue<int> tempQueue = q;
        while (!tempQueue.empty()) {
            outfile << tempQueue.front() << endl;
            tempQueue.pop();
        }
        outfile.close();
    }
}

// Doctor Node
struct Doctor {
    int id;
    string name;
    string specialization;
    Doctor* left;
    Doctor* right;
};

Doctor* root = nullptr;

Doctor* insertDoctor(Doctor* node, int id, const string& name, const string& specialization) {
    if (!node) {
        return new Doctor{id, name, specialization, nullptr, nullptr};
    }
    if (name < node->name) {
        node->left = insertDoctor(node->left, id, name, specialization);
    } else {
        node->right = insertDoctor(node->right, id, name, specialization);
    }
    return node;
}

void inorderTraversal(Doctor* node) {
    if (node) {
        inorderTraversal(node->left);
        cout << "ID: " << node->id << ", Name: " << node->name << ", Specialization: " << node->specialization << endl;
        inorderTraversal(node->right);
    }
}

Doctor* searchDoctor(Doctor* node, const string& name) {
    if (!node || node->name == name) {
        return node;
    }
    if (name < node->name) {
        return searchDoctor(node->left, name);
    } else {
        return searchDoctor(node->right, name);
    }
}

Doctor* deleteDoctor(Doctor* node, const string& name) {
    if (!node) return node;
    if (name < node->name) {
        node->left = deleteDoctor(node->left, name);
    } else if (name > node->name) {
        node->right = deleteDoctor(node->right, name);
    } else {
        if (!node->left) {
            Doctor* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            Doctor* temp = node->left;
            delete node;
            return temp;
        }
        Doctor* temp = node->right;
        while (temp && temp->left) {
            temp = temp->left;
        }
        node->name = temp->name;
        node->specialization = temp->specialization;
        node->right = deleteDoctor(node->right, temp->name);
    }
    return node;
}

void saveDoctorsToFile(Doctor* node, ofstream& outfile) {
    if (node) {
        saveDoctorsToFile(node->left, outfile);
        outfile << node->id << endl << node->name << endl << node->specialization << endl;
        saveDoctorsToFile(node->right, outfile);
    }
}

Doctor* loadDoctorsFromFile(Doctor* node, ifstream& infile) {
    int id;
    string name, specialization;
    if (infile >> id >> ws && getline(infile, name) && getline(infile, specialization)) {
        node = insertDoctor(node, id, name, specialization);
        node->left = loadDoctorsFromFile(node->left, infile);
        node->right = loadDoctorsFromFile(node->right, infile);
    }
    return node;
}

void loadAllDoctorsFromFile() {
    ifstream infile("doctors.txt");
    if (infile.is_open()) {
        root = loadDoctorsFromFile(root, infile);
        infile.close();
    }
}

void saveAllDoctorsToFile() {
    ofstream outfile("doctors.txt");
    if (outfile.is_open()) {
        saveDoctorsToFile(root, outfile);
        outfile.close();
    }
}

void addDoctor(int id, const string& name, const string& specialization) {
    root = insertDoctor(root, id, name, specialization);
    cout << "Add successful: Doctor ID " << id << " added." << endl;
}

void displayDoctors() {
    inorderTraversal(root);
}

void searchDoctor(const string& name) {
    Doctor* foundDoctor = searchDoctor(root, name);
    if (foundDoctor) {
        cout << "Doctor found: ID: " << foundDoctor->id << ", Name: " << foundDoctor->name << ", Specialization: " << foundDoctor->specialization << endl;
    } else {
        cout << "Doctor with name " << name << " not found." << endl;
    }
}

// POS Menu
void posMenu() {
    int choice;
    do {
        cout << "\n--- POS Menu ---" << endl;
        cout << "1. Add Patient" << endl;
        cout << "2. Search Doctor" << endl;
        cout << "3. Display Patients' List" << endl;
        cout << "4. Add Patient to Appointment Queue" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, age;
                string name;
                cout << "Enter Patient ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Patient Name: ";
                getline(cin, name);
                cout << "Enter Patient Age: ";
                cin >> age;
                addPatient(id, name, age);
                break;
            }
            case 2: {
                string name;
                cout << "Enter Doctor Name to search: ";
                cin.ignore();
                getline(cin, name);
                searchDoctor(name);
                break;
            }
            case 3: {
                cout << "Patients List:" << endl;
                displayPatients();
                break;
            }
            case 4: {
                int patientId;
                cout << "Enter Patient ID to add to appointment queue: ";
                cin >> patientId;
                addPatientToQueue(patientId);
                break;
            }
            case 5: {
                cout << "Returning to Main Menu..." << endl;
                break;
            }
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);
}

// Admin Menu
void adminMenu() {
    int choice;
    do {
        cout << "\n--- Admin Menu ---" << endl;
        cout << "1. Add Doctor" << endl;
        cout << "2. Display Patients" << endl;
        cout << "3. Display Doctors" << endl;
        cout << "4. Process Appointments" << endl;
        cout << "5. Show Appointment List" << endl;
        cout << "6. Delete Doctor" << endl;
        cout << "7. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string name, specialization;
                cout << "Enter Doctor ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Doctor Name: ";
                getline(cin, name);
                cout << "Enter Doctor Specialization: ";
                getline(cin, specialization);
                addDoctor(id, name, specialization);
                break;
            }
            case 2: {
                cout << "Patients List:" << endl;
                displayPatients();
                break;
            }
            case 3: {
                cout << "Doctors List:" << endl;
                displayDoctors();
                break;
            }
            case 4: {
                processNextPatient();
                break;
            }
            case 5: {
                showAppointmentList();
                break;
            }
            case 6: {
                string name;
                cout << "Enter Doctor Name to delete: ";
                cin.ignore();
                getline(cin, name);
                root = deleteDoctor(root, name);
                cout << "Delete successful: Doctor with name " << name << " deleted." << endl;
                break;
            }
            case 7: {
                cout << "Returning to Main Menu..." << endl;
                break;
            }
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 7);
}

// Main Function
int main() {
    loadPatientsFromFile();
    loadAppointmentsFromFile();
    loadAllDoctorsFromFile();

    int userType;
    do {
        cout << "\n--- Hospital Management System ---" << endl;
        cout << "1. POS" << endl;
        cout << "2. Admin" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> userType;

        switch (userType) {
            case 1:
                posMenu();
                break;
            case 2:
                adminMenu();
                break;
            case 3:
                cout << "Exiting the system..." << endl;
                savePatientsToFile();
                saveAppointmentsToFile();
                saveAllDoctorsToFile();
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (userType != 3);
    return 0;
}
