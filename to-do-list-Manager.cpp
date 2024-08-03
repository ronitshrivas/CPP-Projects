#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void displayMenu()
{
    cout << "1. Add Task" << endl;
    cout << "2. Display Tasks" << endl;
    cout << "3. Delete Task" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter choice: ";
}

void addTask(const string &task)
{
    ofstream file("tasks.txt", ios::app);
    if (file.is_open())
    {
        file << task << endl;
        file.close();
    }
    else
    {
        cout << "Unable to open file!" << endl;
    }
}

void displayTasks()
{
    ifstream file("tasks.txt");
    string line;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            cout << line << endl;
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file!" << endl;
    }
}

void deleteTask(const string &task)
{
    vector<string> tasks;
    ifstream file("tasks.txt");
    string line;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line != task)
            {
                tasks.push_back(line);
            }
        }
        file.close();
    }

    ofstream outFile("tasks.txt");
    if (outFile.is_open())
    {
        for (const auto &t : tasks)
        {
            outFile << t << endl;
        }
        outFile.close();
    }
    else
    {
        cout << "Unable to open file!" << endl;
    }
}

int main()
{
    int choice;
    string task;

    while (true)
    {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "Enter task to add: ";
            getline(cin, task);
            addTask(task);
            break;
        case 2:
            displayTasks();
            break;
        case 3:
            cout << "Enter task to delete: ";
            getline(cin, task);
            deleteTask(task);
            break;
        case 4:
            return 0;
        default:
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
