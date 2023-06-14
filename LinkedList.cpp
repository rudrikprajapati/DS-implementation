#include <iostream>

using namespace std;

class LinkedList {
private:
    struct Node {
        int data;
        Node* next;

        Node(int value) {
            this->data = value;
            this->next = NULL;
        }
    };

    Node* head;

public:
    LinkedList() : head(NULL) {}

    void insert(int value);
    void insert(int value, int index);
    void remove(int value);
    bool search(int value) const;
    bool empty() const;
    void display() const;
};

void LinkedList::insert(int value) {
    Node* newNode = new Node(value);

    if (head == NULL) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void LinkedList::insert(int value, int index) {
    if (index < 0)
        throw runtime_error("Invalid index");

    Node* newNode = new Node(value);

    if (index == 0) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* current = head;
    int currentIndex = 0;
    while (current != NULL && currentIndex < index - 1) {
        current = current->next;
        currentIndex++;
    }

    if (current == NULL)
        throw runtime_error("Invalid index");

    newNode->next = current->next;
    current->next = newNode;
}

void LinkedList::remove(int value) {
    if (head == NULL)
        return;

    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;
    while (current->next != NULL) {
        if (current->next->data == value) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            return;
        }
        current = current->next;
    }
}

bool LinkedList::search(int value) const {
    Node* current = head;
    while (current != NULL) {
        if (current->data == value)
            return true;
        current = current->next;
    }
    return false;
}

bool LinkedList::empty() const {
    return head == NULL;
}

void LinkedList::display() const {
    Node* current = head;
    while (current != NULL) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "NULL" << endl;
}

int main() {
    LinkedList list;

    list.insert(10);
    list.insert(20);
    list.insert(15);
    list.insert(30);

    cout << "Initial Linked List: ";
    list.display();

    cout << "Search 20: " << (list.search(20) ? "Found" : "Not Found") << endl;

    list.remove(15);

    cout << "Linked List after removing 15: ";
    list.display();

    list.insert(15, 2);
    cout << "Linked List after inserting at original position 15: ";
    list.display();

    cout << "Is the list empty? " << (list.empty() ? "Yes" : "No") << endl;

    return 0;
}
