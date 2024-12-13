#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class CircularLinkedList {
private:
    Node* tail;

public:
    CircularLinkedList() : tail(nullptr) {}

    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        if (!tail) {
            tail = newNode;
            tail->next = tail;
            return;
        }
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;
    }

    void insertAtHead(int value) {
        Node* newNode = new Node(value);
        if (!tail) {
            tail = newNode;
            tail->next = tail;
            return;
        }
        newNode->next = tail->next;
        tail->next = newNode;
    }

    void deleteByValue(int value) {
        if (!tail) return;

        Node* curr = tail->next;
        Node* prev = tail;

        do {
            if (curr->data == value) {
                if (curr == tail) {
                    if (curr->next == curr) {
                        delete curr;
                        tail = nullptr;
                        return;
                    }
                    tail = prev;
                }
                prev->next = curr->next;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        } while (curr != tail->next);
    }

    void display() {
        if (!tail) {
            cout << "List is empty\n";
            return;
        }
        Node* temp = tail->next;
        do {
            cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != tail->next);
        cout << "(back to head)\n";
    }
};

int main() {
    CircularLinkedList list;

    int choice, value;
    do {
        
        cout << "1. Insert at end\n";
        cout << "2. Insert at head\n";
        cout << "3. Delete by value\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert at end: ";
                cin >> value;
                list.insertAtEnd(value);
                break;

            case 2:
                cout << "Enter value to insert at head: ";
                cin >> value;
                list.insertAtHead(value);
                break;

            case 3:
                cout << "Enter value to delete: ";
                cin >> value;
                list.deleteByValue(value);
                break;

            case 4:
                list.display();
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
