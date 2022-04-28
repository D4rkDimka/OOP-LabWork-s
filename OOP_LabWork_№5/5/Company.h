#ifndef UNTITLED_COMPANY_H
#define UNTITLED_COMPANY_H

#include <iostream>
#include "WorkingObject.h"
#include <list>
#include <map>

using namespace std;

class Company {
public:
    list<WorkingObject> objects;

    void ViewCompanyMenu() {
        system("cls");
        cout    << endl
                << "1. Add new object" << endl
                << "2. View all objects" << endl
                << "3. Edit object" << endl
                << "4. Log object info into file" << endl
                << "5. Remove object" << endl
                << "6. Search object" << endl
                << "7. Sort objects" << endl
                << "8. Exit" << endl
                << "Your option: ";
        char ch; cin >> ch;

        if(ch == '1') AddObject();
        if(ch == '2') ViewObjects();
        if(ch == '3') EditObject();
        if(ch == '4') LogObject();
        if(ch == '5') RemoveObject();
        if(ch == '6') SearchObject();
        if(ch == '7') SortObjects();
        if(ch == '8') return;

        system("pause");
        ViewCompanyMenu();
    }

    void AddObject() {
        WorkingObject object;
        object.Input();

        objects.push_back(object);
    }

    void ViewObjects() {
        int i = 1;
        for(WorkingObject object : objects) {
            cout << i << ") " << object << endl;
            i++;
        }
    }

    void EditObject() {
        ViewObjects();

        cout    << endl
                << "Choose object you wanna edit(id): ";
        int id; cin >> id;

        auto iter = objects.begin();
        for (; iter != objects.end() && id != 1; iter++, id--);

        iter->Edit();
    }

    void RemoveObject() {
        ViewObjects();

        cout    << endl
                << "Choose object you wanna remove(id): ";
        int id; cin >> id;

        auto iter = objects.begin();
        for (; iter != objects.end() && id != 1; iter++, id--);

        objects.erase(iter);
    }

    void LogObject() {
        ViewObjects();

        cout    << endl
                << "Choose object you wanna log in file(id): ";
        int id; cin >> id;

        auto iter = objects.begin();
        for (; iter != objects.end() && id != 1; iter++, id--);

        iter->LogInFile();
    }

    void SearchObject() {
        cout    << endl
                << "1. By name" << endl
                << "2. By workers amount" << endl;
        char ch; cin >> ch;

        list<WorkingObject> result;

        cout << "Enter value: ";
        if(ch == '1') {
            string search_name; cin >> search_name;
            result = select([search_name](WorkingObject& obj){ return obj.objectName == search_name; });
        }
        if(ch == '2') {
            int search_amount; cin >> search_amount;
            result = select(([search_amount](WorkingObject& obj){ return obj.workers.size() == search_amount; }));
        }

        cout << "\nResult:\n";
        int i = 1;
        for(WorkingObject object : result) {
            cout << i << ") " << object << endl;
            i++;
        }
    }

    void SortObjects() {
        cout    << endl
                << "Sorting by age!" << endl;
        char ch;

        vector<WorkingObject> result;
        result = orderBy([](WorkingObject obj) { return obj.workers.size(); });

        cout    << endl
                << "1. By increase" << endl
                << "2. By decrease" << endl
                << "Choose option: ";
        cin >> ch;

        if(ch == '2') reverse(result.begin(), result.end());

        for(auto p : result)
            cout << "Name: " << p.objectName << ", Amount: " << p.workers.size() << endl;
    }

    template<typename F>
    list<WorkingObject> select(F transform) {
        list<WorkingObject> items;

        for(WorkingObject object : objects) {
            if(transform(object)) items.push_back(object);
        }

        return items;
    }

    template<typename F>
    vector<WorkingObject> orderBy(F predicate) {
        vector<WorkingObject> items;
        for(auto item : objects) items.push_back(item);

        auto dst = [predicate](WorkingObject& a, WorkingObject& b) { return predicate(a) < predicate(b); };
        std::sort(items.begin(), items.end(), dst);
        return items;
    }
};

#endif //UNTITLED_COMPANY_H
