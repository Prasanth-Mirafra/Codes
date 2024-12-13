#include <iostream>
using namespace std;

class Queue {
private:
    int* arr;
    int front, rear, capacity, size;

public:
    Queue(int capacity) {
        this->capacity = capacity;
        arr = new int[capacity];
        front = 0;
        rear = -1;
        size = 0;
    }

    ~Queue() {
        delete[] arr;
    }

    void enqueue(int value) {
        if (size == capacity) {
            cout << "Queue Overflow\n";
            return;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = value;
        size++;
    }

    void dequeue() {
        if (size == 0) {
            cout << "Queue Underflow\n";
            return;
        }
        front = (front + 1) % capacity;
        size--;
    }

    int peek() {
        if (size == 0) {
            cout << "Queue is empty\n";
            return -1;
        }
        return arr[front];
    }

    bool isEmpty() {
        return size == 0;
    }

    void display() {
        if (size == 0) {
            cout << "Queue is empty\n";
            return;
        }
        for (int i = 0; i < size; i++) {
            cout << arr[(front + i) % capacity] << " ";
        }
        cout << endl;
    }
};

int main() {
    int size;
    cout << "Enter the size of the queue: ";
    cin >> size;

    Queue queue(size);
    int choice, value;

    do {
        cout << "Queue Operations\n";
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cout << "3. Peek\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to enqueue: ";
                cin >> value;
                queue.enqueue(value);
                break;

            case 2:
                queue.dequeue();
                break;

            case 3:
                cout << "Front element: " << queue.peek() << endl;
                break;

            case 4:
                queue.display();
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
