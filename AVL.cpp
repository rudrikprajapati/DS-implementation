#include <bits/stdc++.h>
using namespace std;

class AVL {
private:
    class Node {
    public:
        int data;
        int height;
        Node* left;
        Node* right;

        Node(int value) : data(value), left(NULL), right(NULL), height(1) {}
    };

    Node* root;

    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* insertNode(Node* node, int value);
    Node* findMinValueNode(Node* node);
    Node* deleteNode(Node* node, int value);
    void inOrderTraversal(Node* node);

public:
    AVL() : root(NULL) {}

    void insert(int value);
    void remove(int value);
    bool search(int value);
    void printInorder();
};

int AVL::getHeight(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int AVL::getBalanceFactor(Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

AVL::Node* AVL::rotateRight(Node* y) {
    Node* x = y->left;
    Node* t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

AVL::Node* AVL::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

AVL::Node* AVL::insertNode(Node* node, int value) {
    if (node == NULL)
        return new Node(value);

    if (value < node->data)
        node->left = insertNode(node->left, value);
    else if (value > node->data)
        node->right = insertNode(node->right, value);
    else
        return node;  // Duplicates are not allowed

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalanceFactor(node);

    // Left Left Case
    if (balance > 1 && value < node->left->data)
        return rotateRight(node);

    // Right Right Case
    if (balance < -1 && value > node->right->data)
        return rotateLeft(node);

    // Left Right Case
    if (balance > 1 && value > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && value < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

AVL::Node* AVL::findMinValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

AVL::Node* AVL::deleteNode(Node* node, int value) {
    if (node == NULL)
        return node;

    if (value < node->data)
        node->left = deleteNode(node->left, value);
    else if (value > node->data)
        node->right = deleteNode(node->right, value);
    else {
        if (node->left == NULL || node->right == NULL) {
            Node* temp = node->left ? node->left : node->right;
            if (temp == NULL) {
                temp = node;
                node = NULL;
            } else
                *node = *temp;  // Copy the contents of the non-empty child

            delete temp;
        } else {
            Node* temp = findMinValueNode(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
    }

    if (node == NULL)
        return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalanceFactor(node);

    return node;
}

void AVL::inOrderTraversal(Node* node) {
    if (node == NULL)
        return;
    inOrderTraversal(node->left);
    cout << node->data << " ";
    inOrderTraversal(node->right);
}

void AVL::insert(int value) {
    root = insertNode(root, value);
}

void AVL::remove(int value) {
    root = deleteNode(root, value);
}

bool AVL::search(int value) {
    Node* current = root;
    while (current != NULL) {
        if (value == current->data)
            return true;
        else if (value < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return false;
}

void AVL::printInorder() {
    inOrderTraversal(root);
}

int main() {
    AVL avl;

    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(5);
    avl.insert(15);

    cout << "Inorder traversal of AVL tree: ";
    avl.printInorder();
    cout << endl;

    avl.remove(20);
    cout << "Inorder traversal after deleting 20: ";
    avl.printInorder();
    cout << endl;

    cout << "Search for value 15: " << (avl.search(15) ? "Found" : "Not found") << endl;
    cout << "Search for value 25: " << (avl.search(25) ? "Found" : "Not found") << endl;

    return 0;
}
