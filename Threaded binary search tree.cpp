#include <iostream>
using namespace std;

struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;
    bool isThreaded;

    TreeNode(int val) : key(val), left(nullptr), right(nullptr), isThreaded(false) {}
};

TreeNode* insert(TreeNode* root, int key) {
    if (!root) return new TreeNode(key);

    TreeNode* curr = root;
    TreeNode* parent = nullptr;

    while (curr) {
        parent = curr;

        if (key < curr->key) {
            if (!curr->left) break;
            curr = curr->left;
        } else {
            if (curr->isThreaded || !curr->right) break;
            curr = curr->right;
        }
    }

    TreeNode* newNode = new TreeNode(key);
    if (key < parent->key) {
        parent->left = newNode;
        newNode->right = parent;
        newNode->isThreaded = true;
    } else {
        if (parent->isThreaded) {
            newNode->right = parent->right;
            newNode->isThreaded = true;
        }
        parent->right = newNode;
        parent->isThreaded = false;
    }

    return root;
}

void inOrderTraversal(TreeNode* root) {
    if (!root) return;

    TreeNode* curr = root;
    while (curr->left) curr = curr->left;

    while (curr) {
        cout << curr->key << " ";

        if (curr->isThreaded) {
            curr = curr->right;
        } else {
            curr = curr->right;
            while (curr && curr->left) curr = curr->left;
        }
    }
}

int main() {
    TreeNode* root = nullptr;
    int choice, value;

    do {
        cout << "Threaded Binary Search Tree Operations\n";
        cout << "1. Insert a node\n";
        cout << "2. Display in-order traversal\n";
        cout << "5. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the value to insert: ";
                cin >> value;
                root = insert(root, value);
                cout << "Value " << value << " inserted successfully.\n";
                break;

            case 2:
                cout << "In-order Traversal of Threaded BST: ";
                inOrderTraversal(root);
                cout << endl;
                break;

            case 5:
                cout << "Exiting the program\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
