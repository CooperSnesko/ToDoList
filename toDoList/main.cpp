//
//  main.cpp
//  ToDoList
//  Cooper Snesko
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


class Task {
public:
    int id;
    string description;
    bool completed;

    Task(int _id, const string& _description, bool _completed = false)
        : id(_id), description(_description), completed(_completed) {}
};


class TaskManager {
private:
    vector<Task> tasks;
    int nextId;
    const string filename;

public:
    TaskManager() : nextId(1), filename("tasks.txt") {
        loadFromFile();
    }

    ~TaskManager() {
        saveToFile();
    }

   
    void addTask(const string& description) {
        tasks.push_back(Task(nextId++, description, false));
        cout << "Task added.\n";
    }

   
    void removeTask(int id) {
        bool found = false;
        for (auto it = tasks.begin(); it != tasks.end(); ) {
            if (it->id == id) {
                it = tasks.erase(it);
                found = true;
                cout << "Task removed.\n";
            } else {
                ++it;
            }
        }
        if (!found)
            cout << "Task with ID " << id << " not found.\n";
    }

    
    void listTasks() const {
        if (tasks.empty()) {
            cout << "No tasks added.\n";
            return;
        }
        for (const auto& task : tasks) {
            cout << task.id << ": " << task.description;
            if (task.completed)
                cout << " [Completed]";
            cout << "\n";
        }
    }

    
    void saveToFile() {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Error opening file for writing.\n";
            return;
        }
        for (const auto& task : tasks) {
            
            outFile << task.id << "|" << task.description << "|" << task.completed << "\n";
        }
        outFile.close();
    }

   
    void loadFromFile() {
        ifstream inFile(filename);
        if (!inFile) {
           
            return;
        }
        tasks.clear();
        string line;
        while (getline(inFile, line)) {
            if (line.empty()) continue;
            istringstream iss(line);
            string idStr, desc, compStr;
            
            if (!getline(iss, idStr, '|') || !getline(iss, desc, '|') || !getline(iss, compStr, '|')) {
                
                continue;
            }
            int id = stoi(idStr);
            bool comp = (compStr == "1");
            tasks.push_back(Task(id, desc, comp));
            
           
            if (id >= nextId)
                nextId = id + 1;
        }
        inFile.close();
    }
};


void displayMenu() {
    cout << "\n=== To-Do List Manager ===\n";
    cout << "1. List tasks\n";
    cout << "2. Add task\n";
    cout << "3. Remove task\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    TaskManager manager;
    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();  

        if (choice == 1) {
            manager.listTasks();
        } else if (choice == 2) {
            cout << "Enter task description: ";
            string desc;
            getline(cin, desc);
            manager.addTask(desc);
        } else if (choice == 3) {
            cout << "Enter task ID to remove: ";
            int id;
            cin >> id;
            cin.ignore();
            manager.removeTask(id);
        } else if (choice == 4) {
            cout << "Exiting program. Tasks saved.\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
