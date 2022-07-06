#include <iostream>
#include <string>
#define N 8
#include <cstdlib>

using namespace std;

struct Patron {
	int caliber;
	string manufacturer;
	int price;
};


struct Stack {
	struct Patron arr[N];
	int top = 0;
};


void push(struct Stack *st, Patron aPatron) {
	if (st -> top < N) {
		st -> arr[st -> top] = aPatron;
		st -> top++;
	}
	else {
		cout << "Stack is overflowed" << endl;
	}
}

int empty(struct Stack *st) {
	if (st -> top == 0) return 1;
	return 0;
}

Patron pop(struct Stack *st) {
	if (!empty(st)) {
		st -> top--;
		return st -> arr[st -> top];
	}
	else {
		cout << "Stack is empty" << endl;
		Patron zero {0, "a", 0};
		return zero;
	}

}

int size(struct Stack *st) {
	return st -> top;
}

Patron top(struct Stack *st) {
	if (!empty(st))
		return st -> arr[st -> top - 1];
	else {
		cout << "Stack is empty" << endl;
		Patron zero {0, "a", 0};
		return zero;
	}
}

void print(struct Stack *st) {
	int size_of_el = st -> top;
	while (!empty(st)) {
		cout << "Caliber: " << (st -> arr[st -> top - 1]).caliber << endl;
		cout << "Manufacturer: " << (st -> arr[st -> top - 1]).manufacturer << endl;
		cout << "Price: " << (st -> arr[st -> top - 1]).price << endl;
		cout << "----------------------------------\n";
		cout << endl;
		st -> top--;
	}
	st -> top = size_of_el;
}

int main() {
	struct Patron patrons[] = {101, "Minnesota", 200, 102, "Miami", 300, 103, "Washington", 400, 104, "Missyri", 500, 105, "Alyaska", 600, 
	106, "Kyiv", 700, 107, "Odessa", 800, 108, "Lviv", 900, 109, "Iowa", 1000, 110, "California", 1100};
	
	// TASK 1
	Stack Patron;

	// TASK 2
	for(int i = 0; i < 6; i++) 
		push(&Patron, patrons[i]);
	

	cout << "The size of the stack is: " << size(&Patron) << endl;
	cout << endl;
	print(&Patron);
	
	// TASK 3	
	struct Patron el_1 = pop(&Patron);
	struct Patron el_2 = pop(&Patron);

	if (el_1.price > el_2.price)
		push(&Patron, el_1);
	else
		push(&Patron, el_2);

	cout << "The size of the stack is: " << size(&Patron) << endl;
	cout << endl;
	print(&Patron);

	// TASK 4
	for (int i = 6; i < 10; i++) {
		push(&Patron, patrons[i]);
	}


	cout << "The size of the stack is: " << size(&Patron) << endl;
	cout << endl;
	print(&Patron);

	// TASK 5
	for (int i = 0; i < 6; i++)
		pop(&Patron);


	cout << "The size of the stack is: " << size(&Patron) << endl;
	cout << endl;
	print(&Patron);

	// TASK 6

	for (int i = 0; i < 4; i++) {
		struct Patron element = pop(&Patron);
		if (element.price == 0) 
			break;
	}

	cout << "The size of the stack is: " << size(&Patron) << endl;
	cout << endl;
	print(&Patron);

	return 0;
}