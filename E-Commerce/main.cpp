
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>

// Base class Product
class Product {
protected:
    int productID;
    std::string name;
    double price;
    int quantityInStock;

public:
    Product(int id, const std::string& name, double price, int quantity)
        : productID(id), name(name), price(price), quantityInStock(quantity) {}

    virtual void displayProduct() const {
        std::cout << "Product ID: " << productID << ", Name: " << name << ", Price: " << price << ", Quantity: " << quantityInStock << std::endl;
    }

    // Additional methods can be added here
};

// Derived class Electronics
class Electronics : public Product {
public:
    Electronics(int id, const std::string& name, double price, int quantity)
        : Product(id, name, price, quantity) {}

    void displayProduct() const override {
        std::cout << "Electronics - ";
        Product::displayProduct();
    }
};

// Derived class Books
class Books : public Product {
public:
    Books(int id, const std::string& name, double price, int quantity)
        : Product(id, name, price, quantity) {}

    void displayProduct() const override {
        std::cout << "Books - ";
        Product::displayProduct();
    }
};

// Derived class Clothing
class Clothing : public Product {
public:
    Clothing(int id, const std::string& name, double price, int quantity)
        : Product(id, name, price, quantity) {}

    void displayProduct() const override {
        std::cout << "Clothing - ";
        Product::displayProduct();
    }
};

// Function to read config file and initialize products
std::vector<std::shared_ptr<Product>> initializeProducts(const std::string& filename) {
    std::vector<std::shared_ptr<Product>> products;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; // Skip comments and empty lines

        std::istringstream iss(line);
        std::string type, name;
        int id, quantity;
        double price;

        iss >> type >> id >> name >> price >> quantity;
        if (type == "Electronics") {
            products.push_back(std::make_shared<Electronics>(id, name, price, quantity));
        }
        else if (type == "Books") {
            products.push_back(std::make_shared<Books>(id, name, price, quantity));
        }
        else if (type == "Clothing") {
            products.push_back(std::make_shared<Clothing>(id, name, price, quantity));
        }
    }

    return products;
}

// Main function
int main() {
    // Example initialization from a config file
    auto products = initializeProducts("products.txt");

    // Displaying initialized products
    for (auto& product : products) {
        product->displayProduct();
    }

    return 0;
}
