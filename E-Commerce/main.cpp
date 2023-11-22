#include <iostream>
#include <vector>
#include <string>

class Product {
protected:
    std::string name;
    double price;

public:
    Product(std::string n, double p) : name(n), price(p) {}

    virtual void display() const {
        std::cout << "Name: " << name << ", Price: " << price << std::endl;
    }

};

class Electronics : public Product {
    
public:
    Electronics(std::string n, double p) : Product(n, p) {}

    void display() const override {
        Product::display();
       
    }
};

class Books : public Product {
   
public:
    Books(std::string n, double p) : Product(n, p) {}

    void display() const override {
        Product::display();
        
    }
};

class Clothing : public Product {
  
public:
    Clothing(std::string n, double p) : Product(n, p) {}

    void display() const override {
        Product::display();
       
    }
};


class ProductCatalog {
    std::vector<Product*> products;

public:
    void addProduct(Product* product) {
        products.push_back(product);
    }

    void displayCatalog() const {
        for (const auto& product : products) {
            product->display();
        }
    }

   
};

int main() {
    ProductCatalog catalog;

    catalog.addProduct(new Electronics("Smartphone", 999.99));
    catalog.addProduct(new Books("C++ Programming", 49.99));
    catalog.addProduct(new Clothing("T-Shirt", 19.99));

    catalog.displayCatalog();

    

    return 0;
}
