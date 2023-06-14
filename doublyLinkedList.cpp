#include <iostream>

using namespace std;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;

        Node(int value) {
            this->data = value;
            this->next = NULL;
            this->prev = NULL;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(NULL), tail(NULL) {}

    void insert(int value);
    void insert(int value, int index);
    void remove(int value);
    bool search(int value) const;
    bool empty() const;
    void displayForward() const;
    void displayBackward() const;
};

void DoublyLinkedList::insert(int value) {
    Node* newNode = new Node(value);

    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void DoublyLinkedList::insert(int value, int index) {
    if (index < 0)
        throw runtime_error("Invalid index");

    if (index == 0) {
        Node* newNode = new Node(value);
        newNode->next = head;
        if (head != NULL)
            head->prev = newNode;
        head = newNode;
        if (tail == NULL)
            tail = newNode;
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

    Node* newNode = new Node(value);
    newNode->prev = current;
    newNode->next = current->next;
    if (current->next != NULL)
        current->next->prev = newNode;
    current->next = newNode;
    if (current == tail)
        tail = newNode;
}

void DoublyLinkedList::remove(int value) {
    if (head == NULL)
        return;

    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        if (head != NULL)
            head->prev = NULL;
        else
            tail = NULL;
        delete temp;
        return;
    }

    Node* current = head;
    while (current != NULL) {
        if (current->data == value) {
            if (current->prev != NULL)
                current->prev->next = current->next;
            if (current->next != NULL)
                current->next->prev = current->prev;
            if (current == tail)
                tail = current->prev;
            delete current;
            return;
        }
        current = current->next;
    }
}

bool DoublyLinkedList::search(int value) const {
    Node* current = head;
    while (current != NULL) {
        if (current->data == value)
            return true;
        current = current->next;
    }
    return false;
}

bool DoublyLinkedList::empty() const {
    return head == NULL;
}

void DoublyLinkedList::displayForward() const {
    Node* current = head;
    while (current != NULL) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "NULL" << endl;
}

void DoublyLinkedList::displayBackward() const {
    Node* current = tail;
    while (current != NULL) {
        cout << current->data << " -> ";
        current = current->prev;
    }
    cout << "NULL" << endl;
}

int main() {
    DoublyLinkedList list;

    list.insert(10);
    list.insert(20);
    list.insert(15);
    list.insert(30);

    cout << "Forward Linked List: ";
    list.displayForward();

    cout << "Search 20: " << (list.search(20) ? "Found" : "Not Found") << endl;

    list.insert(25, 2); // Inserting 25 at index 2

    cout << "Forward Linked List after inserting 25 at index 2: ";
    list.displayForward();

    list.remove(15);

    cout << "Forward Linked List after removing 15: ";
    list.displayForward();

    cout << "Backward Linked List: ";
    list.displayBackward();

    cout << "Is the list empty? " << (list.empty() ? "Yes" : "No") << endl;

    return 0;
}