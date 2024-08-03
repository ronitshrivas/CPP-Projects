#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Product
{
public:
    string name;
    int quantity;
    double price;

    Product() : name(""), quantity(0), price(0.0) {}
    Product(string n, int q, double p) : name(n), quantity(q), price(p) {}

    void display() const
    {
        cout << "Name: " << name << ", Quantity: " << quantity << ", Price: $" << price << endl;
    }
};

void addProduct(const Product &p)
{
    ofstream file("inventory.dat", ios::binary | ios::app);
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return;
    }
    file.write(reinterpret_cast<const char *>(&p), sizeof(Product));
    file.close();
}

vector<Product> loadProducts()
{
    vector<Product> products;
    ifstream file("inventory.dat", ios::binary);
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return products;
    }
    Product p;
    while (file.read(reinterpret_cast<char *>(&p), sizeof(Product)))
    {
        products.push_back(p);
    }
    file.close();
    return products;
}

int main()
{
    int choice;
    string name;
    int quantity;
    double price;

    while (true)
    {
        cout << "1. Add Product" << endl;
        cout << "2. Display Products" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "Enter product name: ";
            getline(cin, name);
            cout << "Enter quantity: ";
            cin >> quantity;
            cout << "Enter price: ";
            cin >> price;
            addProduct(Product(name, quantity, price));
            break;
        case 2:
            for (const auto &p : loadProducts())
            {
                p.display();
            }
            break;
        case 3:
            return 0;
        default:
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
