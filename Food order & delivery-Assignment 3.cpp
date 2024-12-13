#include <bits/stdc++.h>

using namespace std;

struct ItemsMenu {
    string name;
    double price;
};

struct Restaurant {
    string name;
    string address;
    vector<ItemsMenu> menuItems;
    Restaurant* next;
};

struct Order {
    string customerName;
    string restaurantName;
    vector<string> items;
    double total;
    Order* next;
};

class RestaurantManage {
private:
    Restaurant* head;

public:
    RestaurantManage() : head(nullptr) {}

    void addRestaurant(const string& name, const string& address) {
        Restaurant* newRestaurant = new Restaurant{name, address, {}, nullptr};
        if (!head) {
            head = newRestaurant;
        } else {
            Restaurant* temp = head;
            while (temp->next){
                temp = temp->next;
            }
            temp->next = newRestaurant;
        }
    }

    void displayRestaurants() {
        if (!head) {
            cout << "No restaurants available.\n";
            return;
        }
        Restaurant* temp = head;
        while (temp) {
            cout << "Name: " << temp->name << ", Address: " << temp->address << "\n";
            temp = temp->next;
        }
    }

    void addMenuItem(const string& restaurantName, const string& itemName, double price) {
        Restaurant* temp = head;
        while (temp && temp->name != restaurantName) {
            temp = temp->next;
        }
        if (temp) {
            temp->menuItems.push_back({itemName, price});
        } else {
            cout << "Restaurant not found!\n";
        }
    }

    Restaurant* getRestaurantByName(const string& restaurantName) {
        Restaurant* temp = head;
        while (temp && temp->name != restaurantName) {
            temp = temp->next;
        }
        return temp;
    }
};

class OrderQueue {
private:
    Order* start;
    Order* end;

public:
    OrderQueue() : start(nullptr), end(nullptr) {}

    void placeOrder(const string& customerName, const string& restaurantName, 
                    const vector<string>& items, double total) {
        Order* newOrder = new Order{customerName, restaurantName, items, total, nullptr};
        if (!end) {
            start = end = newOrder;
            end->next = start;
        } else {
            end->next = newOrder;
            end = newOrder;
            end->next = start;
        }
    }

    void BillingOrder() {
        if (!start) {
            cout << "No orders to process.\n";
            return;
        }
        Order* temp = start;
        cout << "Processing order for: " << temp->customerName << "\n";
        cout << "Restaurant: " << temp->restaurantName << "\n";
        cout << "Items:\n";
        for (const auto& item : temp->items) {
            cout << "- " << item << "\n";
        }
        cout << "Total: $" << temp->total << "\n";

        if (start == end) {
            start = end = nullptr;
        } else {
            start = start->next;
            end->next = start;
        }
        delete temp;
    }
};

void placeOrderForRestaurant(RestaurantManage& rm, OrderQueue& oq, const string& restaurantName, 
                             const string& customerName, const vector<string>& itemNames) {
    Restaurant* restaurant = rm.getRestaurantByName(restaurantName);
    if (!restaurant) {
        cout << "Restaurant not found!\n";
        return;
    }

    double total = 0;
    for (const auto& itemName : itemNames) {
        bool itemFound = false;
    for (const auto& menuItem : restaurant->menuItems) {
        if (menuItem.name == itemName) {  
            total += menuItem.price;       
            itemFound = true;              
            break;                         
        }
    }
    if (!itemFound) {
        cout << "Item " << itemName << " not found in menu!\n"; 
    }
}


    if (total > 0) {
        oq.placeOrder(customerName, restaurantName, itemNames, total);
        cout << "Order placed successfully!\n";
    }
}

void displayMenuForRestaurant(RestaurantManage& rm, const string& restaurantName) {
    Restaurant* restaurant = rm.getRestaurantByName(restaurantName);
    if (!restaurant) {
        cout << "Restaurant not found!\n";
        return;
    }

    cout << "Menu for " << restaurant->name << ":\n";
    for (const auto& item : restaurant->menuItems) {
        cout << "- " << item.name << " ($" << item.price << ")\n";
    }
}

int main() {
    RestaurantManage rm;
    OrderQueue oq;

    int choice;
    do {
        cout << "\n--- Food Ordering and Delivery System ---\n";
        cout << "1. Add Restaurant\n";
        cout << "2. Display Restaurants\n";
        cout << "3. Add Menu Item\n";
        cout << "4. Display Menu\n";
        cout << "5. Place Order\n";
        cout << "6. Process Next Order\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, address;
                cout << "Enter restaurant name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter restaurant address: ";
                getline(cin, address);
                rm.addRestaurant(name, address);
                break;
            }
            case 2:
                rm.displayRestaurants();
                break;
            case 3: {
                string restaurantName;
                cout << "Enter restaurant name: ";
                cin.ignore();
                getline(cin, restaurantName);
            
                int itemCount;
                cout << "Enter the number of items to add: ";
                cin >> itemCount;
                cin.ignore();
            
                for (int i = 0; i < itemCount; ++i) {
                    string itemName;
                    double price;
            
                    cout << "Enter name of item " << i + 1 << ": ";
                    getline(cin, itemName);
                    cout << "Enter price of item " << i + 1 << ": ";
                    cin >> price;
                    cin.ignore();
            
                    rm.addMenuItem(restaurantName, itemName, price);
                }
            
                cout << "Menu items added successfully!\n";
                break;
            }
            case 4: {
                string restaurantName;
                cout << "Enter restaurant name: ";
                cin.ignore();
                getline(cin, restaurantName);
                displayMenuForRestaurant(rm, restaurantName);
                break;
            }
            case 5: {
                string restaurantName, customerName;
                int itemCount;
                vector<string> itemNames;

                cout << "Enter restaurant name: ";
                cin.ignore();
                getline(cin, restaurantName);
                cout << "Enter customer name: ";
                getline(cin, customerName);
                cout << "Enter number of items: ";
                cin >> itemCount;
                cin.ignore();

                for (int i = 0; i < itemCount; ++i) {
                    string itemName;
                    cout << "Enter item " << i + 1 << ": ";
                    getline(cin, itemName);
                    itemNames.push_back(itemName);
                }

                placeOrderForRestaurant(rm, oq, restaurantName, customerName, itemNames);
                break;
            }
            case 6:
                oq.BillingOrder();
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 7);

    return 0;
}
