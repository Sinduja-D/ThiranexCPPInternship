#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class Student {
public:
    int id;
    string name;
    int age;
    string course;

    void input() {
        cout << "Enter Student ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();

        cout << "Enter Course: ";
        getline(cin, course);
    }

    void display() const {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(10) << age
             << setw(20) << course << endl;
    }
};

const string FILE_NAME = "students.txt";

// Add Student
void addStudent() {
    Student s;
    s.input();

    ofstream file(FILE_NAME, ios::app);
    file << s.id << "|"
         << s.name << "|"
         << s.age << "|"
         << s.course << endl;

    file.close();
    cout << "\nStudent record added successfully!\n";
}

// Load Students
vector<Student> loadStudents() {
    vector<Student> students;
    ifstream file(FILE_NAME);

    Student s;
    string line;

    while (getline(file, line)) {
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|", pos1 + 1);
        size_t pos3 = line.find("|", pos2 + 1);

        s.id = stoi(line.substr(0, pos1));
        s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        s.age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        s.course = line.substr(pos3 + 1);

        students.push_back(s);
    }

    file.close();
    return students;
}

// Display Students
void displayStudents() {
    vector<Student> students = loadStudents();

    if (students.empty()) {
        cout << "\nNo records found.\n";
        return;
    }

    cout << "\n-----------------------------------------------------------\n";
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(10) << "Age"
         << setw(20) << "Course" << endl;
    cout << "-----------------------------------------------------------\n";

    for (const auto &s : students)
        s.display();
}

// Search Student
void searchStudent() {
    int searchId;
    cout << "Enter Student ID to search: ";
    cin >> searchId;

    vector<Student> students = loadStudents();
    bool found = false;

    for (const auto &s : students) {
        if (s.id == searchId) {
            cout << "\nStudent Found:\n";
            s.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nStudent not found.\n";
}

// Update Student
void updateStudent() {
    int updateId;
    cout << "Enter Student ID to update: ";
    cin >> updateId;
    cin.ignore();

    vector<Student> students = loadStudents();
    bool found = false;

    for (auto &s : students) {
        if (s.id == updateId) {
            cout << "\nEnter New Details:\n";
            cout << "Name: ";
            getline(cin, s.name);

            cout << "Age: ";
            cin >> s.age;
            cin.ignore();

            cout << "Course: ";
            getline(cin, s.course);

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nStudent not found.\n";
        return;
    }

    ofstream file(FILE_NAME);

    for (const auto &s : students) {
        file << s.id << "|"
             << s.name << "|"
             << s.age << "|"
             << s.course << endl;
    }

    file.close();
    cout << "\nStudent record updated successfully!\n";
}

// Delete Student
void deleteStudent() {
    int deleteId;
    cout << "Enter Student ID to delete: ";
    cin >> deleteId;

    vector<Student> students = loadStudents();
    ofstream file(FILE_NAME);

    bool found = false;

    for (const auto &s : students) {
        if (s.id == deleteId) {
            found = true;
            continue;
        }

        file << s.id << "|"
             << s.name << "|"
             << s.age << "|"
             << s.course << endl;
    }

    file.close();

    if (found)
        cout << "\nStudent record deleted successfully!\n";
    else
        cout << "\nStudent not found.\n";
}

// Main Menu
int main() {
    int choice;

    do {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            updateStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 6:
            cout << "\nExiting program...\n";
            break;
        default:
            cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}