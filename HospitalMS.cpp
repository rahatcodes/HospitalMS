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

// Linked List for Patient Records
class PatientList {
private:
    Patient* head;

public:
    PatientList() : head(nullptr) {
        loadPatientsFromFile();
    }

    ~PatientList() {
        savePatientsToFile();
    }

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
};

// Queue for Appointment Management with File Handling
class AppointmentQueue {
private:
    queue<int> q;

public:
    AppointmentQueue() {
        loadAppointmentsFromFile();
    }

    ~AppointmentQueue() {
        saveAppointmentsToFile();
    }

    void addPatientToQueue(int patientId) {
        q.push(patientId);
    }

    void processNextPatient() {
        if (!q.empty()) {
            int patientId = q.front();
            q.pop();
            cout << "Processing patient with ID: " << patientId << endl;
        } else {
            cout << "No patients in queue." << endl;
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
};

// Doctor Node
struct Doctor {
    int id;
    string name;
    string specialization;
    Doctor* left;
    Doctor* right;
};

// BST for Doctor Management
class DoctorBST {
private:
    Doctor* root;

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

public:
    DoctorBST() : root(nullptr) {
        loadDoctorsFromFile();
    }

    ~DoctorBST() {
        saveDoctorsToFile();
    }

    void addDoctor(int id, const string& name, const string& specialization) {
        root = insertDoctor(root, id, name, specialization);
    }

    void displayDoctors() {
        inorderTraversal(root);
    }

    void loadDoctorsFromFile() {
        ifstream infile("doctors.txt");
        if (infile.is_open()) {
            root = loadDoctorsFromFile(root, infile);
            infile.close();
        }
    }

    void saveDoctorsToFile() {
        ofstream outfile("doctors.txt");
        if (outfile.is_open()) {
            saveDoctorsToFile(root, outfile);
            outfile.close();
        }
    }
};

// POS Menu
void posMenu(PatientList &patientList, AppointmentQueue &appointmentQueue, DoctorBST &doctorBST) {
    int choice;
    do {
        cout << "\n--- POS Menu ---" << endl;
        cout << "1. Add Patient" << endl;
        cout << "2. Display Doctors" << endl;
        cout << "3. Add Patient to Appointment Queue" << endl;
        cout << "4. Back to Main Menu" << endl;
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
                patientList.addPatient(id, name, age);
                break;
            }
            case 2: {
                cout << "Doctors List:" << endl;
                doctorBST.displayDoctors();
                break;
            }
            case 3: {
                int patientId;
                cout << "Enter Patient ID to add to appointment queue: ";
                cin >> patientId;
                appointmentQueue.addPatientToQueue(patientId);
                break;
            }
            case 4:
                cout << "Returning to Main Menu..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);
}

// Admin Menu
void adminMenu(PatientList &patientList, AppointmentQueue &appointmentQueue, DoctorBST &doctorBST) {
    int choice;
    do {
        cout << "\n--- Admin Menu ---" << endl;
        cout << "1. Add Doctor" << endl;
        cout << "2. Display Patients" << endl;
        cout << "3. Display Doctors" << endl;
        cout << "4. Process Appointments" << endl;
        cout << "5. Back to Main Menu" << endl;
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
                doctorBST.addDoctor(id, name, specialization);
                break;
            }
            case 2: {
                cout << "Patients List:" << endl;
                patientList.displayPatients();
                break;
            }
            case 3: {
                cout << "Doctors List:" << endl;
                doctorBST.displayDoctors();
                break;
            }
            case 4: {
                appointmentQueue.processNextPatient();
                break;
            }
            case 5:
                cout << "Returning to Main Menu..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);
}

// Main Function
int main() {
    PatientList patientList;
    AppointmentQueue appointmentQueue;
    DoctorBST doctorBST;

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
                posMenu(patientList, appointmentQueue, doctorBST);
                break;
            case 2:
                adminMenu(patientList, appointmentQueue, doctorBST);
                break;
            case 3:
                cout << "Exiting the system..." << endl;
                break;
            default:
                cout << "Invalid";
        }
        }while (userType !=3);
    return 0;
}
        
