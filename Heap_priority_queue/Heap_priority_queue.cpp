#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

struct Data {
	int health;
	int damage;
	int playersSkill;

	Data() {
		health = 1 + rand() % 500;
		damage = 1 + rand() % 100;
		playersSkill = 1 + rand() % 10;
	}

	Data(int aHealth, int aDamage, int aPlayersSkill) {
		health = aHealth;
		damage = aDamage;
		playersSkill = aPlayersSkill;
	}


	/*bool operator<(const Data& aEnemy) {
		if (damage != aEnemy.damage)
			return damage < aEnemy.damage;
		else if (health != aEnemy.health)
			return health < aEnemy.health;
		else
			return playersSkill < aEnemy.playersSkill;
	}

	bool operator==(const Data& aEnemy) {
		return (damage == aEnemy.damage && health == aEnemy.health && playersSkill == aEnemy.playersSkill);
	}*/
};

bool operator<(const Data& aEnemy1, const Data& aEnemy2) {

		if (aEnemy1.damage != aEnemy2.damage)
			return aEnemy1.damage < aEnemy2.damage;

		else if (aEnemy1.health != aEnemy2.health)
			return aEnemy1.health < aEnemy2.health;

		return aEnemy1.playersSkill < aEnemy2.playersSkill;
	}

	bool operator==(const Data& aEnemy1, const Data& aEnemy2) {
		return (aEnemy1.damage == aEnemy2.damage && aEnemy1.health == aEnemy2.health && aEnemy1.playersSkill == aEnemy2.playersSkill);
	}

class Heap {
public:
	int capacity;
	int realSize;
	const int alpha = 2;
	Data* innerArray;

	Heap() {
		capacity = 1;
		realSize = 0;
		innerArray = new Data[capacity];
	}

	~Heap() {
		delete[] innerArray;
	}

	void push_back(Data aObj) {
		if (capacity == realSize) {
			capacity *= alpha;

			Data* newArray = new Data[capacity];
			
			for (int i = 0; i < realSize; i++) 
				newArray[i] = innerArray[i];

			delete[] innerArray;

			innerArray = newArray;

		}
		innerArray[realSize] = aObj;
		realSize++;
	}


	int getParent(int aIndex) {
		return (aIndex - 1) / 2;
	}

	int getLeftChild(int aIndex) {
		return 2 * aIndex + 1;
	}

	int getRightChild(int aIndex) {
		return 2 * aIndex + 2;
	}

	void HeapSort() {
		for (int i = realSize - 1 / 2; i >= 0; i--) {
			siftDown(i);
		}
		
		int k = realSize;
		while(realSize != 0) {
			swap(innerArray[realSize - 1], innerArray[0]);
			realSize--;
			siftDown(0);
		}
		realSize = k;
	}

	int size() {
		return realSize;
	}

	void siftUp(int aIndex) {
		int parent = getParent(aIndex);
		while (aIndex > 0 && innerArray[parent] < innerArray[aIndex]) {

			swap(innerArray[parent], innerArray[aIndex]);

			aIndex = parent;
			parent = getParent(aIndex);
		}
	}

	void siftDown(int aIndex) {
		int leftChild = getLeftChild(aIndex);
		int rightChild = getRightChild(aIndex);

		int maxIndex = aIndex;

		if (leftChild < realSize && innerArray[maxIndex] < innerArray[leftChild]) {
			maxIndex = leftChild;
		}

		if (rightChild < realSize && innerArray[maxIndex] < innerArray[rightChild])
			maxIndex = rightChild;

		if (maxIndex != aIndex) {
			swap(innerArray[maxIndex], innerArray[aIndex]);
			siftDown(maxIndex);
		}
	}
	
};

class PriorityQueue {
public:
	Heap arr;
	int qsize;

	PriorityQueue() {
		qsize = 0;
	}

	void push(Data aEnemy) {
		arr.push_back(aEnemy);
		qsize++;
		arr.siftUp(arr.realSize - 1);
	}

	Data top() {
		if (qsize != 0)
			return arr.innerArray[0];
		else {
			cout << "Binary Tree is empty" << endl;
			return Data(0, 0, 0);
		}
	}

	void pop() {
		if (qsize != 0) {
			swap(arr.innerArray[0], arr.innerArray[arr.realSize - 1]);
			arr.realSize--;
			qsize--;
			arr.siftDown(0);
		}
	}

	int size() {
		return qsize;
	}

	bool empty() {
		return qsize == 0;
	}
};


template <typename T>

float testPriorityQueueSpeed(T&& priorityQueue) {
	const int iters = 100000;
	clock_t timeStart = clock();
 	for (int i = 0; i < iters; i++) {
		int insertDataAmount = rand() % 6 + 5;
		for (int j = 0; j < insertDataAmount; j++) {
			priorityQueue.push(Data());
	 	}
	 	priorityQueue.top();
	 	priorityQueue.pop();
	}
	clock_t timeEnd = clock();
	float time = (float(timeEnd - timeStart)) / CLOCKS_PER_SEC;
	return time;
	}

bool testPriorityQueue() {
	srand(time(NULL));
	const int iters = 20000;
	PriorityQueue myPriorQueue;
	priority_queue<Data> stlPriorQueue;

	bool isDataEqual = true;
	for (int i = 0; i < iters; i++) {
		int insertDataAmount = rand() % 6 + 5;

		for (int j = 0; j < insertDataAmount; j++) {
			Data randData = Data();
			myPriorQueue.push(randData);
			stlPriorQueue.push(randData);
		} 
		if (!(myPriorQueue.top() == stlPriorQueue.top())) {
	 		isDataEqual = false;
	 		cerr << "Comparing failed on iteration " << i << endl;
	 		break;
	 	}
		int removeDataAmount = rand() % insertDataAmount;
		for (int j = 0; j < removeDataAmount; j++) {
			myPriorQueue.pop();
			stlPriorQueue.pop();
	 	}
	 }
	int myQueueSize = myPriorQueue.size();
	int stlQueueSize = stlPriorQueue.size();
	float stlTime = testPriorityQueueSpeed<priority_queue<Data>>(priority_queue<Data>());
	float myTime = testPriorityQueueSpeed<PriorityQueue>(PriorityQueue());
	cout << "My PriorityQueue:" << endl;
	cout << "Time: " << myTime << ", size: " << myQueueSize << endl;
	cout << "STL priority_queue:" << endl;
	cout << "Time: " << stlTime << ", size: " << stlQueueSize << endl << endl;
	if (isDataEqual && myQueueSize == stlQueueSize) {
		cout << "The lab is completed" << endl << endl;
		return true;
	}
	cerr << ":(" << endl << endl;
	return false;
}

void print_a_queue(PriorityQueue queue, priority_queue<Data> aQueue) {
	while (!queue.empty()) {
		Data el3 = queue.top();
		cout << "Health: " << el3.health << endl;
		cout << "Damage: " << el3.damage << endl;
		cout << "Player's Skill: " << el3.playersSkill << endl;
		cout << "-------------------------------" << endl;
		queue.pop();
	}

	cout << endl;
	cout << endl;

	while (!aQueue.empty()) {
		Data el4 = aQueue.top();
		cout << "Health: " << el4.health << endl;
		cout << "Damage: " << el4.damage << endl;
		cout << "Player's Skill: " << el4.playersSkill << endl;
		cout << "-------------------------------" << endl;
		aQueue.pop();
	}
}

int main() {
	srand(time(NULL));
	Heap arr;
	Heap arr2;
	for (int i = 0; i < 200000; i++) {
		Data rand = Data();
		arr.push_back(rand);
		arr2.push_back(rand);
	}

	clock_t start1 = clock();
	sort(arr.innerArray, arr.innerArray + arr.realSize);
	clock_t end1 = clock();
	float total1 = float(end1 - start1) / CLOCKS_PER_SEC;

	clock_t start2 = clock();
	arr2.HeapSort();
	clock_t end2 = clock();
	float total2 = float(end2 - start2) / CLOCKS_PER_SEC;

	cout << "The execution time for heapsort: " << total2 << endl;
	cout << "The execution time for std::sort: " << total1 << endl;

	testPriorityQueue();
	

	return 0;
}