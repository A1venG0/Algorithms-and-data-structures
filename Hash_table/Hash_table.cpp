#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>
#include <unordered_map>
#define N 12
#define ll long long

using namespace std;


struct Data {
	string address;
	int area;
	bool isHeated;

	Data() {
		address = "";
		for (int i = 0; i < 5; i++)
			address += (char) 65 + rand() % 26;
		area = 1 + rand() % 2000;
		isHeated = rand() % 2;
	}
};


ll generateRandLong() {
	int i;
	ll answer = 0, j;

	for (i = 0, j = 1; i < N; i++, j *= 10) {

		if (i == N - 1)
			answer += 1 + rand() % 9 * j;
		else
			answer += rand() % 10 * j;
	}
	return answer;

}

struct HashNode {
	ll key;
	Data value;
	HashNode* next;
};


struct LinkedList {
	HashNode* head = NULL;
	HashNode* tail = NULL;

	void pushBack(Data aData, ll aKey) {
		HashNode* newNode = new HashNode();
		newNode->value = aData;
		newNode->key = aKey;
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

	bool popMiddle(ll aKey) {
		HashNode* tempNode;
		bool isFound = false;

		for (tempNode = head; tempNode != NULL; tempNode = tempNode -> next) {
			if (tempNode -> key == aKey) {
				isFound = true;
				break;
			}
		}

		if (isFound) {
			HashNode* tempNodePrev = head;

			if (tempNodePrev == tempNode) {
				head = head -> next;
				delete tempNode;
				return true;
			}

			while (tempNodePrev -> next != tempNode) 
				tempNodePrev = tempNodePrev -> next;

			if (tempNode == tail)
				tail = tempNodePrev;

			tempNodePrev -> next = tempNode -> next;
			tempNode -> next = NULL;
			delete tempNode;
		}
		return isFound;


	}
};


struct HashTable {
	int M = 8;
	int realSize = 0;
	const float loadFactor = 0.75;
	const int alpha = 2;
	LinkedList* bucketsArray = new LinkedList[M];


	ll hash(ll aKey) {
		int a = 9753, b = 10290;
		ll p = 9149658775000477;
		return ((a * aKey + b) % p) % M;
	}

	HashNode* find(ll aKey) {
		ll tempVal = hash(aKey);
		for (HashNode* tempNode = bucketsArray[tempVal].head; tempNode != NULL; tempNode = tempNode->next) {
			if (tempNode -> key == aKey)
				return tempNode;
		}
		return NULL;
	}


	void rehash() {
		M *= alpha;
		LinkedList* newArray = new LinkedList[M];

		for (int i = 0; i < M / alpha; i++) {

			for (HashNode* tempNode = bucketsArray[i].head; tempNode != NULL; tempNode = tempNode -> next) {

				ll tempVal = hash(tempNode -> key);
				newArray[tempVal].pushBack(tempNode -> value, tempNode -> key);
				delete tempNode;
			}
		}

		delete[] bucketsArray;

		bucketsArray = newArray;
	}


	void insert(ll aKey, Data aData) {
		ll temp = hash(aKey);
		if (find(aKey) != NULL) {
			bucketsArray[temp].popMiddle(aKey);
			realSize--;
		}
		bucketsArray[temp].pushBack(aData, aKey);
		realSize++;


		if (realSize * 1.0 / M > loadFactor) {
			rehash();
		}



	}

	void erase(ll aKey) {
		ll tempVal = hash(aKey);
		bool smth = bucketsArray[tempVal].popMiddle(aKey);
		if (smth) 
			realSize--;
	}

	int size() {
		return realSize;
	}

};

bool testHashTable() {
	 const int iters = 500000;
	 const int keysAmount = iters / 5;

	 // generate random keys:

	 long long* keys = new long long[keysAmount];
	 long long* keysToInsert = new long long[iters];
	 long long* keysToErase = new long long[iters];
	 long long* keysToFind = new long long[iters];

	 for (int i = 0; i < keysAmount; i++) {
	 	keys[i] = generateRandLong();
	 }

	 for (int i = 0; i < iters; i++) {
		 keysToInsert[i] = keys[generateRandLong() % keysAmount];
		 keysToErase[i] = keys[generateRandLong() % keysAmount];
		 keysToFind[i] = keys[generateRandLong() % keysAmount];
	 }
	 // test my HashTable:
	 HashTable hashTable;

	 clock_t myStart = clock();
	 for (int i = 0; i < iters; i++) {
	 	hashTable.insert(keysToInsert[i], Data());
	 }

	 int myInsertSize = hashTable.size();

	 for (int i = 0; i < iters; i++) {
	 	hashTable.erase(keysToErase[i]);
	 }
	 int myEraseSize = hashTable.size();
	 int myFoundAmount = 0;

	 for (int i = 0; i < iters; i++) {
		if (hashTable.find(keysToFind[i]) != NULL) {
		 	myFoundAmount++;
		}
	 }
	 clock_t myEnd = clock();
	 float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
	 // test STL hash table:

	 unordered_map<long long, Data> unorderedMap;
	 clock_t stlStart = clock();
	 for (int i = 0; i < iters; i++) {
	 	unorderedMap.insert({keysToInsert[i], Data()});
	 }
	 int stlInsertSize = unorderedMap.size();
	 for (int i = 0; i < iters; i++) {
	 	unorderedMap.erase(keysToErase[i]);
	 }
	 int stlEraseSize = unorderedMap.size();
	 int stlFoundAmount = 0;

	 for (int i = 0; i < iters; i++) {
		 if (unorderedMap.find(keysToFind[i]) != unorderedMap.end()) {
		 	stlFoundAmount++;
		 }
	 }
	 clock_t stlEnd = clock();
	 float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;

	 cout << "My HashTable:" << endl;
	 cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize <<
	", found amount: " << myFoundAmount << endl;
	 cout << "STL unordered_map:" << endl;
	 cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize 
	<< ", found amount: " << stlFoundAmount << endl << endl;
	 delete keys;
	 delete keysToInsert;
	 delete keysToErase;
	 delete keysToFind;

	 if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize && myFoundAmount == stlFoundAmount) {
	 	cout << "The lab is completed" << endl;
	 	return true;
	 }
	 cerr << ":(" << endl;
	 return false;
	}


int main() {
	srand(time(NULL));
	testHashTable();
	return 0;
}