#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Student
{
public:
    int id;
    string name;
    float gpa;

    Student() : id(0), name(""), gpa(0.0) {}
    Student(int i, string n, float g) : id(i), name(n), gpa(g) {}

    void display() const
    {
        cout << "ID: " << id << ", Name: " << name << ", GPA: " << gpa << endl;
    }
};

void addStudent(const Student &s)
{
    ofstream file("students.dat", ios::binary | ios::app);
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return;
    }
    file.write(reinterpret_cast<const char *>(&s), sizeof(Student));
    file.close();
}

vector<Student> loadStudents()
{
    vector<Student> students;
    ifstream file("students.dat", ios::binary);
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return students;
    }
    Student s;
    while (file.read(reinterpret_cast<char *>(&s), sizeof(Student)))
    {
        students.push_back(s);
    }
    file.close();
    return students;
}

int main()
{
    int choice;
    int id;
    string name;
    float gpa;

    while (true)
    {
        cout << "1. Add Student" << endl;
        cout << "2. Display Students" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "Enter student ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter student name: ";
            getline(cin, name);
            cout << "Enter GPA: ";
            cin >> gpa;
            addStudent(Student(id, name, gpa));
            break;
        case 2:
            for (const auto &s : loadStudents())
            {
                s.display();
            }
            break;
        case 3:
            return 0;
        default:
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
