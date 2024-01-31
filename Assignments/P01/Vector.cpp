#include <iostream>
#include <fstream>

using namespace std;

// node struct to hold a value and the next node in the list.
struct Node{
    int value;
    struct Node* next;
};

class Vector{
    private:
        Node* head;                         // pointer to keep track of head of the linked list
        Node* rear;                         // pointer to keep track of the rear of the linked list
        int size = 0;

    public:
        // Default Constructor
        Vector(){
            head = nullptr;
            rear = nullptr;
            size = 0;                       // default values
        }

        // Copy from array Constructor
        Vector(int *A, int size){
            head = nullptr;
            rear = nullptr;
            this->size = size;              // default values except copying input size

            for(int i = 0; i < size; i++){
                int temp = A[i];
                pushRear(temp);             // loops through input array and pushes it into list
            }
        }

        // Copy from data file Constructor
        Vector(string fileName){
            head = nullptr;
            rear = nullptr;
            size = 0;                       // default values

            ifstream infile(fileName);      // open an input file as the input filename

            int val;                        // placeholder integer
            while(!infile.eof()){           // loops through all lines of input file until the end
                infile >> val;
                pushRear(val);              // pushes each integer into the vector
            }
            infile.close();                 // close infile
        }

        // copy Constructor
        Vector(const Vector& v2){
            head = v2.head;
            rear = v2.rear;
            size = v2.size;                 // copy all values of the vector class
        }

        // function for pushing a new node to the front of the linked list
        void pushFront(int inputValue){
            Node* newNode = new Node;
            newNode->value = inputValue;    // Node creation and value initialization

            newNode->next = head;           // newNode's next node is set to the previous head
            size++;                         // increment of linked list size
            head = newNode;                 // head is set as the newest node pushed in the front with this function
        }

        // function to push another vector to the front of current vector
        void pushFront(Vector v2){
            v2.rear->next = head;            // end of inputted vector has the current vector put the end of it
            head = v2.head;                  // current vector's head is set as the head of the input vector
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
        void pushRear(Vector v2){
            Node* temp = v2.head;       // Sets a temp node as the passed in vector's head node

            while(temp != nullptr){         // Loops until end of linked list
                pushRear(temp->value);      // pushes the value to the rear of the current linked list.
                temp = temp->next;          // moves to next node
            }
        }

        // function to push value into location in the list
        void pushAt(int loc, int val){
            Node* travelNode = head;        // sets the travelnode as the head of the list

            Node* tempNode = new Node;      
            tempNode->value = val;          // Node creation and value initialization

            for(int i = 0; i <= loc; i++){  // travels through list to location
                travelNode = travelNode->next;
            }

            tempNode->next = travelNode->next;  // sets the next of the tempnode to travelnodes next
            travelNode->next = tempNode;    // sets travelnodes next as tempnode
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

        // function to pop value from specific location in list
        int popAt(int loc){
            size--;                         // decrement of linked list size

            if(loc > size - 1){             // if the index is bigger than the size of the list - 1 returns -1;
                return -1;
            }

            Node* tempNode = nullptr;       // sets tempnode as nullptr
            Node* travelNode = head;        // sets travelnode as head to travel through

            for(int i = 0; i < loc - 1; i++){  // goes from head to one before location node
                travelNode = travelNode->next;
            }

            tempNode = travelNode->next;    // sets tempnode as the location value
            int tempValue = tempNode->value; // sets the return value
            
            travelNode->next = tempNode->next; // sets the travelnodes next as the one after the location node

            delete tempNode;                // delete tempnode to clear it out of memory
            return tempValue;
        }
        
        // function to return value of location in list
        int find(int searchValue){
            Node* tempNode = head;          // sets temp node as the head of the list

            for(int i = 0; i < size; i++){
                if(tempNode->value == searchValue){ // if tempnode value is the search value, return the index value
                    return i;           
                }else if(tempNode->next != nullptr){ // if tempnodes next value isn't null, go to next node
                    tempNode = tempNode->next;
                } else{                     // if the number doesnt exist in list, return -1
                    return -1;              
                }
            }

            return -1;
        }

        // function to print all values of list in a formatted fashion
        void print(ofstream& outfile){
            Node* temp = head;              // set temp node to start printing from

            outfile << "[";                 // front bracket! important
            cout << "[";

            while(temp != nullptr){         // Loops through list until empty
                cout << temp->value;        // prints value, also important
                outfile << temp->value;
                
                temp = temp->next;          // moves to next node

                if(temp != nullptr){        // if statement for print formatting
                    outfile << ", ";
                    cout << ", ";
                }
            }

            outfile << "]" << endl;         // close bracket, also also important :)
            cout << "]" << endl;
        }
};