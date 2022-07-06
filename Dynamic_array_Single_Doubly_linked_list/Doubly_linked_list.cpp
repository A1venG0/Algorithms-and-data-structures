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


struct Node {
	Lab data;
	Node* next;
};




struct LinkedList {
	Node* head = NULL;
	Node* tail = NULL;

	void push_back(Lab aLab) {
		Node* newNode = new Node();
		newNode->data = aLab;
		newNode->next = NULL;

		if (head == NULL) {
			head = newNode;
			tail = newNode;
		}
		else {
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

		if (head == NULL) {
			tail = newNode;
		}
		head = newNode;
	}

	Lab pop_back() {
		Lab element = tail->data;
		Node* tempNode = head;
		Node *delNode = tail;
		while(tempNode->next != tail) {
			tempNode = tempNode->next;
		}
		tempNode->next = NULL;
		tail = tempNode;
		delete delNode;
		return element;
	}

	Lab pop_front() {
		Lab element = head->data;
		Node* tempNode = head;
		head = head->next;
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
	LinkedList Labs;

	struct Lab labss[] = {'a', 1, 1, 'b', 2, 1, 'c', 3, 0, 'd', 4, 0, 'e', 5, 1, 'f', 6, 1, 'g', 7, 1};


	/*Labs.push_back(labss[1]);
	Labs.push_back(labss[1]);
	Labs.push_back(labss[1]);
	Labs.push_back(labss[1]);
	Labs.push_back(labss[1]);
	Labs.pop_back();
	Labs.pop_back();
	Labs.pop_back();
	Labs.pop_back();
	Labs.pop_back();
	cout << "YES" << endl;*/


	/*clock_t start_1 = clock();
	for (int i = 0; i < 50000; i++)
		Lab.push_back(randomizer());
	clock_t end_1 = clock();
	float seconds_1 = float(end_1 - start_1) / CLOCKS_PER_SEC;	



	clock_t start_2 = clock();
	for (int i = 0; i < 10000; i++)
		Lab.push_front(randomizer());
	clock_t end_2 = clock();
	float seconds_2 = float(end_2 - start_2) / CLOCKS_PER_SEC;



	clock_t start_3 = clock();
	for (int i = 0; i < 20000; i++)
		Lab.get(rand() % 50000);
	clock_t end_3 = clock();
	float seconds_3 = float(end_3 - start_3) / CLOCKS_PER_SEC;


	clock_t start_4 = clock();
	for (int i = 0; i < 5000; i++)
		Lab.pop_front();
	clock_t end_4 = clock();
	float seconds_4 = float(end_4 - start_4) / CLOCKS_PER_SEC;



	clock_t start_5 = clock();
	for (int i = 0; i < 5000; i++)
		Lab.pop_back();
	clock_t end_5 = clock();
	float seconds_5 = float(end_5 - start_5) / CLOCKS_PER_SEC;

	float seconds_6 = seconds_1 + seconds_2 + seconds_3 + seconds_4 + seconds_5;

	cout << "The execution time for push_back method is: " << seconds_1 << endl;
	cout << "The execution time for push_front method is: " << seconds_2 << endl;
	cout << "The execution time for get method is: " << seconds_3 << endl;
	cout << "The execution time for pop_front method is: " << seconds_4 << endl;
	cout << "The execution time for pop_back method is: " << seconds_5 << endl;
	cout << "The overall execution time for DynamicArray is: " << seconds_6 << endl;*/

	/*Labs.push_back(labss[0]);
	Labs.push_front(labss[1]);
	Labs.push_front(labss[2]);
	Labs.push_front(labss[3]);
	Labs.print();
	cout << endl;
	struct Lab el = Labs.get(3);
	cout << "Subject: " << el.subject << endl;
	cout << "Number: " << el.number << endl;
	cout << "Is wanted: " << boolalpha << el.isWanted << endl;
	Labs.pop_back();
	Labs.pop_front();
	Labs.print();

	/*Labs.push_back(labss[0]);
	Labs.print();
	Labs.push_back(labss[1]);
	Labs.push_back(labss[2]);
	Labs.print();

	struct Lab element = Labs.get(0);
	cout << "Subject: " << element.subject << endl;
	cout << "Number: " << element.number << endl;
	cout << "Is wanted: " << boolalpha << element.isWanted << endl;
	cout << Labs.size() << endl;
	cout << endl;
	Labs.push_front(labss[3]);
	Labs.push_front(labss[4]);

	Labs.print();
	cout << endl;
	Labs.pop_back();
	Labs.pop_back();
	Labs.print();
	cout << endl;
	Labs.pop_front();
	Labs.pop_front();
	Labs.print();*/

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

	cout << "LinkedList:" << endl;
	cout << "The execution time for push_back method is: " << seconds_21 << endl;
	cout << "The execution time for push_front method is: " << seconds_22 << endl;
	cout << "The execution time for get method is: " << seconds_23 << endl;
	cout << "The execution time for pop_front method is: " << seconds_24 << endl;
	cout << "The execution time for pop_back method is: " << seconds_25 << endl;
	cout << "The overall execution time is: " << seconds_26 << endl;
	return 0;
}