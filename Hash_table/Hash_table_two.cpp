#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>
#include <cstring>
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

struct Node {
	ll key;
	Data value;
};

struct HashTable {
	int M = 5000000;
	int realSize = 0;
	const int loadFactor = 0.75;
	const int alpha = 2;
	bool* deleted = new bool[M];
	Node* bucketsArray = new Node[M];


	int hash1(ll aKey) {
		return (aKey % M);
	}

	int hash2(ll aKey) {
		return aKey % (M - 1) + 1;
	}

	HashTable() {
		for (int i = 0; i < M; i++) {
            bucketsArray[i].key = -1;
            deleted[i] = false;
		}

	}

	/*void rehash() {
		M *= alpha;
		Node* newArray = new Node[M];
		bool* newDeleted = new bool[M];

		for (int i = 0; i < M; i++) {
			newArray[i].key = -1;
			newDeleted[i] = false;
		}

		for (int i = 0; i < M / alpha; i++) {

			int x = hash1(bucketsArray[i].key);
			int y = hash2(bucketsArray[i].key);

			if (bucketsArray[i].key != -1 && !deleted[i]) {

				for (int j = 0; j < M; j++) {

					if (newArray[x].key == -1 || newDeleted[x]) {

						newArray[x].key = bucketsArray[i].key;
						newArray[x].value = bucketsArray[i].value;

						newDeleted[x] = false;
						break;
					}
					x = (x + j * y) % M;
				}
			}

		}
		delete[] bucketsArray;
		delete[] deleted;
		deleted = newDeleted;
		bucketsArray = newArray;

	}*/


	void insert(ll aKey, Data aData) {
		
		//if (realSize * 1.0 / M > loadFactor)
			//rehash();

		if (find(aKey) != NULL) {
			erase(aKey);
		}
		int x = hash1(aKey);
		int y = hash2(aKey);

		for (int i = 0; i < M; i++) {

			if (bucketsArray[x].key == -1 || deleted[x]) {

				bucketsArray[x].key = aKey;
				bucketsArray[x].value = aData;

				deleted[x] = false;
				realSize++;
				return;
			}
			x = (x + i * y) % M;
		}


	}


	Node* find(ll aKey) {
		int x = hash1(aKey);
		int y = hash2(aKey);
		for (int i = 0; i < M; i++) {
			if (bucketsArray[x].key != -1) {
				if (bucketsArray[x].key == aKey && !deleted[x])
					return &bucketsArray[x];
			}
			else
				return NULL;
			x = (x + i * y) % M;
		}
		return NULL;
	}


	void erase(ll aKey) {
		if (find(aKey) != NULL) {
			int x = hash1(aKey);
			int y = hash2(aKey);

			for (int i = 0; i < M; i++) {

				if (bucketsArray[x].key != -1) {

					if (bucketsArray[x].key == aKey && !deleted[x]) {
						deleted[x] = true;
						realSize--;
					}
				}
				else
					return;
				x = (x + i * y) % M;
			}

		}
	}

	int size() {
		return realSize;
	}

};

bool testHashTable() {
	 const int iters = 500000;
	 const int keysAmount = iters * 1;

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

	/*HashTable somethinggg;

	ll num1 = generateRandLong();
	ll num2 = generateRandLong();
	somethinggg.insert(num1, Data());
	somethinggg.insert(num2, Data());
	somethinggg.erase(num1);

	for (int i = 0; i < somethinggg.M; i++) {
		cout << i << endl;
		if ((somethinggg.bucketsArray[i].key != -1) && somethinggg.deleted[i] == false) {
			cout << "address: " << somethinggg.bucketsArray[i].value.address << endl;
			cout << "area: " << somethinggg.bucketsArray[i].value.area << endl;
			cout << "isHeated: " << boolalpha << somethinggg.bucketsArray[i].value.isHeated << endl;
			cout << "Key: " << somethinggg.bucketsArray[i].key << endl;
			cout << endl;
		}
	}
	cout << somethinggg.size() << endl;*/
	testHashTable();
	return 0;
}