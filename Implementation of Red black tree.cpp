#include <iostream>
#include<bits/stdc++.h>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    bool color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int value) : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;
    Node* TNULL;

    void initializeTNULL() {
        TNULL = new Node(0);
        TNULL->color = BLACK;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
    }

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != TNULL) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nullptr) {
            root = x;
        } else if (y == y->parent->right) {
            y->parent->right = x;
        } else {
            y->parent->left = x;
        }
        x->right = y;
        y->parent = x;
    }

    void fixInsert(Node* k) {
        while (k->parent->color == RED) {
            if (k->parent == k->parent->parent->left) {
                Node* uncle = k->parent->parent->right;
                if (uncle->color == RED) {
                    k->parent->color = BLACK;
                    uncle->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            } else {
                Node* uncle = k->parent->parent->left;
                if (uncle->color == RED) {
                    k->parent->color = BLACK;
                    uncle->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void inOrderHelper(Node* node) {
        if (node != TNULL) {
            inOrderHelper(node->left);
            cout << node->data << " ";
            inOrderHelper(node->right);
        }
    }

public:
    RedBlackTree() {
        initializeTNULL();
        root = TNULL;
    }

    void insert(int key) {
        Node* newNode = new Node(key);
        newNode->parent = nullptr;
        newNode->left = TNULL;
        newNode->right = TNULL;

        Node* y = nullptr;
        Node* x = root;

        while (x != TNULL) {
            y = x;
            if (newNode->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        newNode->parent = y;
        if (y == nullptr) {
            root = newNode;
        } else if (newNode->data < y->data) {
            y->left = newNode;
        } else {
            y->right = newNode;
        }

        if (newNode->parent == nullptr) {
            newNode->color = BLACK;
            return;
        }

        if (newNode->parent->parent == nullptr) {
            return;
        }

        fixInsert(newNode);
    }

    void display() {
        cout << "In-order Traversal: ";
        inOrderHelper(root);
        cout << endl;
    }
};

int main() {
    RedBlackTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);

    tree.display();

    return 0;
}
