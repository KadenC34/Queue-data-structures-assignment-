
#include <iostream>
#include <queue>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// Stores information about each customer
struct Customer
{
    int customerID;
    string name;
    int numberOfItems;
    double totalCost;
};

// Gets a valid whole number from the user
int getNumber(string message)
{
    int number;

    while (true)
    {
        cout << message;
        cin >> number;

        if (!cin.fail() && number >= 0)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return number;
        }

        cout << "Please enter a valid positive number.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Adds a customer to the checkout line
void addCustomer(queue<Customer>& checkoutLine, int& nextID)
{
    Customer newCustomer;

    newCustomer.customerID = nextID++;

    cout << "\nEnter customer name: ";
    getline(cin, newCustomer.name);

    while (newCustomer.name.empty())
    {
        cout << "Name cannot be empty. Try again: ";
        getline(cin, newCustomer.name);
    }

    newCustomer.numberOfItems = getNumber("Enter number of grocery items: ");

    while (newCustomer.numberOfItems == 0)
    {
        cout << "A customer must have at least one item.\n";
        newCustomer.numberOfItems = getNumber("Enter number of grocery items: ");
    }

    cout << "Enter total cost of groceries: $";
    cin >> newCustomer.totalCost;

    while (cin.fail() || newCustomer.totalCost < 0)
    {
        cout << "Please enter a valid amount: $";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cin >> newCustomer.totalCost;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    checkoutLine.push(newCustomer);

    cout << "\n" << newCustomer.name
        << " has been added to the checkout line.\n";
}

// Displays everyone waiting in line
void displayLine(queue<Customer> checkoutLine)
{
    cout << "\n========== CHECKOUT LINE ==========\n";

    if (checkoutLine.empty())
    {
        cout << "There are currently no customers waiting.\n";
        return;
    }

    while (!checkoutLine.empty())
    {
        Customer currentCustomer = checkoutLine.front();

        cout << "Customer ID: " << currentCustomer.customerID << endl;
        cout << "Name: " << currentCustomer.name << endl;
        cout << "Items: " << currentCustomer.numberOfItems << endl;

        cout << "Total: $" << fixed << setprecision(2)
            << currentCustomer.totalCost << endl;

        cout << "-----------------------------------\n";

        checkoutLine.pop();
    }
}

// Checks out the customer at the front of the line
void checkoutCustomer(queue<Customer>& checkoutLine,
    int& customersServed, double& totalSales)
{
    if (checkoutLine.empty())
    {
        cout << "\nNobody is waiting to check out.\n";
        return;
    }

    Customer currentCustomer = checkoutLine.front();

    cout << "\n========== CHECKOUT ==========\n";
    cout << "Serving customer: " << currentCustomer.name << endl;
    cout << "Customer ID: " << currentCustomer.customerID << endl;
    cout << "Number of items: " << currentCustomer.numberOfItems << endl;

    cout << "Total bill: $" << fixed << setprecision(2)
        << currentCustomer.totalCost << endl;

    cout << "Payment received. Thank you for shopping!\n";

    totalSales += currentCustomer.totalCost;
    customersServed++;

    checkoutLine.pop();

    cout << "Customer has left the checkout line.\n";
}

// Displays information about the store
void displayStatistics(queue<Customer> checkoutLine,
    int customersServed, double totalSales)
{
    cout << "\n========== STORE STATISTICS ==========\n";

    cout << "Customers currently waiting: "
        << checkoutLine.size() << endl;

    cout << "Customers served: "
        << customersServed << endl;

    cout << "Total sales: $" << fixed << setprecision(2)
        << totalSales << endl;

    cout << "======================================\n";
}

int main()
{
    queue<Customer> checkoutLine;

    int choice;
    int nextID = 1;
    int customersServed = 0;

    double totalSales = 0.0;

    cout << "Welcome to the Grocery Store Simulation!\n";

    while (true)
    {
        cout << "\n====================================\n";
        cout << "          GROCERY STORE\n";
        cout << "====================================\n";

        cout << "1 - Add customer to checkout line\n";
        cout << "2 - Display checkout line\n";
        cout << "3 - Checkout next customer\n";
        cout << "4 - Display store statistics\n";
        cout << "0 - Close grocery store\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nPlease enter a valid menu option.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            addCustomer(checkoutLine, nextID);
            break;

        case 2:
            displayLine(checkoutLine);
            break;

        case 3:
            checkoutCustomer(checkoutLine,
                customersServed, totalSales);
            break;

        case 4:
            displayStatistics(checkoutLine,
                customersServed, totalSales);
            break;

        case 0:
            cout << "\nClosing grocery store...\n";
            cout << "Thank you for using the simulation!\n";
            return 0;

        default:
            cout << "\nThat is not a valid option. Try again.\n";
            break;
        }
    }

    return 0;
}
