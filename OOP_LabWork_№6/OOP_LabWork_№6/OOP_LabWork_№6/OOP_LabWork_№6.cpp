#include<stack>
#include<queue>
#include<string>
#include <iostream>
using namespace std;

class Product
{
private:
    string nameOfProduct;
    int price;

public:
    Product():nameOfProduct("NULL"),price(0){}
    Product(string name, int price):nameOfProduct(name),price(price){}
    
    friend ostream& operator << (ostream& out, Product& product);

    friend bool operator< (const Product& firstOperand, const Product& secondOperand);

    friend bool operator> (const Product& firstOperand, const Product& secondOperand);

    void displayProductInfo()
    {
        cout << "Name of product: " << this->nameOfProduct << "\n\tPrice: " << this->price << endl;
    }

    void setNameOfProduct(string name) { this->nameOfProduct = name; }
    
    void setPriceOfProduct(int price) { this->price = price; }

    string getNameOfProduct() const { return this->nameOfProduct; }
    
    int getPriceOfProduct() const { return this->price; }
};

ostream& operator << (ostream& out, Product& product)
{
    product.displayProductInfo();
    return out;
}

bool operator < (const Product& firstOperand, const Product& secondOperand)
{
    return firstOperand.nameOfProduct > secondOperand.nameOfProduct;
}

bool operator > (const Product& firstOperand, const Product& secondOperand)
{
    return firstOperand.nameOfProduct < secondOperand.nameOfProduct;
}

class GoodsAccountingStack
{
private:
    stack<Product> goods;
public:

    void enterElementsIntoStack()
    {
        string nameOfProduct;
        int priceOfProduct;

        cout << "Enter name of product y,d like to add to stack" << endl;
        cout << ">> ";
        cin >> nameOfProduct;

        cout << "Enter price of product" << endl;
        cout << ">> ";
        priceOfProduct = getValue();

        goods.push(*new Product(nameOfProduct, priceOfProduct));

        CleareBuffer();
        
    }

    void displayStackElements()
    {
        stack<Product> tempGoods;
        int counterOfElements = 1;

        cout << "\tStack contents" << endl;
        
        while (!goods.empty())
        {
            cout << "["<< counterOfElements <<"] = "<< goods.top();
            tempGoods.push(goods.top());
            goods.pop();
            counterOfElements++;
            cout << endl;
        }

        goods = tempGoods;
    }

    void changeElementContent()
    {
        bool isFound = false;
        string userNameOfProduct;
        Product userProduct;
        stack<Product>tempGoods;

        cout << "Enter name of product y,d like to edit: ";
        getline(cin, userNameOfProduct);
        
        while (!goods.empty())
        {
            Product product = goods.top();
            userProduct = product;

            if (product.getNameOfProduct() == userNameOfProduct)
            {
                isFound = true;

                string nameOfProduct;
                int priceOfProduct;

                cout << "\nElement is found!\n";
                cout << "Enter name of product y,d like to add to stack" << endl;
                cout << ">> ";
                getline(cin, nameOfProduct);

                cout << "Enter price of product" << endl;
                cout << ">> ";
                priceOfProduct = getValue();

                userProduct.setNameOfProduct(nameOfProduct);
                userProduct.setPriceOfProduct(priceOfProduct);
            }

            tempGoods.push(userProduct);
            goods.pop();
        }
        if (isFound == false) cout << "\nThere is no element with such input!\n";

        goods = tempGoods;
    }

    int  getValue()
    {
        int userValue = 0;
        while (!(cin >> userValue) && cin.get() != '\n')
        {
            cout << "There is incorrect input, try again: ";
            cin.clear();
            cin.ignore();
            while (cin.get() != '\n');
        }

        return userValue;
    }

    void CleareBuffer()
    {
        if (char(cin.peek()) == '\n')
            cin.ignore();
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
        }
    }

    bool isEmpty()
    {
        if (goods.empty()) return true;
        else return false;
    }

    int  getSize()
    {
        return this->goods.size();
    }
};

class GoodsAccountingQueue
{
private:
    queue<Product> goods;
public:
    void enterElementsIntoQueue()
    {
        string nameOfProduct;
        int priceOfProduct;

        cout << "Enter name of product y,d like to add to stack" << endl;
        cout << ">> ";
        cin >> nameOfProduct;

        cout << "Enter price of product" << endl;
        cout << ">> ";
        priceOfProduct = getValue();

      
        goods.push(*new Product(nameOfProduct, priceOfProduct));

        CleareBuffer();
    }

    void displayQueueElements(int userChoice)
    {
        queue<Product> tempGoods;
        int counterOfElements = 1;

        switch (userChoice)
        {
        case 1:
            cout << "\tQueue contents(Start)" << endl;
            while (!goods.empty())
            {
                cout << "[" << counterOfElements << "] = " << goods.front();
                tempGoods.push(goods.front());
                counterOfElements++;
                goods.pop();
            }
            break;
        case 2:
            cout << "\tQueue contents(End)" << endl;
            while (!goods.empty())
            {
                cout << "[" << counterOfElements << "] = " << goods.back();
                tempGoods.push(goods.front());
                counterOfElements++;
                goods.pop();
            }
            break;
        default:
            cout << "\nThere is no cases with such input!\n";
            break;
        }
        
        goods = tempGoods;
    }

    void displayQueueElementsInCertainOrder()
    {
        int userChoice;
        
        cout << "Enter how to display queue:";
        cout << "\n(1) - Display from start"
            << "\n(2) = Display from end"
            << "\n\nYour choice>> ";
        
        switch (userChoice = getValue())
        {
        case 1:
            displayQueueElements(1);
            break;
        case 2:
            displayQueueElements(2);
            break;
        default:
            cout << "\nThere is no cases with such input!\n";
            break;
        }
    }

    void changeElementContent()
    {
        bool isFound = false;
        string userNameOfProduct;
        Product userProduct;
        queue<Product>tempGoods;
        CleareBuffer();

        cout << "Enter name of product y,d like to edit: ";
        getline(cin, userNameOfProduct);

        while (!goods.empty())
        {
            Product product = goods.front();
            userProduct = product;

            if (product.getNameOfProduct() == userNameOfProduct)
            {
                isFound = true;

                string nameOfProduct;
                int priceOfProduct;

                cout << "\nElement is found!\n";
                cout << "Enter name of product y,d like to add to stack" << endl;
                cout << ">> ";
                getline(cin, nameOfProduct);

                cout << "Enter price of product" << endl;
                cout << ">> ";
                priceOfProduct = getValue();

                userProduct.setNameOfProduct(nameOfProduct);
                userProduct.setPriceOfProduct(priceOfProduct);
            }

            tempGoods.push(userProduct);
            goods.pop();
        }
        if (isFound == false) cout << "\nThere is no element with such input!\n";

        goods = tempGoods;
    }

    int  getValue()
    {
        int userValue = 0;
        while (!(cin >> userValue) && cin.get() != '\n')
        {
            cout << "There is incorrect input, try again: ";
            cin.clear();
            cin.ignore();
            while (cin.get() != '\n');
        }

        return userValue;
    }

    void CleareBuffer()
    {
        if (char(cin.peek()) == '\n')
            cin.ignore();
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
        }
    }

    bool isEmpty()
    {
        if (goods.empty()) return true;
        else return false;
    }

    int  getSize()
    {
        return this->goods.size();
    }

};

class GoodsAccountingPriorityQueue
{
private:
    priority_queue<Product, vector<Product>, greater<vector<Product>::value_type >> goods;
public:
    void enterElementsIntoPriorityQueue()
    {
        string nameOfProduct;
        int priceOfProduct;

        cout << "Enter name of product y,d like to add to queue" << endl;
        cout << ">> ";
        cin>>nameOfProduct;

        cout << "Enter price of product" << endl;
        cout << ">> ";
        priceOfProduct = getValue();


        goods.push(*new Product(nameOfProduct, priceOfProduct));

        CleareBuffer();
    }

    void displayPriorityQueueElements()
    {
        priority_queue<Product, vector<Product>, greater<vector<Product>::value_type>> tempGoods;
        int counterOfElements = 1;

        cout << "\Priority queue contents" << endl;

        while (!goods.empty())
        {
            Product good = goods.top();
            cout <<"["<<counterOfElements<<"] = "<< good;
            counterOfElements++;
            tempGoods.push(good);
            goods.pop();
        }

        goods = tempGoods;
    }

    void changeElementContent()
    {
        bool isFound = false;
        string userNameOfProduct;
        Product userProduct;
        priority_queue<Product,vector<Product>,greater<vector<Product>::value_type>> tempGoods;

        cout << "Enter name of product y,d like to edit: ";
        getline(cin, userNameOfProduct);

        while (!goods.empty())
        {
            Product product = goods.top();
            userProduct = product;

            if (product.getNameOfProduct() == userNameOfProduct)
            {
                isFound = true;

                string nameOfProduct;
                int priceOfProduct;

                cout << "\nElement is found!\n";
                cout << "Enter name of product y,d like to add to stack" << endl;
                cout << ">> ";
                getline(cin, nameOfProduct);

                cout << "Enter price of product" << endl;
                cout << ">> ";
                priceOfProduct = getValue();

                userProduct.setNameOfProduct(nameOfProduct);
                userProduct.setPriceOfProduct(priceOfProduct);
            }

            tempGoods.push(userProduct);
            goods.pop();
        }
        if (isFound == false) cout << "\nThere is no element with such input!\n";

        goods = tempGoods;
    }

    int  getValue()
    {
        int userValue = 0;
        while (!(cin >> userValue) && cin.get() != '\n')
        {
            cout << "There is incorrect input, try again: ";
            cin.clear();
            cin.ignore();
            while (cin.get() != '\n');
        }

        return userValue;
    }

    void CleareBuffer()
    {
        if (char(cin.peek()) == '\n')
            cin.ignore();
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
        }
    }

    bool isEmpty()
    {
        if (goods.empty()) return true;
        else return false;
    }

    int  getSize()
    {
        return this->goods.size();
    }

};

void showMenu()
{
    cout << "\tMenu to work Adapter - containers"
        << "\n(1) - Work with stack"
        << "\n(2) - Work with queue"
        << "\n(3) - Work with priority queue"
        << "\n(0) - Exit"
        << "\n\nYour choice>> ";
}

void showOptionsOfMenu()
{
    cout << "(1) - Add new element to container"
        << "\n(2) - Display container"
        << "\n(3) - Change element"
        << "\n(0) - Exit"
        << "\n\nYour choice>> ";
}

int main()
{
    GoodsAccountingStack stack;
    GoodsAccountingQueue queue;
    GoodsAccountingPriorityQueue prQueue;
    bool isWorking = true;
    bool isWorkingStack = true;
    bool isWorkingQueue = true;
    bool isWorkingPrQueue = true;

    while (isWorking)
    {
        showMenu();
        int userChoice = stack.getValue();
        switch (userChoice)
        {
        case 1:
            isWorkingStack = true;

            while (isWorkingStack)
            {
                showOptionsOfMenu();
                userChoice = stack.getValue();

                switch (userChoice)
                {
                case 1:
                    stack.enterElementsIntoStack();
                    break;
                case 2:
                    if (stack.isEmpty() == false)
                    {
                        stack.displayStackElements();
                        cout << "\nAmount of element's - " << stack.getSize() << endl;
                    } 
                    else cout << "\nStack is empty!\n";
                    break;
                case 3:
                    if (stack.isEmpty() == false) stack.changeElementContent();
                    else cout << "\nStack is empty!\n";
                    break;
                case 0:
                    isWorkingStack = false;
                    break;
                default:
                    cout << "\nThere is no case with such input!\n";
                    break;
                }
                system("pause");
                system("cls");
            }
            break;
        case 2:
            isWorkingQueue = true;

            while (isWorkingQueue)
            {
                showOptionsOfMenu();
                userChoice = stack.getValue();

                switch (userChoice)
                {
                case 1:
                    queue.enterElementsIntoQueue();
                    break;
                case 2:
                    if (queue.isEmpty() == false) 
                    {
                        queue.displayQueueElementsInCertainOrder();
                        cout << "\nAmount of element's - " << stack.getSize() << endl;
                    }
                    else cout << "\nQueue is empty!\n";
                    break;
                case 3:
                    if (queue.isEmpty() == false) queue.changeElementContent();
                    else cout << "\nQueue is empty!\n";
                    break;
                default:
                    cout << "\nThere is no case with such input!\n";
                    break;
                case 0:
                    isWorkingQueue = false;
                    break;
                }
                system("pause");
                system("cls");

            }
            break;
        case 3:
            isWorkingPrQueue = true;

            while (isWorkingPrQueue)
            {
                showOptionsOfMenu();
                userChoice = stack.getValue();

                switch (userChoice)
                {
                case 1:
                    prQueue.enterElementsIntoPriorityQueue();
                    break;
                case 2:
                    if (prQueue.isEmpty() == false)
                    {
                        prQueue.displayPriorityQueueElements();
                        cout << "\nAmount of element's - " << stack.getSize() << endl;
                    }
                    else cout << "\nQueue is empty!\n";
                    break;
                case 3:
                    if (queue.isEmpty() == false) prQueue.changeElementContent();
                    else cout << "\nQueue is empty!\n";
                    break;
                case 0:
                    isWorkingPrQueue = false;
                    break;
                default:
                    cout << "\nThere is no case with such input!\n";
                    break;
                }
                system("pause");
                system("cls");

            }
            break;
        case 0:
            isWorking = false;
            break;
        default:
            cout << "\nThere is no case with such input!\n";
            break;
        }
        system("pause");
        system("cls");
    }
   
}

