#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Product {
    string name;
    float price;
    int quantity;
};

// TODO: Declare all function prototypes
void displayMenu();
void viewInventory(const vector<Product>&);
void addProduct(vector<Product>&);
void removeProduct(vector<Product>&);
void restockProduct(vector<Product>&);
void handlePurchase(vector<Product>&, float* storeBalance);
void endOfDayReport(const vector<Product>&, float storeBalance);

int main() {
    // TODO: Declare variables for manager name, store name, and store balance
    // TODO: Get input and print welcome message
    string Mname;
    string Sname;
    float Obalance;
    cout << "Welcome to market manager pro!" << endl;
    cout << "Enter manager name: " << endl;
    cin >> Mname;
    cout << "Enter store name: " << endl;
    cin >> Sname;
    cout << "Enter opening balance: " << endl;
    cin >> Obalance;
    cout << endl;
    cout << Mname << ", welcome to " << Sname << "!" << endl;

    // TODO: Initialize vector<Product> with some starting items
    vector <Product> products;
    products.push_back({"Apples", 2.00, 20});
    products.push_back({"Milk", 1.25, 25});
    products.push_back({"Bread", 1.00, 30});

    srand(time(0));
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
            viewInventory(products);
            break;
            case 2: 
            addProduct(products);
            break;
            case 3:
            removeProduct(products);
            break;
            case 4:
            restockProduct(products);
            break;
            case 5:
            handlePurchase(products, &Obalance);
            break;
            case 6:
            endOfDayReport(products, Obalance);
            break;
            case 7:
            cout << "Exiting " << Sname << " have a great day, " << Mname;
            break;
            default:
            cout << "Invalid choice... try again";
            break;
            
        }

    } while (choice != 7);

    return 0;
}

// TODO: Implement all the following functions step by step:
// 1. displayMenu()
void displayMenu(){
    cout << "MAIN MENU" << endl;
    cout << "1. View inventory" << endl;
    cout << "2. Add product" << endl;
    cout << "3. Remove product" << endl;
    cout << "4. Restock product" << endl;
    cout << "5. Handle purchase" << endl;
    cout << "6. End the day and see the report" << endl;
    cout << "7. Exit" << endl;
}

// 2. viewInventory()
void viewInventory(const vector<Product>& products){
    for (int i = 0; i < products.size(); ++i){
        cout << products[i].name << "-Price $" << products[i].price << "-Quantity: " << products[i].quantity << endl;
        if (products[i].quantity < 5){
            cout << products[i].name << " is low on stock" << endl;
        }
    }
    cout << "Starting from the top the input is 1" << endl;
}
// 3. addProduct()
void addProduct(vector<Product>& products){
    Product a;
    cout << "Enter name of product: ";
    cin >> a.name;
    cout << "Enter the price of the product: ";
    cin >> a.price;
    cout << "Enter the quantity of the product: ";
    cin >> a.quantity;
    products.push_back(a);
    cout << "The product " << a.name << " has been added." << endl;
}
// 4. removeProduct()
void removeProduct(vector<Product>& products){
    viewInventory(products);
    cout << "Enter the product you want to remove." << endl;
    int choice;
    cin >> choice;
    cin.ignore();
    cout << products[choice - 1].name << " has been removed." << endl;
    products.erase(products.begin() + (choice - 1));
}
// 5. restockProduct()
void restockProduct(vector<Product>& products){
    viewInventory(products);
    cout << "Enter the product you want to restock." << endl;
    int choice;
    cin >> choice;
    cin.ignore();
    products[choice - 1].quantity += 10;
    cout << products[choice - 1].name << " has been restocked." << endl;
}
// 6. handlePurchase()
void handlePurchase(vector<Product>& products, float* storeBalance){
    float totalcost = 0.0;
    char more = 'y';
    while (more == 'y'){
    viewInventory(products);
    cout << "What products would you like to purchase?" << endl;
    int choice;
    cin >> choice;
    cin.ignore();
    cout << "How much would you like to buy?" << endl;
    int qty;
    cin >> qty;
    if (products[choice - 1].quantity >= qty){
        float cost = products[choice - 1].price * qty;
        products[choice - 1].quantity -= qty;
        totalcost += cost;
    } else { 
        cout << "Not enough stock available." << endl;
    }
    cout << "Would you like to purchase a another item (y/n)" << endl;
    cin >> more;
    }
    if (totalcost > 100){
        float discount = totalcost * 0.10;
        totalcost -= discount;
        cout << "Discount applied " << discount << " 10%" << endl;
    }
    cout << "Total cost $" << totalcost << endl;
    cout << "Thank you for shopping with us" << endl;
    *storeBalance += totalcost;
    if (*storeBalance < 100)
        cout << "Warning funds are getting low" << endl;
}
// 7. endOfDayReport()
void endOfDayReport(const vector<Product>& products, float storeBalance){
    cout << "End of day report" << endl;
    cout << "Products - sales - quantity" << endl;
    int n = products.size();
    int sales[50];
    float totalRev = 0.0;
    for (int i = 0; i < n; ++i){
        sales[i] = rand() % 8;
        if (sales[i] > products[i].quantity) sales[i] = products[i].quantity;
        int remaining = products[i].quantity - sales[i];
        float revenue = sales[i] * products[i].price;
        totalRev += revenue;
        cout << products[i].name << " - " << sales[i] << " - " << remaining << endl;
    }
    cout << "Total revenue: $" << totalRev << endl;
    cout << "Store balance: $" << storeBalance + totalRev << endl;
}
