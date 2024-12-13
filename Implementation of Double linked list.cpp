#include <iostream>
#include<bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void insertAtHead(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        if (!tail) {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    void deleteByValue(int value) {
        if (!head) return;

        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            if (head) head->prev = nullptr;
            else tail = nullptr;
            delete temp;
            return;
        }

        Node* temp = head;
        while (temp && temp->data != value) {
            temp = temp->next;
        }

        if (temp) {
            temp->prev->next = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            else tail = temp->prev;
            delete temp;
        }
    }

    void displayForward() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    void displayBackward() {
        Node* temp = tail;
        while (temp) {
            cout << temp->data << " <-> ";
            temp = temp->prev;
        }
        cout << "NULL\n";
    }
};

int main() {
    DoublyLinkedList list;

    int choice, value;
    do {
        
        cout << "1. Insert at head\n";
        cout << "2. Insert at end\n";
        cout << "3. Delete by value\n";
        cout << "4. Display forward\n";
        cout << "5. Display backward\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert at head: ";
                cin >> value;
                list.insertAtHead(value);
                break;

            case 2:
                cout << "Enter value to insert at end: ";
                cin >> value;
                list.insertAtEnd(value);
                break;

            case 3:
                cout << "Enter value to delete: ";
                cin >> value;
                list.deleteByValue(value);
                break;

            case 4:
                list.displayForward();
                break;

            case 5:
                list.displayBackward();
                break;

            case 6:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
