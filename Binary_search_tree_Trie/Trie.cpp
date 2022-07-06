#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <queue>
#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#define ll long long

using namespace std;

struct Node {
	unordered_map<char, Node*> table;
	bool is_leaf;
	unordered_map<char, Node*>::iterator it;
	Node() {
		is_leaf = false;
	}
};

class Trie {
private:
	Node* root;
	void insert(Node* aRoot, string aWord) {
		Node* temp = aRoot;

		for (int i = 0; i < aWord.size(); i++) {
			if (temp -> table.find(aWord[i]) == temp -> table.end()) {
				temp -> table[aWord[i]] = new Node();
			}
			temp = temp -> table[aWord[i]];
		}
		temp -> is_leaf = true;

	}

	void iterate_through(Node* aRoot, string aWord) {
		Node* temp = aRoot;
		if (temp -> is_leaf)
			cout << aWord << endl;

		if (aRoot->table.empty()) {
			return;
		}
		unordered_map<char, Node*>::iterator it;
		for (it = temp->table.begin(); it != temp-> table.end(); it++) {
			aWord += it -> first;
			temp = it -> second;
			iterate_through(temp, aWord);
			aWord = aWord.substr(0, aWord.size() - 1);
		}
	}

	void deletion(Node* aRoot) {
		Node* temp = aRoot;
		delete temp;
		if (temp -> table.empty())
			return;
		unordered_map<char, Node*>::iterator it;
		for (it = temp->table.begin(); it != temp-> table.end(); it++) {
			temp = it -> second;
			deletion(temp);
		}
	}
	void find_by_prefix(Node* aRoot, string aWord) {
		Node* temp = aRoot;

		for (int i = 0; i < aWord.size(); i++) {
			if (temp -> table.find(aWord[i]) != temp -> table.end()) {
				temp = temp -> table[aWord[i]];
			}
			else {
				cout << "Words with this prefix are not found" << endl;
				return;
			}
		}
		iterate_through(temp, aWord);

	}
public:
	Trie() {
		root = new Node();
	}
	void insert(string aWord) {
		insert(root, aWord);
	}
	void find_by_prefix(string aWord) {
		find_by_prefix(root, aWord);
	}
	~Trie() {
		deletion(root);
	}

};

int main() {
	Trie tree;
	ifstream File;
	File.open("a.txt");
	while(!File.eof()) {
		string word;
		File >> word;
		tree.insert(word);
	}
	File.close();
	cout << "Enter the prefix: " << endl;
	string a;
	cin >> a;
	tree.find_by_prefix(a); 
	return 0;

}