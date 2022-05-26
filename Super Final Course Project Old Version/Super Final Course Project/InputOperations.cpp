#include "InputOperations.h"

int inputOperations::getValueInt()
{

    int userValue;

    while (!(cin >> userValue) && cin.get() != '\n')
    {
        cout << "������������ ���� ������, ���������� ��� ���: ";
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
            if (userInput == "��" || userInput == "��" || userInput == "�" || userInput == "�")
            {
                isFinded = false;
                isGiven = true;

            }
            else if (userInput == "�" || userInput == "�" || userInput == "���" || userInput == "���")
            {
                isFinded = false;
                isGiven = false;
            }
            else
            {
                throw runtime_error("�� ���������� ���� ������!");
                cin.clear();
            }
        }
        catch (runtime_error exception)
        {
            cout << "������: " << exception.what() << "\n���������� ��� ���:";
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
