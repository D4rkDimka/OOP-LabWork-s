#ifndef UNTITLED_WORKINGOBJECT_H
#define UNTITLED_WORKINGOBJECT_H

#include <iostream>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

class WorkingObject {
public:
    string objectName;
    map<string, int> workers;

    void Input() {
        cout << "Enter object name: ";
        cin >> objectName;
    }

    void ViewObjectMenu() {
        system("cls");
        cout    << endl
                << "1. Add new worker" << endl
                << "2. View all workers" << endl
                << "3. Edit worker" << endl
                << "4. Remove worker" << endl
                << "5. Search worker" << endl
                << "6. Sort workers" << endl
                << "7. Back" << endl
                << "Your option: ";
        char ch; cin >> ch;

        if(ch == '1') AddWorker();
        if(ch == '2') ViewWorkers();
        if(ch == '3') EditWorker();
        if(ch == '4') RemoveWorker();
        if(ch == '5') SearchWorker();
        if(ch == '6') SortWorkers();
        if(ch == '7') return;

        system("pause");
        ViewObjectMenu();
    }

    void AddWorker() {
        int age; string name;
        cout << "Enter worker name:";
        cin >> name;
        cout << "Enter worker age: ";
        cin >> age;

        workers.insert(pair<string, int>(name, age));
    }

    void ViewWorkers() {
        map<string, int>::iterator it = workers.begin();
        for(int i = 1; it != workers.end(); i++, it++)
            cout << i << ") " << it->first << ", " << it->second << endl;
    }

    void EditWorker() {
        ViewWorkers();

        cout    << endl
                << "Choose worker you wanna edit(name): ";
        string name; cin >> name;

        cout    << endl
                << "1. Name" << endl
                << "2. Age" << endl
                << "What do you wanna edit: ";
        char ch; cin >> ch;

        if(ch == '1') {
            pair<string, int> p;
            auto it = workers.find(name);
            if(it != workers.end()) {
                p.second = it->second;
                workers.erase(it);
                cout << "Enter new name: ";
                cin >> p.first;
                workers.insert(p);
            }
        }
        if(ch == '2') {
            auto it = workers.find(name);
            if(it != workers.end()) {
                cout << "Enter new age: ";
                cin >> it->second;
            }
        }
    }

    void RemoveWorker() {
        ViewWorkers();

        cout    << endl
                << "Choose worker you wanna edit(name): ";
        string name; cin >> name;

        auto it = workers.find(name);
        if(it != workers.end())
            workers.erase(it);
    }

    void SortWorkers() {
        cout    << endl
                << "1. By name" << endl
                << "2. By age" << endl
                << "Choose option: ";
        char ch; cin >> ch;

        vector<pair<string, int>> result;
        if(ch == '1')
            result = orderBy([](pair<string, int>& obj) { return obj.first; });
        if(ch == '2')
            result = orderBy([](pair<string, int>& obj) { return obj.second; });

        cout    << endl
                << "1. By increase" << endl
                << "2. By decrease" << endl
                << "Choose option: ";
        cin >> ch;

        if(ch == '2') reverse(result.begin(), result.end());

        for(auto p : result)
            cout << "Name: " << p.first << ", Age: " << p.second << endl;
    }

    void LogInFile() {
        fstream file;

        string pathBase = "../";
        string pathInfo = objectName;
        string fileType = ".txt";
        string result = pathBase + pathInfo + fileType;

        file.open(result.data(), ios::out | ios::app);

        if(file.is_open()) {

            file << "Workers: " << endl;

            auto it = workers.begin();
            for(int i = 1; it != workers.end(); i++, it++)
                file << i << ") " << it->first << ", " << it->second << endl;

            file.close();
        }
    }

    friend ostream&operator<<(ostream& stream, WorkingObject& obj) {
        stream << obj.objectName << ", workers: " << obj.workers.size();
        return stream;
    }

    void Edit() {
        cout    << endl
                << "1. Edit object name" << endl
                << "2. Edit object content" << endl
                << "Your choose: ";
        char ch; cin >> ch;

        if(ch == '1') Input();
        if(ch == '2') ViewObjectMenu();
    }

    void SearchWorker() {
        cout << "Enter name: ";
        string search_name; cin >> search_name;

        auto it = workers.find(search_name);
        if(it != workers.end())
            cout << "Name: " << it->first << "\nAge: " << it->second << endl;
    }

    template<typename F>
    vector<pair<string, int>> orderBy(F predicate) {
        vector<pair<string, int>> items;
        for(auto& it : workers) items.push_back(it);

        auto dst = [predicate](pair<string, int>& a, pair<string, int>& b) { return predicate(a) < predicate(b); };
        std::sort(items.begin(), items.end(), dst);
        return items;
    }
};

#endif //UNTITLED_WORKINGOBJECT_H
