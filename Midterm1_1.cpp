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

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
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