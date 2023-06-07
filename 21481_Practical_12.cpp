//============================================================================
// Name        : DSA12_21481.cpp
// Author      : Atharva Khodke
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MAX_RECORDS = 100;

class Student {
    int rollNumber;
    char name[50];
    char address[100];

public:
    Student(){
        rollNumber=999;
        string n="default_name";
        string addr="default_address";
        strcpy(name,n.c_str());
        strcpy(address,addr.c_str());

    }
    void readData() {
        cout << "Enter Roll Number: ";
        cin >> rollNumber;
        cin.ignore(); // Ignore the newline character left by cin

        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Address: ";
        cin.getline(address, 100);
    }

    void displayData() {
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "---------------------" << endl;
    }

    int getRollNumber() const {
        return rollNumber;
    }
};

class StudentManagement {
    fstream file;
    fstream inputFile;

    int hashFunction(int rollNumber) {
        return rollNumber % MAX_RECORDS;
    }
public:
    StudentManagement(){
        file.open("students.bin", ios::binary | ios::app);
        Student student;
        for(int i=0;i<MAX_RECORDS;i++){
        file.seekp(hashFunction(i) * sizeof(Student), ios::beg);
        file.write(reinterpret_cast<char*>(&student), sizeof(Student));
        }
        file.close();
    }

    void addStudent() {
        file.open("students.bin", ios::binary | ios::out | ios::in);

        Student student;
        student.readData();

        int position = hashFunction(student.getRollNumber());
        
        file.seekp(position * sizeof(Student), ios::beg);
        // file.seekg(position * sizeof(Student), ios::beg);
        
        cout<<"positionbyhash "<<position<<"; sizeof Student : "<<sizeof(Student)<<" tellp at : "<<file.tellp()<<endl;
        cout<<"Data insertion from "<<file.tellp()<<endl;
        
        file.write(reinterpret_cast<char*>(&student), sizeof(Student));

        cout<<"Data inserted till "<<file.tellp()<<endl;
        
        file.close();

        cout << "Student added successfully!" << endl;
    }
    void findstudent(int roll){
        cout<<" Finding Student"<<endl;
        inputFile.open("students.bin", ios::binary | ios::in);
        int position = hashFunction(roll);
        inputFile.seekg(position * sizeof(Student), ios::beg);
        // inputFile.seekp(position * sizeof(Student), ios::beg); 
        cout<<"positionbyhash "<<position<<"; sizeof Student : "<<sizeof(Student)<<" tellp at : "<<(position * sizeof(Student))<<endl;

        cout<<"Data found at "<<inputFile.tellg()<<endl;

         Student student;
        inputFile.read(reinterpret_cast<char*>(&student), sizeof(Student));
        student.displayData();
        

        inputFile.close();
        cout<<"Student found!"<<endl;

    }
    void deleteStudent() {
        int rollNumber;
        cout << "Enter Roll Number of the student to delete: ";
        cin >> rollNumber;

        int position = hashFunction(rollNumber);

        inputFile.open("students.bin", ios::binary);
        if (!inputFile) {
            cout << "File not found!" << endl;
            return;
        }

        ofstream tempFile;
        tempFile.open("temp.bin", ios::binary);

        Student student;
        while (inputFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
            if (student.getRollNumber() != rollNumber) {
                tempFile.write(reinterpret_cast<char*>(&student), sizeof(Student));
            }
        }

        inputFile.close();
        tempFile.close();

        remove("students.bin");
        rename("temp.bin", "students.bin");

        cout << "Student deleted successfully!" << endl;
    }

    void displayStudents() {
        cout<<"\n-------------Displaying data-------------"<<endl;
        inputFile.open("students.bin", ios::binary|ios::in);
        if (!inputFile) {
            cout << "File not found!" << endl;
            return;
        }

        Student student;
        while (inputFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
            if(student.getRollNumber()!=999){
            cout<<" tellp at display: "<<inputFile.tellg()<<endl;

            student.displayData();
            }
        }

        inputFile.close();
        cout<<"\n-----------------------"<<endl;
    }

    void run() {
        int choice,roll;

        while (true) {
            cout << "Menu" << endl;
            cout << "1. Add Student" << endl;
            cout << "2. Delete Student" << endl;
            cout << "3. Display Students" << endl;
            cout << "4. Search" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addStudent();
                    break;
                case 2:
                    deleteStudent();
                    break;
                case 3:
                    displayStudents();
                    break;
                case 4:
                    cout<<"Enter Roll no to search ";
                    cin>>roll;
                    findstudent(roll);
                    break;
                case 5:
                    exit(0);

                default:
                    cout << "Invalid choice!" << endl;
            }

            cout << endl;
        }
    }
};

int main() {
    StudentManagement management;
    management.run();

    return 0;
}
