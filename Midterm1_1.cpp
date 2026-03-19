#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; // const variable calls for min and max number and list size

class DoublyLinkedList { // start of DoublyLinkedList class
private: // contains data that should not be edited unless by a public function call
    struct Node { // creating struct for Nodes in linked list
        int data; // data inside linked list
        Node* prev; // pointer to hold prev node location
        Node* next; // pointer for next node location
        Node(int val, Node* p = nullptr, Node* n = nullptr) { // complete parameter constructor for a Node
            data = val;
            prev = p;
            next = n;
        }
    };

    Node* head; // pointer for front of linked list
    Node* tail; // pointer for end of linked list

public: // public information for class that can be used in main() function
    DoublyLinkedList() { head = nullptr; tail = nullptr; } // default constructor for DoublyLinkedList class

    void insert_after(int value, int position) { // insert Node after specific position in linked list
        if (position < 0) { // if invalid position < 0 is used, print error msg and exit
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value); // creating new Node for linked list
        if (!head) { // if linked list is empty, set head and tail to pointer of new Node
            head = tail = newNode;
            return;
        }

        Node* temp = head; // create new temp Node to start from head's position pointer
        for (int i = 0; i < position && temp; ++i) // iterate through linked list to find location
            temp = temp->next;

        if (!temp) { // if temp ends as a nullptr, the position is out of the linked list bounds
            cout << "Position exceeds list size. Node not inserted.\n"; // prints error message, deletes node to insert, ends function
            delete newNode;
            return;
        }
        // if position is within the size of the linked list, insert new Node between the nodes
        newNode->next = temp->next; // set the newNode's next pointer to be the next node
        newNode->prev = temp; // set the newNode's prev pointer to the current temp node to insert the newNode
        if (temp->next) // if there is another node after temp
            temp->next->prev = newNode; // set the next node's prev pointer to point to the new Node
        else
            tail = newNode; // if not, set the tail pointer to the new Node
        temp->next = newNode; // set the current temp node's next pointer to the newNode instead of the node after newNode
    }

    void delete_val(int value) { // find and delete a node in the list with a specific value
        if (!head) return; // if list is empty, exit function

        Node* temp = head; // create temp node to iterate through from beginning of list
        
        while (temp && temp->data != value) // iterate through list, checking if list contains the requested value
            temp = temp->next;

        if (!temp) return; // if list does not contain value, exit function

        // list contains value, code for the deletion process

        if (temp->prev) // if there is a node before the node to be deleted
            temp->prev->next = temp->next; // set the prev node's next pointer to the node after the node to be deleted
        else // if deleting at the head
            head = temp->next; // set the head pointer to the node after the node to be deleted

        if (temp->next) // if there is a node after the node to be deleted
            temp->next->prev = temp->prev; // set the next node's prev pointer to the node before the node to be deleted
        else
            tail = temp->prev; // if there isn't a node after, set the tail pointer to point to the node before the node to be deleted

        delete temp; // delete the node with the value
    }

    void delete_pos(int pos) { // delete a node at a specific position in the list
        if (!head) { // if list is empty
            cout << "List is empty." << endl; // print error and return
            return;
        }
    
        if (pos == 1) { // if the user chose the first position 
            pop_front(); // use the "pop_front()" function to delete the head node and exit the function
            return;
        }
    
        Node* temp = head; // temp node to iterate through list without losing head pointer
    
        for (int i = 1; i < pos; i++){ // loop to confirm position is within list bounds
            if (!temp) { // if the position exceeds the list size
                cout << "Position doesn't exist." << endl; // print error and return
                return;
            }
            else // if position is still within bounds
                temp = temp->next; // move to next node in list
        }
        if (!temp) { // if list has been iterated through completely and the position still is not in list
            cout << "Position doesn't exist." << endl; // print error and exit function
            return;
        }
    
        if (!temp->next) { // if position is at the end of list
            pop_back(); // use the "pop_back()" function to delete list tail and exit function
            return;
        }
    
        // if position is found in list
        Node* tempPrev = temp->prev; // create new Node to hold the position of the node before the node to be deleted
        tempPrev->next = temp->next; // point the prev node's next pointer to the node after the node to be deleted, skipping the node in the list
        temp->next->prev = tempPrev; // set the next node's prev pointer to the node before the node to be deleted, connecting the list 
        delete temp; // delete the node at the position
    }

    void push_back(int v) { // append new Node with a value to the list, as if the list was a vector
        Node* newNode = new Node(v); // create new Node
        if (!tail) // if the list is empty, add node to list
            head = tail = newNode; // set the head and tail pointers to the newNode as it is the only node in the list
        else { // if the list is not empty
            tail->next = newNode; // place the new Node at the back of the list, and point the tail's next pointer to the node to add it to the list
            newNode->prev = tail; // set the new node's prev pointer to the tail to complete the connection
            tail = newNode; // set the tail to the newNode pointer to set the newNode as the end of the list
        }
    }
    
    void push_front(int v) { // append a new Node to the front of the list with a value
        Node* newNode = new Node(v); // new Node to add
        if (!head) // if list is empty
            head = tail = newNode; // set newNode to head and tail, as explained previously
        else { // if list has nodes
            newNode->next = head; // set the new Node's next pointer to point at the current head node, placing it before the start of the list
            head->prev = newNode; // set the head's prev pointer to the new Node, connecting the new Node to the list both ways
            head = newNode; // set the head pointer to the newNode to set the new Node at front of the list
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}