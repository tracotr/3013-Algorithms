#include <iostream>

using namespace std;

struct Node{
    int value;
    struct Node* next;
};

class Vector{
    private:
        Node* head;
        Node* rear;
        int size = 0;

    public:
        // Default Constructor
        Vector(){
            head = nullptr;
            rear = nullptr;
            size = 0;
        }

        // Copy from array Constructor
        Vector(int *A, int size){
            head = nullptr;
            rear = nullptr;
            this->size = size;

            for(int i = 0; i < size; i++){
                int temp = A[i];
                pushRear(temp);
            }
        }

        // Function for pushing a new node to the front of the linked list
        void pushFront(int inputValue){
            Node* newNode = new Node;
            newNode->value = inputValue;    // Node creation and value initialization

            newNode->next = head;           // newNode's next node is set to the previous head
            size++;                         // increment of linked list size
            head = newNode;                 // head is set as the newest node pushed in the front with this function
        }


        // function for pushing a new node to the rear of the linked list
        void pushRear(int inputValue){
            Node* newNode = new Node;
            newNode->value = inputValue;
            newNode->next = nullptr;        // Node creation and value initialization

            rear = head;                    // stores the head value to start at, for traversal through the nodes

            if (head == nullptr) {          // if statement if the list is empty, initializes the head node.
                head = newNode;
                return;
            }

            while (rear->next != nullptr) { // Traversal through nodes until it finds an empty node
                rear = rear->next;
            }

            size++;                         // increment of linked list size
            rear->next = newNode;           // Once it goes through the entire list, sets the rearmost node as newNode.
        }
        
        // function for pushing another linked list onto the rear of the linked list
        void pushRear(Vector vector){
            Node* temp = vector.head;       // Sets a temp node as the passed in vector's head node

            while(temp != nullptr){         // Loops until end of linked list
                pushRear(temp->value);      // pushes the value to the rear of the current linked list.
                temp = temp->next;          // moves to next node
            }
        }

        // function for pushing an input value  in order into a list (requires list to be in order already)
        void inOrderPush(int inputValue){

            Node* tempNode = head;          // sets tempnode to the head of the list

            Node* newNode = new Node;
            newNode->value = inputValue;    // Node creation and value initialization
             
            for(int i = 0; i < size; i++){  // for loop to go through size of linked list
                if(tempNode->next->value < inputValue){
                    tempNode = tempNode->next;  // if tempnode's next node value is less than the input value, goes to next in list
                } else{
                    newNode->next = tempNode->next; // newnodes next node is tempnodes next node,
                    tempNode->next = newNode; // tempnodes next node is the newnode
                    size++;                 // increment of linked list size
                    return;                 // returns to stop for loop
                }                           // idk if this is hacky, but makes sense to me
            }
            
        }

        // function for removing and returning the head's value in the linked list
        int popFront(){
            int temp = head->value;         // temp value holds the head's value

            Node* tempNode = head;          // pointer to head to hold
            head = head->next;              // sets head to the next node
            delete tempNode;                // deletes old head

            size--;                         // decrement of linked list size
            return temp;
        }

        // function for removing and returning the rear's value in the linked list
        int popRear(){
            int temp = rear->value;         // temp value holds the rear's value

            Node* beforeRear = head;        // before rear starts at head
            while(beforeRear->next->next != nullptr){   // checks the next two nodes to see if its empty
                beforeRear = beforeRear->next;          // moves onto next node
            }
            
            delete (beforeRear->next);      // deletes the next node (which is the rear), idk why deleting the rear doesnt work
            beforeRear->next = nullptr;     // sets the node after beforerear as null
            rear = beforeRear;              // rear is set as beforerear

            size--;                         // decrement of linked list size
            return temp;
        }

        int popAt(int loc){
            size--;                         // decrement of linked list size

            Node* tempNode = head;
            for(int i = 1; i <= loc; i++){
                tempNode = tempNode->next;
            }
            int tempValue = tempNode->value;
            delete tempNode;
            return tempValue;
        }
        
        int find(int searchValue){
            Node* tempNode = head;

            for(int i = 0; i < size; i++){
                if(tempNode->value == searchValue){
                    return i;
                }else if(tempNode->next != nullptr){
                    tempNode = tempNode->next;
                } else{
                    return -1;
                }
            }
            return -1;
        }

        void print(){
            Node* temp = head;              // set temp node to start printing from

            cout << "[";
            while(temp != nullptr){         // Loops through list until empty
                cout << temp->value;
                temp = temp->next;          // moves to next node

                if(temp != nullptr){        // if statement for print formatting
                    cout << ", ";
                }
            }
            cout << "]" << endl;
        }
};