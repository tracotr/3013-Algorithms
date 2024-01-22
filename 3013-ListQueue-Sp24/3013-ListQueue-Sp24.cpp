#include <iostream>
#include "ListQueue.hpp"

using namespace std;

int main(){
	ListQueue Q;
	Q.push(5);
	Q.push(7);
	Q.print();

	for (int i = 0; i < 10; i++){
		Q.push(rand()%100);
	}
	Q.print();
	Q.pop();
	Q.pop();
	Q.pop();
	Q.print();
}
