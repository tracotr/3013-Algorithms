#include <iostream>

using namespace std;

class IntStack {
private:
    int *stack;
    int top;
    int size;

public:
    IntStack() {
        top = -1;
        size = 10;
        stack = new int[10];
    }
    IntStack(int size){
        top = -1;
        this->size = size;
        stack = new int[size];
    }

    bool full() {
        return top == size - 1;
    }

    bool empty() {
        return top < 0;
    }

    void push(int val){
        if (!full()) {
            top++;
            // check if top > size
            stack[top] = val;
        }
        else {
            cout << "Full!!!!!!!!\n";
        }

    }

    int pop(){
        return stack[top--];
    }

    void print(){
        for (int i = 0; i <= top; i++)
        {
            cout << stack[i] << " ";
        }
        cout << endl;
    }
};

int main(){
    IntStack I1;

    for (int i = 0; i <= 12; i++){
        if (I1.full())
            I1.push(i);
    }
    
    I1.print();
}