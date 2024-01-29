#include <iostream>

using namespace std;

class Vector{
    private:
        int *array;
        int size;

    public:
        Vector(){
            size = 0;
        }

        void push(int val){
            size++;
            array[size] = val;
        }

        void print(){
            for(int i = 0; i < this->size; i++){
                cout << array[i] << " ";
            }
            cout << endl;
        }
};