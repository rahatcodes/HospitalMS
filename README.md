# Hospital Management System

This project represents a simple Hospital Management System that manages patients, doctors, and appointments using data structures like **Linked Lists**, **Queues**, and **Binary Search Trees (BST)**. The system includes file handling to persist data across sessions and offers different menus for different types of users (POS and Admin).

## Patient Management<br>
### Patient Node Structure
<img src="https://github.com/user-attachments/assets/8299ab89-a68a-4039-bc30-32a61707f833"><br><br>

- id: Unique identifier for the patient.
- name: Name of the patient.
- age: Age of the patient.
- next: Pointer to the next patient in the linked list.

### Functions for Patient Management

 - addPatient: Adds a new patient to the linked list.
 - displayPatients: Displays all patients in the list.
 - loadPatientsFromFile: Loads patients' data from a file and populates the linked list.
 - savePatientsToFile: Saves the current patients' data to a file.

## Appointment Management
### Queue for Appointment Management

A queue is used to manage patients' appointments.
### Functions for Appointment Management

- addPatientToQueue: Adds a patient's ID to the appointment queue.
- processNextPatient: Processes the next patient in the queue (removes them from the queue).
- showAppointmentList: Displays the IDs of all patients currently in the appointment queue.
- loadAppointmentsFromFile: Loads appointments' data from a file and populates the queue.
- saveAppointmentsToFile: Saves the current appointments' data to a file.

## Doctor Management
### Doctor Node Structure
<img src="https://github.com/user-attachments/assets/d03df059-44d7-46bc-ba2d-11ee30013468"><br><br>

* id: Unique identifier for the doctor.
* name: Name of the doctor.
* specialization: Specialization of the doctor.
* left: Pointer to the left child in the BST.
* right: Pointer to the right child in the BST.

### Functions for Doctor Management

* insertDoctor: Inserts a new doctor into the BST.
* inorderTraversal: Performs an in-order traversal of the BST to display all doctors.
* searchDoctor: Searches for a doctor by name in the BST.
* deleteDoctor: Deletes a doctor by name from the BST.
* saveDoctorsToFile: Saves the current doctors' data to a file.
* loadDoctorsFromFile: Loads doctors' data from a file and populates the BST.

## Menus
### POS Menu

This menu is intended for point-of-sale (POS) users like receptionists who manage patient records and appointments.

**Options include:**

* Adding patients
* Searching for doctors
* Displaying the patient list
* Adding patients to the appointment queue

### Admin Menu

This menu is intended for administrative users who manage doctors and appointments.

**Options include:**

* Adding doctors
* Deleting doctors
* Displaying doctors
* Displaying patients
* Showing the appointment list
* Processing appointments
  
## Main Function
<img src="https://github.com/user-attachments/assets/57cdaaa6-c123-4ffb-8bb2-c20ee70870f7"><br>

* The main function initializes the system by loading data from files and then presents the user with a menu to select their role (POS or Admin) or to exit the system.
* Based on the user's choice, the corresponding menu is displayed, and the appropriate functions are called.
* When exiting, it saves the current state of patients, appointments, and doctors to their respective files.

## Summary

* Patients are managed using a linked list.
* Appointments are managed using a queue.
* Doctors are managed using a binary search tree (BST).
* The system includes file handling to persist data across sessions.
* Different menus are provided for different types of users (POS and Admin).

### Live Preview: <a href="https://replit.com/@rahatdev/Hospital-Management-System?v=1">REPLIT</a>
