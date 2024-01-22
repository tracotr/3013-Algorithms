#include <iostream>

using namespace std;

struct Node {
	int val;
	Node* next;
	Node(int _val) {
		val = _val;
		next = nullptr;
	}
};

class ListQueue {
private:
	Node* front;
	Node* rear;
public:
	ListQueue() {
		front = rear = nullptr;
	}
	void push(int _val) {
		Node* temp = new Node(_val);
		if (!front && !rear) {
			front = rear = temp;
		}
		else {
			rear->next = temp;
			rear = temp;
		}
	}

	int pop() {
		int tval = front->val;
		Node* temp = front;
		front = front->next;
		delete temp;
		return tval;
	}

	void print() {
		Node* travel = front;
		while (travel) {
			cout << travel->val;
			if (travel->next) {
				cout << "->";
			}
			travel = travel->next;
		}
		cout << endl;
	}
};