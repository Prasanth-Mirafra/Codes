#include <iostream>
#include<bits/stdc++.h>
using namespace std;

class Product {
private:
    int id;
    string name;
    int price;
    string category;

public:
    Product(int id, const string &name, int price, const string &category)
        : id(id), name(name), price(price), category(category) {}

    int getId() const { return id; }
    string getName() const { return name; }
    int getPrice() const { return price; }
    string getCategory() const { return category; }

    void displayProduct() const {
        cout << "Product ID: " << id << ", Name: " << name << ", Price: $" << price 
             << ", Category: " << category << endl;
    }
};

class Customer {
private:
    int id;
    string name;
    string email;

public:
    Customer(int id, const string &name, const string &email)
        : id(id), name(name), email(email) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getEmail() const { return email; }

    void displayCustomer() const {
        cout << "Customer ID: " << id << ", Name: " << name << ", Email: " << email << endl;
    }
};

class Order {
private:
    int order_id;
    Customer customer;
    vector<Product> products;
    int totalAmount;

public:
    Order(int order_id, const Customer &customer)
        : order_id(order_id), customer(customer), totalAmount(0) {}

    void addProduct(const Product &product) {
        products.push_back(product);
        totalAmount += product.getPrice();
    }

    void displayOrder() const {
        cout << "Order ID: " << order_id << endl;
        customer.displayCustomer();
        cout << "Products in Order:" << endl;
        for (const auto &product : products) {
            product.displayProduct();
        }
        cout << "Total Amount: $" << totalAmount << endl;
    }

    int getTotalAmount() const { return totalAmount; }
};

class ShoppingCart {
private:
    vector<Order> orders;

public:
    void addOrder(const Order &order) {
        orders.push_back(order);
    }

    void displayCart() const {
        cout << "Shopping Cart Contents:" << endl;
        for (const auto &order : orders) {
            order.displayOrder();
            cout << "--------------------" << endl;
        }
    }
};

int main() {
    
    Product laptop(1, "Mobile", 1200, "Electric Accessories");
    Product shirt(2, "TShirt", 30, "Clothing");
    Product apple(3, "Apple", 1, "Food");

    
    Customer customer(1, "Prasanth Nallabariki", "prasanthnallabariki@mirafra.com");

    Order order1(1001, customer);
    order1.addProduct(laptop);
    order1.addProduct(shirt);
    order1.addProduct(apple);

    
    ShoppingCart cart;
    cart.addOrder(order1);

    
    cart.displayCart();

    return 0;
}
