#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    long long id;
    string name;
    int age;
    string gender;
    string phone;
};

vector<Student> students;

void showAll() {
    if (students.empty()) {
        cout << "No students found.\n";
    } else {
        for (int i = 0; i < students.size(); i++) {
            cout << "ID: " << students[i].id << ", Name: " << students[i].name
                 << ", Age: " << students[i].age << ", Gender: " << students[i].gender
                 << ", Phone: " << students[i].phone << "\n";
        }
    }
}

void addStudent() {
    Student s;
    cout << "Enter ID: ";
    cin >> s.id;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Enter Age: ";
    cin >> s.age;
    cout << "Enter Gender: ";
    cin.ignore();
    getline(cin, s.gender);
    cout << "Enter Phone Number: ";
    getline(cin, s.phone);
    students.push_back(s);
    cout << "Student added successfully!\n";
}

void modifyStudent() {
    int id;
    cout << "Enter ID to modify: ";
    cin >> id;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].id == id) {
            cout << "Enter new Age: ";
            cin >> students[i].age;
            cout << "Enter new Gender: ";
            cin.ignore();
            getline(cin, students[i].gender);
            cout << "Enter new Phone Number: ";
            getline(cin, students[i].phone);
            cout << "Student information updated!\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

void deleteStudent() {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].id == id) {
            students.erase(students.begin() + i);
            cout << "Student deleted successfully!\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

int main() {
    int choice;
    while (true) {
        cout << "\n1. Show all information\n";
        cout << "2. Add a student's information\n";
        cout << "3. Modify the information of a student\n";
        cout << "4. Delete the information of a student\n";
        cout << "5. Quit the system\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) showAll();
        else if (choice == 2) addStudent();
        else if (choice == 3) modifyStudent();
        else if (choice == 4) deleteStudent();
        else if (choice == 5) break;
        else cout << "Invalid choice! Please try again.\n";
    }
    return 0;
}