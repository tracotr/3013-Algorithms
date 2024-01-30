#include "Vector.cpp"

using namespace std;

int main(){
    int x = 0;

    Vector v1;
    v1.pushFront(18);
    v1.pushFront(20);
    v1.pushFront(25);
    v1.pushRear(18);
    v1.pushRear(20);
    v1.pushRear(25);
    v1.print();
    // [25, 20, 18, 18, 20, 25]

    int A[] = {11,25,33,47,51};
    Vector v2(A,5);
    v2.print();
    // [11, 25, 33, 47, 51]

    v2.pushFront(9);
    v2.inOrderPush(27);
    v2.pushRear(63);
    v2.print();
    // [9, 11, 25, 33, 47, 51, 63]

    v1.pushRear(v2);
    v1.print();
    // [25, 20, 18, 18, 20, 25, 9, 11, 25, 33, 47, 51, 63]

    x = v1.popFront();
    x = v1.popFront();
    x = v1.popFront();
    v1.print();
    // [18, 20, 25, 9, 11, 25, 33, 47, 51, 63]
    cout<< x << endl;
    // 18

    x = v1.popRear();
    x = v1.popRear();
    x = v1.popRear();
    v1.print();
    // [18, 20, 25, 9, 11, 25, 33]
    cout<< x << endl;
    // 47

    x = v2.popAt(3);
    v2.print();
    // [9, 11, 25, 33, 47, 51, 63]
    cout<< x << endl;
    // 27

    x = v2.find(51);
    cout<< x << endl;
    // it says 5 on the sheet but i get 6 because of line 24

    x = v2.find(99);
    cout<<x<<endl;
    // -1

    //Vector v3(v1);
    //v3.print();
    // [18, 20, 25, 9, 11, 25, 27, 33]
}