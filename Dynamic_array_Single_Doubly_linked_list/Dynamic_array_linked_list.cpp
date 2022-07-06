#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>

using namespace std;

struct Lab {
	char subject;
	int number;
	bool isWanted;
};

struct DynamicArray {
	int capacity = 1;
	int realSize = 0;
	const int alpha = 2;
	Lab* innerArray = new Lab[capacity];


	void push_back(Lab aObj) {
		if (capacity == realSize) {
			capacity *= alpha;

			Lab* newArray = new Lab[capacity];
			
			for (int i = 0; i < realSize; i++) 
				newArray[i] = innerArray[i];

			delete[] innerArray;

			innerArray = newArray;

		}
		innerArray[realSize] = aObj;
		realSize++;
	}

	Lab pop_back() {
		if (realSize != 0) {
			realSize--;
			Lab element = innerArray[realSize];
			return element;
		}
		else {
			cout << "The array is empty" << endl;
			Lab zero {'0', 0, 0};
			return zero;
		}
	}


	int size() {
		return realSize;
	}

	Lab get(int aNum) {
		if (aNum <= realSize)
			return innerArray[aNum];
		else {
			cout << "No such element in the array" << endl;
			Lab zero {'0', 0, 0};
			return zero;
		}
	}


	void print() {
		for (int i = 0; i < realSize; i++) {
			cout << "Subject: " << innerArray[i].subject << endl;
			cout << "Number: " << innerArray[i].number << endl;
			cout << "Is wanted: " << boolalpha << innerArray[i].isWanted << endl;
			cout << "-------------------------------" << endl;
		}
	}


	void push_front(Lab aObj) {
		if (capacity == realSize) {
			capacity *= alpha;

			Lab* newArray = new Lab[capacity];
			
			for (int i = 0; i < realSize; i++) 
				newArray[i + 1] = innerArray[i];

			delete[] innerArray;

			innerArray = newArray;
		}
		else {
			for (int i = realSize; i > 0; i--) {
				innerArray[i] = innerArray[i - 1];
			}
		}
		innerArray[0] = aObj;
		realSize++;
	}


	Lab pop_front() {
		if (realSize != 0) {
			Lab element = innerArray[0];
			for (int i = 0; i < realSize - 1; i++) {
				innerArray[i] = innerArray[i + 1];
			}
			realSize--;
			return element;
		}
		else {
			cout << "The array is empty" << endl;
			Lab zero {'0', 0, 0};
			return zero;
		}
	}
	
};





struct Node {
	Lab data;
	Node* next;
	Node* previous;
};




struct LinkedList {
	Node* head = NULL;
	Node* tail = NULL;

	void push_back(Lab aLab) {
		Node* newNode = new Node();
		newNode->data = aLab;
		newNode->next = NULL;
		newNode->previous = NULL;

		if (head == NULL) {
			head = newNode;
			tail = newNode;
		}
		else {
			newNode->previous = tail;
			tail->next = newNode;
			tail = tail->next;
		}
	}


	void print() {
		for (Node* tempNode = head; tempNode != NULL; tempNode = tempNode->next) {
			cout << "Subject: " << tempNode->data.subject << endl;
			cout << "Number: " << tempNode->data.number << endl;
			cout << "Is wanted: " << boolalpha << tempNode->data.isWanted << endl;
			cout << "-------------------------------" << endl;
		}	
	}
	int size() {
		int count = 0;
		for (Node* tempNode = head; tempNode != NULL; tempNode = tempNode->next) {
			count++;
		}
		return count;
	}
	Lab get(int aNum) {
		Node* tempNode = head;
		for (int i = 0; i < aNum; i++) {
			tempNode = tempNode->next;
		}
		return tempNode->data;
	}

	void push_front(Lab aLab) {
		Node* newNode = new Node();
		newNode->data = aLab;
		newNode->next = head;
		newNode->previous = NULL;

		if (head == NULL) {
			tail = newNode;
			head = newNode;
		}
		else {
		head->previous = newNode;
		head = head->previous;
		}
	}

	Lab pop_back() {
		Lab element = tail->data;
		Node *tempNode = tail;
		tail = tail->previous;
		tail->next = NULL;
		delete tempNode;
		return element;
	}

	Lab pop_front() {
		Lab element = head->data;
		Node* tempNode = head;
		head = head->next;
		head->previous = NULL;
		delete tempNode;
		return element;
	}
};





Lab randomizer() {
	srand(time(NULL));
	string b = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char a = b[rand() % 36];
	int n = rand() % 5000;
	bool k = rand() % 2;
	Lab answer {a, n, k};
	return answer;
}


int main() {
	DynamicArray arr;
	LinkedList Labs;

	clock_t start_1 = clock();
	for (int i = 0; i < 50000; i++)
		arr.push_back(randomizer());
	clock_t end_1 = clock();
	float seconds_1 = float(end_1 - start_1) / CLOCKS_PER_SEC;	



	clock_t start_2 = clock();
	for (int i = 0; i < 10000; i++)
		arr.push_front(randomizer());
	clock_t end_2 = clock();
	float seconds_2 = float(end_2 - start_2) / CLOCKS_PER_SEC;



	clock_t start_3 = clock();
	for (int i = 0; i < 20000; i++)
		arr.get(rand() % 50000);
	clock_t end_3 = clock();
	float seconds_3 = float(end_3 - start_3) / CLOCKS_PER_SEC;


	clock_t start_4 = clock();
	for (int i = 0; i < 5000; i++)
		arr.pop_front();
	clock_t end_4 = clock();
	float seconds_4 = float(end_4 - start_4) / CLOCKS_PER_SEC;



	clock_t start_5 = clock();
	for (int i = 0; i < 5000; i++)
		arr.pop_back();
	clock_t end_5 = clock();
	float seconds_5 = float(end_5 - start_5) / CLOCKS_PER_SEC;

	float seconds_6 = seconds_1 + seconds_2 + seconds_3 + seconds_4 + seconds_5;
	cout << "DynamicArray: " << endl;
	cout << "The execution time for push_back method is: " << seconds_1 << endl;
	cout << "The execution time for push_front method is: " << seconds_2 << endl;
	cout << "The execution time for get method is: " << seconds_3 << endl;
	cout << "The execution time for pop_front method is: " << seconds_4 << endl;
	cout << "The execution time for pop_back method is: " << seconds_5 << endl;
	cout << "The overall execution time for DynamicArray is: " << seconds_6 << endl;



	
	

	clock_t start_21 = clock();
	for (int i = 0; i < 50000; i++)
		Labs.push_back(randomizer());
	clock_t end_21 = clock();
	float seconds_21 = float(end_21 - start_21) / CLOCKS_PER_SEC;


	clock_t start_22 = clock();
	for (int i = 0; i < 10000; i++)
		Labs.push_front(randomizer());
	clock_t end_22 = clock();
	float seconds_22 = float(end_22 - start_22) / CLOCKS_PER_SEC;

	//int sized = Labs.size();
	clock_t start_23 = clock();
	for (int i = 0; i < 20000; i++)
		Labs.get(rand() % 50000);
	clock_t end_23 = clock();
	float seconds_23 = float(end_23 - start_23) / CLOCKS_PER_SEC;


	clock_t start_24 = clock();
	for (int i = 0; i < 5000; i++)
		Labs.pop_front();
	clock_t end_24 = clock();
	float seconds_24 = float(end_24 - start_24) / CLOCKS_PER_SEC;


	clock_t start_25 = clock();
	for (int i = 0; i < 5000; i++)
		Labs.pop_back();
	clock_t end_25 = clock();
	float seconds_25 = float(end_25 - start_25) / CLOCKS_PER_SEC;

	float seconds_26 = seconds_21 + seconds_22 + seconds_23 + seconds_24 + seconds_25;

	cout << "Doubly LinkedList:" << endl;
	cout << "The execution time for push_back method is: " << seconds_21 << endl;
	cout << "The execution time for push_front method is: " << seconds_22 << endl;
	cout << "The execution time for get method is: " << seconds_23 << endl;
	cout << "The execution time for pop_front method is: " << seconds_24 << endl;
	cout << "The execution time for pop_back method is: " << seconds_25 << endl;
	cout << "The overall execution time is: " << seconds_26 << endl;
	return 0;
}