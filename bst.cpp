#include <bits/stdc++.h>
using namespace std;

class BST
{
private:
    struct Node
    {
        Node *left;
        Node *right;
        int data;

        Node(int data)
        {
            this->left = NULL;
            this->right = NULL;
            this->data = data;
        }
    };

    Node *root;
    Node *insertNode(Node *curr, int val);
    Node *deleteCurr(Node *curr);
    Node *findLastRight(Node *curr);
    void inorder(Node *root);
    Node *deleteNode(Node *curr, int val);
    bool searchBST(Node *curr, int val);

public:
    BST() : root(NULL){};
    void deleteN(int val);
    void insert(int val);
    void inorderTraversal();
    bool search(int val);
};

BST::Node *BST::insertNode(Node *curr, int val)
{

    if (!curr)
    {
        return new Node(val);
    }

    if (curr->data > val)
    {
        curr->left = insertNode(curr->left, val);
    }
    else if (curr->data < val)
    {
        curr->right = insertNode(curr->right, val);
    }
    return curr;
}

void BST::insert(int val)
{
    root = insertNode(root, val);
}

BST::Node *BST::findLastRight(Node *curr)
{
    if (!curr->right)
        return curr;

    return findLastRight(curr->right);
}

BST::Node *BST::deleteCurr(Node *curr)
{
    if (!curr->left)
    {
        return curr->right;
    }
    else if (!curr->right)
    {
        return curr->left;
    }

    Node *rightChild = curr->right;
    Node *lastRight = findLastRight(curr->left);
    lastRight->right = rightChild;
    return curr->left;
}

BST::Node *BST::deleteNode(Node *curr, int val)
{
    if (!curr)
        return curr;

    if (curr->data == val)
        return deleteCurr(curr);

    Node *temp = curr;
    while (temp)
    {
        if (temp->data > val)
        {
            if (temp->left != NULL && temp->left->data == val)
            {
                temp->left = deleteCurr(temp->left);
                break;
            }
            else
            {
                temp = temp->left;
            }
        }
        else
        {
            if (temp->right != NULL && temp->right->data == val)
            {
                temp->right = deleteCurr(temp->right);
                break;
            }
            else
            {
                temp = temp->right;
            }
        }
    }
    return curr;
}

void BST::deleteN(int val)
{
    root = deleteNode(root, val);
}

void BST::inorder(Node *root)
{
    if (!root)
        return;

    inorder(root->left);
    cout << root->data << "->";
    inorder(root->right);
}

void BST::inorderTraversal()
{
    inorder(root);
    cout << endl;
}

bool BST::searchBST(Node *curr, int val)
{
    while (curr)
    {
        if (val == curr->data)
        {
            return true;
        }
        else if (val < curr->data)
        {
            curr = curr->left;
        }
        else if (val > curr->data)
        {
            curr = curr->right;
        }
    }
    return false;
}

bool BST::search(int val)
{
    bool res = searchBST(root, val);
    cout << res << endl;
    return res;
}

int main()
{
    BST tree;
    tree.insert(6);
    tree.insert(1);
    tree.insert(2);
    tree.insert(4);
    tree.insert(8);
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.inorderTraversal();
    tree.deleteN(5);
    tree.inorderTraversal();
    tree.search(5);
}