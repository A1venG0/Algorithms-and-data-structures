#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <queue>
#include <algorithm>
#include <bits/stdc++.h>
#define N 12
#define ll long long

using namespace std;


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

struct Data {
	string nickname;
	int rank;
	int experience;
	int sum_of_donation;

	Data() {
		string all = "abcdefghijklmonpqrstuvwxyz";
		nickname = "";
		for (int i = 0; i < rand() % 10 + 1; i++) {
			nickname += all[rand() % 26 + 1]; 
		}
		rank = 1 + rand() % 15;
		experience = 1 + rand() % 50;
		sum_of_donation = 1 + rand() % 100;
	}

	Data (string aNick, int aRank, int aExp, int aSum) {
		nickname = aNick;
		rank = aRank;
		experience = aExp;
		sum_of_donation = aSum;
	}	
};

bool operator<(const Data& aPlayer1, const Data& aPlayer2) {

	if (aPlayer1.rank != aPlayer2.rank)
		return aPlayer1.rank < aPlayer2.rank;

	else if (aPlayer1.experience != aPlayer2.experience)
		return aPlayer1.experience < aPlayer2.experience;
	else if (aPlayer1.sum_of_donation != aPlayer2.sum_of_donation)
		return aPlayer1.sum_of_donation < aPlayer2.sum_of_donation;
	else
		return aPlayer1.nickname < aPlayer2.nickname;
}

bool operator==(const Data& aPlayer1, const Data& aPlayer2) {
	return (aPlayer1.rank == aPlayer2.rank && aPlayer1.experience == aPlayer2.experience && aPlayer1.sum_of_donation == aPlayer2.sum_of_donation && aPlayer1.nickname == aPlayer2.nickname);
}

bool operator<=(const Data& aPlayer1, const Data& aPlayer2) {

	return (aPlayer1 < aPlayer2 || aPlayer1 == aPlayer2);
}

struct Node {
	Data value;
	Node* left, *right;
};

class BinarySearchTree {
private:
	int treeSize;
	Node* root;
	vector<Data> range;

	Node* insert(Node* curNode, const Data& aPlayer) {
		if (curNode == NULL) {
			Node* newNode = new Node;
			newNode -> value = aPlayer;
			newNode -> left = newNode -> right = NULL;
			treeSize++;
			root = newNode;
			return newNode;
		}
		if (aPlayer < curNode -> value) {
			curNode -> left = insert(curNode -> left, aPlayer);
		}
		else if (curNode -> value < aPlayer) {
			curNode -> right = insert(curNode -> right, aPlayer);
		}

		return curNode;
	}

	Node* minimum(Node* aRoot) {
		if (aRoot -> left == NULL)
			return aRoot;
		return minimum(aRoot -> left);
	}

	Node* find(Node* aRoot, const Data& aPlayer) {
		if (aRoot == NULL || aRoot -> value == aPlayer)
			return aRoot;
		if (aPlayer < aRoot -> value)
			return find(aRoot -> left, aPlayer);

		return find(aRoot -> right, aPlayer);
	}

	Node* erase(Node* aRoot, const Data& aPlayer) {
		if (aRoot == NULL) {

			return aRoot;
		}
		if (aPlayer < aRoot -> value)
			aRoot -> left = erase(aRoot -> left, aPlayer);
		else if (aRoot -> value < aPlayer) {
			aRoot -> right = erase(aRoot -> right, aPlayer);
		}
		else if (aRoot -> left != NULL && aRoot -> right != NULL) {
			aRoot -> value = (minimum(aRoot -> right)) -> value;
			aRoot -> right = erase(aRoot -> right, aRoot -> value);	
		}
		else {

			if (aRoot -> left != NULL) {
				delete aRoot;
				aRoot = aRoot -> left;
			}

			else if (aRoot -> right != NULL) {
				delete aRoot;
				aRoot = aRoot -> right;
			}
			else {
				delete aRoot;
				aRoot = NULL;
			}
			treeSize--;
		}
		return aRoot;
	}

	void print(Node* aRoot) {
		if (aRoot != NULL) {
			print(aRoot -> left);
			cout << "Nickname: " << aRoot -> value.nickname << endl;
			cout << "Rank: " << aRoot -> value.rank << endl;
			cout << "Experience: " << aRoot -> value.experience << endl;
			cout << "Donation: " << aRoot -> value.sum_of_donation << endl;
			cout << "-----------------------------" << endl;
			print(aRoot -> right);
		}
	}

	int height(Node* aRoot) {
		if (aRoot == NULL)
			return 0;

		int left = height(aRoot -> left);
		int right = height(aRoot -> right);

		if (left > right)
			return left + 1;
		else
			return right + 1;
	}

	void findInRange(Data minObj, Data maxObj, Node* aRoot, vector<Data> &aVec) {
		if (aRoot == NULL)
			return;

		if (aRoot -> value < minObj)
			return findInRange(minObj, maxObj, aRoot -> right, aVec);

		if (minObj <= aRoot -> value && aRoot -> value <= maxObj) {
			aVec.push_back(aRoot -> value);
			findInRange(minObj, maxObj, aRoot -> left, aVec);
			findInRange(minObj, maxObj, aRoot -> right, aVec);
		}
		if (maxObj < aRoot -> value)
			return findInRange(minObj, maxObj, aRoot -> left, aVec);
	}

	void findInRange(Data minObj, Data maxObj, Node* aRoot, int& counter) {
		if (aRoot == NULL)
			return;

		if (aRoot -> value < minObj)
			return findInRange(minObj, maxObj, aRoot -> right, counter);

		if (minObj <= aRoot -> value && aRoot -> value <= maxObj) {
			counter++;
			findInRange(minObj, maxObj, aRoot -> left, counter);
			findInRange(minObj, maxObj, aRoot -> right, counter);
		}
		if (maxObj < aRoot -> value)
			return findInRange(minObj, maxObj, aRoot -> left, counter);
	}

	void clear(Node* aRoot) {
		if (aRoot != NULL) {
			clear(aRoot -> left);
			delete aRoot;
			clear(aRoot -> right);
		}
	}
	
public:

	BinarySearchTree() {
		treeSize = 0;
		root = NULL;
	}
	~BinarySearchTree() {
		clear(root);
		range.clear();
	}

	void insert(const Data& aPlayer) {
		root = insert(root, aPlayer);
	}
	void minimum() {
		minimum(root);
	}
	bool find(const Data& aPlayer) {
		return find(root, aPlayer);
	}

	void erase(const Data& aPlayer) {
		erase(root, aPlayer);
	}

	int size() {
		return treeSize;
	}
	void print() {
		print(root);
	}

	int height() {
		return height(root);
	}

	int findInRange(Data minObj, Data maxObj) {
		int count = 0;
		findInRange(minObj, maxObj, root, count);
		return count;
	}
};

bool testBinarySearchTree()
{
    srand(time(NULL));

    const int iters = 80000;
    const int keysAmount = iters * 2;
    const int itersToRangeQueries = 1000;

    vector<Data> data(keysAmount);

    vector<Data> dataToInsert(iters);
    vector<Data> dataToErase(iters);
    vector<Data> dataToFind(iters);
    vector<pair<Data, Data>> dataToRangeQueries;

    for (int i = 0; i < iters; i++)
    {
        dataToInsert[i] = data[generateRandLong() % keysAmount];
        dataToErase[i] = data[generateRandLong() % keysAmount];
        dataToFind[i] = data[generateRandLong() % keysAmount];
    }

    for (int i = 0; i < itersToRangeQueries; i++)
    {
        Data minData = Data();
        Data maxData = Data();

        if (maxData < minData)
        {
            swap(minData, maxData);
        }
        dataToRangeQueries.push_back({minData, maxData});
    }

    BinarySearchTree myTree;
    clock_t myStart = clock();
    for (int i = 0; i < iters; i++)
    {
        myTree.insert(dataToInsert[i]);
    }
    int myInsertSize = myTree.size();
    int myTreeHeight = myTree.height();
    int optimalTreeHeight = log2(myInsertSize) + 1;
    for (int i = 0; i < iters; i++)
    {
        myTree.erase(dataToErase[i]);
    }
    int myEraseSize = myInsertSize - myTree.size();
    int myFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (myTree.find(dataToFind[i]))
        {
            myFoundAmount++;
        }
    }
    clock_t myEnd = clock();
    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;

    set<Data> stlTree;
    clock_t stlStart = clock();
    for (int i = 0; i < iters; i++)
    {
        stlTree.insert(dataToInsert[i]);
    }
    int stlInsertSize = stlTree.size();
    for (int i = 0; i < iters; i++)
    {
        stlTree.erase(dataToErase[i]);
    }
    int stlEraseSize = stlInsertSize - stlTree.size();
    int stlFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (stlTree.find(dataToFind[i]) != stlTree.end())
        {
            stlFoundAmount++;
        }
    }
    clock_t stlEnd = clock();
    float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;

    clock_t myRangeStart = clock();
    int myRangeFoundAmount = 0;
    for (int i = 0; i < itersToRangeQueries; i++)
    {
        myRangeFoundAmount += myTree.findInRange(dataToRangeQueries[i].first, dataToRangeQueries[i].second);
    }
    clock_t myRangeEnd = clock();
    float myRangeTime = (float(myRangeEnd - myRangeStart)) / CLOCKS_PER_SEC;

    clock_t stlRangeStart = clock();
    int stlRangeFoundAmount = 0;
    for (int i = 0; i < itersToRangeQueries; i++)
    {
        const auto& low = stlTree.lower_bound(dataToRangeQueries[i].first);
        const auto& up = stlTree.upper_bound(dataToRangeQueries[i].second);
        stlRangeFoundAmount += distance(low, up);
    }
    clock_t stlRangeEnd = clock();
    float stlRangeTime = (float(stlRangeEnd - stlRangeStart)) / CLOCKS_PER_SEC;

    cout << "My BinaryTree: height = " << myTreeHeight << ", optimal height = " << optimalTreeHeight << endl;
    cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize << ", found amount: " << myFoundAmount << endl;
    cout << "Range time: " << myRangeTime << ", range found amount: " << myRangeFoundAmount << endl << endl;
    cout << "STL Tree:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize << ", found amount: " << stlFoundAmount << endl;
    cout << "Range time: " << stlRangeTime << ", range found amount: " << stlRangeFoundAmount << endl << endl;

    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize &&
        myFoundAmount == stlFoundAmount && myRangeFoundAmount == stlRangeFoundAmount)
    {
        cout << "The lab is completed" << endl;
        return true;
    }

    cerr << ":(" << endl;
    return false;
}

int main() {
	srand(time(NULL));
	//testBinarySearchTree();
	/*BinarySearchTree tree;
	Data el1 = Data();
	Data el2 = Data();
	Data el3 = Data();
	Data el4 = Data();
	Data el5 = Data();
	cout << "el1 " << el1.rank << " el2 " << el2.rank << " el3 " << el3.rank << " el4 " << el4.rank << " el5 " << el5.rank << endl;
	tree.insert(el1);
	tree.insert(el2);
	tree.insert(el3);
	tree.insert(el4);
	tree.insert(el5);

	cout << tree.height();*/
	return 0;
}