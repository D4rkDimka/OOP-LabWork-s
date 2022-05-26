#include "InputOperations.h"

int inputOperations::getValueInt()
{

    int userValue;

    while (!(cin >> userValue) && cin.get() != '\n')
    {
        cout << "Некорректный ввод данных, попробуйте еще раз: ";
        cin.clear();
        while (cin.get() != '\n');
    }

    return userValue;
}

void inputOperations::cleareBuffer()
{
    if (char(cin.peek()) == '\n')
        cin.ignore();
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(32767, '\n');
    }
}

bool inputOperations::getCorrectAnswer()
{
    string userInput;
    bool isFinded = true;
    bool isGiven = false;
    while (isFinded)
    {
        cin >> userInput;

        try
        {
            if (userInput == "Да" || userInput == "да" || userInput == "Д" || userInput == "д")
            {
                isFinded = false;
                isGiven = true;

            }
            else if (userInput == "Н" || userInput == "н" || userInput == "Нет" || userInput == "нет")
            {
                isFinded = false;
                isGiven = false;
            }
            else
            {
                throw runtime_error("Не корректный ввод данных!");
                cin.clear();
            }
        }
        catch (runtime_error exception)
        {
            cout << "Ошибка: " << exception.what() << "\nПопробуйте еще раз:";
        }
    }

    return isGiven;
}

string inputOperations::getValueStr()
{
    string userInput;
    cin >> userInput;
    return userInput;
}
