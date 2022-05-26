#pragma once
#include<iostream>
#include<fstream>
#include<memory>
#include<string>
#include<vector>
#include"InputOperations.h"
using namespace std;

template<class T>
class FileOperations
{
private:
    string fileName;
    shared_ptr <T> buffer;
public:
    FileOperations() {}
    FileOperations(string fileName) :fileName(fileName) {}
    string enterFileName();

    void writeInformationFile(string fileStr);

    string getFileName() const;

    void writeInFile(vector<shared_ptr<T>> vector,string fileName);

    void readFromFile(vector<shared_ptr<T>> vector);

    int getFileSize(string userFileName);
};

template<class T>
inline string FileOperations<T>::enterFileName()
{
    cin.ignore(100, '\n');

    cout << "Пожалуйста,введите имя файла: ";
    getline(cin, fileName);
    fileName += ".txt";
    return fileName;
}

template<class T>
inline void FileOperations<T>::writeInformationFile(string fileStr)
{
    ofstream fout;
    int userChoice;
    string fileName = "InformationFile.txt";
    int sizeOfFile = getFileSize(fileName);

    if (sizeOfFile == 0)
    {
        fout.open(fileName, ios_base::trunc);

        try
        {
            if (fout.is_open() == false || fout.bad() == true) throw runtime_error
            ("Файл не может быть открыт или появились критическеи ошибки открытии!");
        }
        catch (runtime_error exception)
        {
            cout << "Ошибка: " << exception.what() << endl;
        }

        fout << "[" << fileStr << "]" << endl << endl;

        fout.close();
    }
    else
    {
        fout.open(fileName, ios_base::app );

        try
        {
            if (fout.is_open() == false || fout.bad() == true) throw runtime_error
            ("Файл не может быть открыт или появились критическеи ошибки открытии!");
        }
        catch (runtime_error exception)
        {
            cout << "Ошибка: " << exception.what() << endl;
        }

        fout << "[" << fileStr << "]" << endl << endl;
       
        fout.close();
    }

}

template<class T>
inline string FileOperations<T>::getFileName() const
{
    return fileName;
}

template<class T>
inline void FileOperations<T>::writeInFile(vector<shared_ptr<T>> vector, string fileName)
{
    ofstream fout;
    int userChoice;
    bool isWorking = true;
    int sizeOfFile = getFileSize(fileName);

    if (sizeOfFile == 0)
    {
        fout.open(fileName, ios_base::trunc | ios::binary);

        try
        {
            if (fout.is_open() == false || fout.bad() == true) throw runtime_error
            ("Файл не может быть открыт или появились критическеи ошибки открытии!");
        }
        catch (runtime_error exception)
        {
            cout << "Ошибка: " << exception.what() << endl;
        }

        for (int i = 0; i < vector.size(); i++)
        {
            buffer = vector[i];
            fout.write(reinterpret_cast<char*>(&buffer), sizeof T);
        }

        fout.close();
    }
    else
    {
        fout.open(fileName, ios_base::app || ios::binary);

        try
        {
            if (fout.is_open() == false || fout.bad() == true) throw runtime_error
            ("Файл не может быть открыт или появились критическеи ошибки открытии!");
        }
        catch (runtime_error exception)
        {
            cout << "Ошибка: " << exception.what() << endl;
        }

        for (int i = 0; i < vector.size(); i++)
        {
            buffer = vector[i];
            fout.write(reinterpret_cast<char*>(&buffer), sizeof T);
        }

        fout.close();
    }
}

template<class T>
inline void FileOperations<T>::readFromFile(vector<shared_ptr<T>> vector)
{
    ifstream fin;
    bool isWorking = true;

    fileName = enterFileName();

    fin.open(fileName, ios_base::in | ios::binary);

    try
    {
        if (fin.is_open() == false || fin.bad() == true) throw runtime_error("Файл не может быть открыт или не существует!");
    }
    catch (runtime_error exception)
    {
        cout << "Ошибка: " << exception.what() << endl;
        return;
    }

    auto ptr = vector.begin();
    fin.seekg(0, ios::end);
    int size = fin.tellg() / sizeof(T);
    fin.seekg(0);

    for (int i = 0; i < vector.size(); i++)
    {
        fin.read(reinterpret_cast<char*>(&buffer), sizeof(T));
        cout << buffer << endl;
    }

    fin.close();
    cout << "\nВся информация из файла была успешно считана!\n";
}

template<class T>
inline int FileOperations<T>::getFileSize(string userFileName)
{
    ifstream fin(userFileName, ios::in);
    int fileSize = 0;
    fin.seekg(0, ios::end);
    fileSize = fin.tellg();
    fin.close();

    return fileSize;
}
