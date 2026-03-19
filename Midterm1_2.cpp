#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    string getData(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return "";
        }
    
        if (pos == 1) {
            pop_front();
            return "";
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return "";
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return "";
        }
    
        return temp->data;
    }

    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
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

    void delete_val(string value) {
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

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
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

    void printLine() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        cout << "\tResulting line:" << endl;
        while (current) {
            cout << "\t\t" << current->data << endl;
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    srand(time(0));

    DoublyLinkedList* line = new DoublyLinkedList();
    int value; 
    int lineLength = 0;
    int random;

    ifstream fin("names.txt");

    if (!fin) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    string name;
    fin >> name;

    cout << "Store opens:" << endl;
    for (int i = 0; i < 5; ++i) {
        line->push_front(name);
        cout << "\t" << name << " joins the line" << endl;
        ++lineLength;
        fin >> name;
    }
    line->printLine();

    for (int i = 0; i < 19; ++i) {
        cout << "Time step #" << i + 2 << ":" << endl;
        value = rand() % 140 + 1;
        if (value <= 40) {
            // customer at front gets helped
            cout << "\t" << line->getData(0) << " is served" << endl;
            line->pop_front();
            --lineLength;
        }
        else if (value <= 100) {
            // new customer joins line
            line->push_back(name);
            cout << "\t" << name << " joined the line" << endl;
            ++lineLength;
            fin >> name;
        }
        else if (value <= 120) {
            // customer at end leaves
            cout << "\t" << line->getData(lineLength) << " (at the rear) left the line" << endl;
            --lineLength;
            line->pop_back();
        }
        else if (value <= 130) {
            // random customer leaves
            random = rand() % lineLength + 1;
            cout << "\t" << line->getData(random) << " left the line" << endl;
            line->delete_pos(random);
            --lineLength;
            
        }
        else if (value <=140) {
            // VIP skips line
        }
        line->printLine();

    }

    fin.close();
    return 0;
}