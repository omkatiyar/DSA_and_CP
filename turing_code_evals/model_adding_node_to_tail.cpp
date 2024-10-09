#include <iostream>

// Define a Node structure
struct Node {
    int data;       // Data of the node
    Node* next;     // Pointer to the next node

    // Constructor
    Node(int value) : data(value), next(nullptr) {}
};

// Define a LinkedList class
class LinkedList {
public:
    Node* head;     // Pointer to the head of the list
    Node* tail;     // Pointer to the tail (last) of the list

    // Constructor
    LinkedList() : head(nullptr), tail(nullptr) {}

    // Method to add a node to the tail
    void addToTail(int value) {
        Node* newNode = new Node(value); // Create a new node

        if (head == nullptr) {
            // If the list is empty, set both head and tail to the new node
            head = newNode;
            tail = newNode;
        } else {
            // Otherwise, append the new node to the tail and update the tail pointer
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Method to print the linked list
    void printList() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    // Destructor to release allocated memory
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    LinkedList list;
    list.addToTail(10);
    list.addToTail(20);
    list.addToTail(30);

    list.printList(); // Output: 10 -> 20 -> 30 -> nullptr

    return 0;
}
