#include <iostream>
#include <string>
#define N 4
#include <cstdlib>

using namespace std;

struct Song {
	string name;
	int duration;
	int likes;
};

struct Queue {
	struct Song arr[N];
	int head = 0;
	int tail = 0;
};



int size(struct Queue *qe) {
	return qe -> tail - qe -> head;
}


int push(struct Queue *qe, Song aSong) {
	if (size(qe) != N) {
		qe -> arr[qe -> tail] = aSong;
		qe -> tail++;
		return 0;
	}
	else {
		cout << "Queue is overflowed" << endl;
		return 1;
	}
}


int empty(struct Queue *qe) {
	if (qe -> head >= qe -> tail) return 1;
	return 0;
}


Song pop(struct Queue *qe) {
	if (!empty(qe)) {
		Song element = qe -> arr[qe -> head];
		qe -> head++;
		return element;
	}
	cout << "Queue is underflowed" << endl;
	Song zero {"a", 0, 0};
	return zero;
}


Song front(struct Queue *qe) {
	if (!empty(qe)) {
		return qe -> arr[qe -> head];
	}
	else {
		cout << "Stack is underflowed" << endl;
		Song zero {"a", 0, 0};
		return zero;
	}
}

void print(struct Queue *qe) {
	int pos_of_head = qe -> head;
	while (!empty(qe)) {
		cout << "Name: " << (qe -> arr[qe -> head]).name << endl;
		cout << "Duration: " << (qe -> arr[qe -> head]).duration << endl;
		cout << "Likes: " << (qe -> arr[qe -> head]).likes << endl;
		cout << "----------------------------------\n";
		cout << endl;
		qe -> head++;
	}
	qe -> head = pos_of_head;
}



int main() {
	struct Song songs[] = {"Beliver", 165, 20, "Mansion", 130, 30, "Mountain", 200, 40, "Real", 196, 50, "Search", 200, 60, "Noname", 250, 100};

	//TASK 1
	Queue Song;

	// TASK 2
	for (int i = 0; i < 2; i++)
		push(&Song, songs[i]);

	cout << "The size of the queue is: " << size(&Song) << endl;
	cout << endl;
	print(&Song);

	// TASK 3
	for (int i = 2; i < 6; i++) {
		int is_full = push(&Song, songs[i]);
		if (is_full) break;

	}

	cout << "The size of the queue is: " << size(&Song) << endl;
	cout << endl;
	print(&Song);

	// TASK 4
	struct Song el_1 = pop(&Song);
	struct Song el_2 = pop(&Song);

	push(&Song, el_2);
	push(&Song, el_1);

	cout << "The size of the queue is: " << size(&Song) << endl;
	cout << endl;
	print(&Song);

	// TASK 5
	struct Song el_3 = pop(&Song);
	el_3.likes += 100;
	push(&Song, el_3);

	cout << "The size of the queue is: " << size(&Song) << endl;
	cout << endl;
	print(&Song);

	// TASK 6

	for (int i = 0; i < 5; i++) {
		struct Song element = pop(&Song);
		if (element.duration == 0)
			break;
	}


	cout << "The size of the queue is: " << size(&Song) << endl;
	cout << endl;
	print(&Song);
	return 0;
}