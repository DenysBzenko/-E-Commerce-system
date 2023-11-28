#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <algorithm>

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

    double getPrice() const { return price; }

    int getProductID() const { return productID; }

    int getQuantityInStock() const { return quantityInStock; }

    void reduceQuantity(int quantity) {
        quantityInStock -= quantity;
    }
};

class Electronics : public Product {
public:
    Electronics(const std::string& name, double price, int quantity,
        const std::string& brand, const std::string& model, const std::string& additionalInfo)
        : Product(0, name, price, quantity), brand(brand), model(model), additionalInfo(additionalInfo) {}

    void displayProduct() const override {
        std::cout << "Product ID: " << getProductID() << ", Name: " << name
            << ", Price: " << getPrice() << ", Quantity: " << getQuantityInStock()
            << ", Brand: " << brand << ", Model: " << model << ", Additional Info: " << additionalInfo << std::endl;
    }

private:
    std::string brand;
    std::string model;
    std::string additionalInfo;
};

class Books : public Product {
public:
    Books(const std::string& name, double price, int quantity,
        const std::string& author, const std::string& genre, const std::string& isbn)
        : Product(0, name, price, quantity), author(author), genre(genre), isbn(isbn) {}

    void displayProduct() const override {
        std::cout << "Product ID: " << getProductID() << ", Name: " << name
            << ", Price: " << getPrice() << ", Quantity: " << getQuantityInStock()
            << ", Author: " << author << ", Genre: " << genre << ", ISBN: " << isbn << std::endl;
    }

private:
    std::string author;
    std::string genre;
    std::string isbn;
};

class Clothing : public Product {
public:
    Clothing(const std::string& name, double price, int quantity,
        const std::string& size, const std::string& color, const std::string& material)
        : Product(0, name, price, quantity), size(size), color(color), material(material) {}

    void displayProduct() const override {
        std::cout << "Product ID: " << getProductID() << ", Name: " << name
            << ", Price: " << getPrice() << ", Quantity: " << getQuantityInStock()
            << ", Size: " << size << ", Color: " << color << ", Material: " << material << std::endl;
    }

private:
    std::string size;
    std::string color;
    std::string material;
};

class Inventory {
private:
    std::vector<std::shared_ptr<Product>> products;

public:
    std::shared_ptr<Product> getProduct(int productID) {
        auto it = std::find_if(products.begin(), products.end(),
            [productID](const std::shared_ptr<Product>& product) {
                return product->getProductID() == productID;
            });

        return (it != products.end()) ? *it : nullptr;
    }

    void reduceStock(int productID, int quantity) {
        auto product = getProduct(productID);
        if (product) {
            int remainingQuantity = product->getQuantityInStock() - quantity;
            if (remainingQuantity >= 0) {
                product->reduceQuantity(quantity);
            }
            else {
                std::cout << "Insufficient stock available.\n";
            }
        }
    }
};

class ProductCatalog {
private:
    std::vector<std::shared_ptr<Product>> products;

public:
    void addProduct(const std::shared_ptr<Product>& product) {
        products.push_back(product);
    }

    void displayAllProducts() const {
        for (const auto& product : products) {
            product->displayProduct();
        }
    }
};

class ECommerceSystem {
private:
    ProductCatalog catalog;
    Inventory inventory;

public:
    void loadConfig(const std::string& configFile) {
        std::ifstream file(configFile);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open config file " << configFile << std::endl;
            return;
        }

        int productIDCounter = 1; // Додано лічильник для ідентифікації продуктів

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string type, name, priceStr, quantityStr;
            if (iss >> type >> name >> priceStr >> quantityStr) {
                double price = std::stod(priceStr);
                int quantity = std::stoi(quantityStr);

                if (type == "Electronics") {
                    std::string brand, model, additionalInfo;
                    if (iss >> brand >> model) {
                        std::getline(iss, additionalInfo);
                        catalog.addProduct(std::make_shared<Electronics>(name, price, quantity, brand, model, additionalInfo));
                    }
                }
                else if (type == "Books") {
                    std::string author, genre, isbn;
                    if (iss >> author >> genre >> isbn) {
                        catalog.addProduct(std::make_shared<Books>(name, price, quantity, author, genre, isbn));
                    }
                }
                else if (type == "Clothing") {
                    std::string size, color, material;
                    if (iss >> size >> color >> material) {
                        catalog.addProduct(std::make_shared<Clothing>(name, price, quantity, size, color, material));
                    }
                }
                else {
                    std::cerr << "Error: Unknown product type '" << type << "'. Skipped.\n";
                }
            }
            else {
                std::cerr << "Error: Invalid product format. Skipped.\n";
            }

            productIDCounter++;
        }
    }

    void displayProducts() {
        catalog.displayAllProducts();   
    }

    // Add other functionality as needed
};

int main() {
    ECommerceSystem system;
    system.loadConfig("config.txt");
    system.displayProducts();
    // Add other interactions as needed
    return 0;
}
