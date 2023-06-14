#include <iostream>

using namespace std;

class CircularLinkedList {
private:
    struct Node {
        int data;
        Node* next;

        Node(int value) : data(value), next(NULL) {}
    };

    Node* head;

public:
    CircularLinkedList() : head(NULL) {}

    void insert(int value);
    void insert(int value, int index);
    void remove(int value);
    bool search(int value) const;
    bool empty() const;
    void display() const;
};

void CircularLinkedList::insert(int value) {
    Node* newNode = new Node(value);

    if (head == NULL) {
        // If the list is empty, set the new node as the head and make it point to itself
        head = newNode;
        newNode->next = head;
    } else {
        // Traverse the list to find the last node and update its next pointer
        Node* current = head;
        while (current->next != head) {
            current = current->next;
        }
        current->next = newNode;
        newNode->next = head;
    }
}

void CircularLinkedList::insert(int value, int index) {
    if (index < 0)
        throw runtime_error("Invalid index");

    if (index == 0) {
        // Inserting at the beginning
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        // Traverse to the last node and update its next pointer to the head
        Node* current = head;
        while (current->next != NULL)
            current = current->next;
        current->next = head;
        return;
    }

    // Traverse the list to find the node just before the desired index
    Node* current = head;
    int currentIndex = 0;
    while (current != NULL && currentIndex < index - 1) {
        current = current->next;
        currentIndex++;
    }

    if (current == NULL)
        throw runtime_error("Invalid index");

    // Insert the new node between the current node and its next node
    Node* newNode = new Node(value);
    newNode->next = current->next;
    current->next = newNode;
}

void CircularLinkedList::remove(int value) {
    if (head == NULL)
        return;

    if (head->data == value) {
        // Removing the head node
        Node* temp = head;
        Node* current = head;
        // Traverse to find the last node
        while (current->next != head)
            current = current->next;
        if (current == head)
            head = NULL; // Only one node in the list
        else {
            current->next = head->next;
            head = head->next;
        }
        delete temp;
        return;
    }

    // Traverse the list to find the node with the specified value
    Node* current = head;
    while (current->next != head) {
        if (current->next->data == value) {
            // Remove the node by adjusting the next pointer of the previous node
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            return;
        }
        current = current->next;
    }
}

bool CircularLinkedList::search(int value) const {
    if (head == NULL)
        return false;

    // Start from the head and traverse the list until reaching the head again
    Node* current = head;
    do {
        if (current->data == value)
            return true;
        current = current->next;
    } while (current != head);

    return false;
}

bool CircularLinkedList::empty() const {
    return head == NULL;
}

void CircularLinkedList::display() const {
    if (head == NULL) {
        cout << "NULL" << endl;
        return;
    }

    // Start from the head and traverse the list until reaching the head again
    Node* current = head;
    do {
        cout << current->data << " -> ";
        current = current->next;
    } while (current != head);
    cout << "NULL" << endl;
}

int main() {
    CircularLinkedList list;

    list.insert(10);
    list.insert(20);
    list.insert(15);
    list.insert(30);

    cout << "Initial Circular Linked List: ";
    list.display();

    cout << "Search 20: " << (list.search(20) ? "Found" : "Not Found") << endl;

    list.insert(25, 2); // Inserting 25 at index 2

    cout << "Circular Linked List after inserting 25 at index 2: ";
    list.display();

    list.remove(15);

    cout << "Circular Linked List after removing 15: ";
    list.display();

    cout << "Is the list empty? " << (list.empty() ? "Yes" : "No") << endl;

    return 0;
}
