<h1>Hospital Management System </h1>

This project represents a simple Hospital Management System that manages patients, doctors, and appointments using data structures like **Linked Lists**, **Queues**, and **Binary Search Trees (BST)**. The system includes file handling to persist data across sessions and offers different menus for different types of users (POS and Admin).

<h2> Patient Management</h2><br>
<h3>Patient Node Structure</h3>
<img src="https://github.com/user-attachments/assets/8299ab89-a68a-4039-bc30-32a61707f833"><br><br>

- id: Unique identifier for the patient.
- name: Name of the patient.
- age: Age of the patient.
- next: Pointer to the next patient in the linked list.

<h3>Functions for Patient Management</h3>

 - addPatient: Adds a new patient to the linked list.
 - displayPatients: Displays all patients in the list.
 - loadPatientsFromFile: Loads patients' data from a file and populates the linked list.
 - savePatientsToFile: Saves the current patients' data to a file.

<h2>Appointment Management</h2>
<h3>Queue for Appointment Management</h3>

A queue is used to manage patients' appointments.
<h3>Functions for Appointment Management</h3>

- addPatientToQueue: Adds a patient's ID to the appointment queue.
- processNextPatient: Processes the next patient in the queue (removes them from the queue).
- showAppointmentList: Displays the IDs of all patients currently in the appointment queue.
- loadAppointmentsFromFile: Loads appointments' data from a file and populates the queue.
- saveAppointmentsToFile: Saves the current appointments' data to a file.

<h2>Doctor Management</h2>
<h3>Doctor Node Structure</h3>
<img src="https://github.com/user-attachments/assets/d03df059-44d7-46bc-ba2d-11ee30013468"><br><br>

* id: Unique identifier for the doctor.
* name: Name of the doctor.
* specialization: Specialization of the doctor.
* left: Pointer to the left child in the BST.
* right: Pointer to the right child in the BST.

<h3>Functions for Doctor Management</h3>

* insertDoctor: Inserts a new doctor into the BST.
* inorderTraversal: Performs an in-order traversal of the BST to display all doctors.
* searchDoctor: Searches for a doctor by name in the BST.
* deleteDoctor: Deletes a doctor by name from the BST.
* saveDoctorsToFile: Saves the current doctors' data to a file.
* loadDoctorsFromFile: Loads doctors' data from a file and populates the BST.

<h2>Menus</h2>
<h3>POS Menu</h3>

This menu is intended for point-of-sale (POS) users like receptionists who manage patient records and appointments.

    Options include:
        Adding patients
        Searching for doctors
        Displaying the patient list
        Adding patients to the appointment queue

Admin Menu

This menu is intended for administrative users who manage doctors and appointments.

    Options include:
        Adding doctors
        Displaying patients
        Displaying doctors
        Processing appointments
        Showing the appointment list
        Deleting doctors
