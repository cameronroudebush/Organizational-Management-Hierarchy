#pragma once
#define TREENODEPTR TreeNode*
#define TREENULLPTR NULL
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class TreeNode {
public:
	string title;
	string name;
	TreeNode * parent;
	TreeNode * left;
	TreeNode * right;
	TreeNode(string newTitle, string newName) {
		title = newTitle;
		name = newName;
		left = TREENULLPTR;
		right = TREENULLPTR;
		parent = TREENULLPTR;
	}
};

class OrgTree {
public:
	TreeNode * head;
	int size = 0;
	OrgTree() {
		head = TREENULLPTR;
	}

	void addRoot(string newTitle, string newName) {
		if (!head) {
			//if the root is null then add a root
			head = new TreeNode(newTitle, newName);
		}
		else {
			//if the root isnt null add a new root and make the old root a left child of it
			head->parent = new TreeNode(newTitle, newName);
			head->parent->left = head;
			head = head->parent;
		}
		size++;
	}

	TREENODEPTR getRoot() {
		return head; //return the head or root
	}

	void printSubTree(TREENODEPTR subTreeRoot) {
		cout << subTreeRoot->title << ": " << subTreeRoot->name << endl; //prints root
		int counter = 1;
		printSubTreeRecursive(subTreeRoot->left, counter); //calls recursion to print everything

	}

	void hire(TREENODEPTR root, string newTitle, string newName) {
		TreeNode * current = root->left;
		if (!current) { //if the left value of the root is null just put it there
			current = new TreeNode(newTitle, newName);
			current->parent = root; //sets the parent of the new left
			root->left = current; //sets the left of the parent to the current
		}
		else {
			TreeNode * currentRight = current->right; //gotta navigate to the right until we find a null
			while (currentRight) {
				current = currentRight;
				currentRight = currentRight->right;

			}
			currentRight = new TreeNode(newTitle, newName); //once we find a null insert a new node there
			current->right = currentRight; //dont forget to set the previous left value to know where the new right is
			currentRight->parent = root;
		}
		size++;
	}

	TREENODEPTR find(string title) {
		if (head->title == title) { //if the head = the title than you found it! Way to go!
			return head; 
		}
		return findRecursive(head, title); // call the recursive method because its way easier
	}

	unsigned int getSize() {
		return size;
	}

	bool fire(string formerTitle) {
		if (head->title == formerTitle) { //if the head = the title than you cant fire the president
			return false;
		}
		TREENODEPTR toFire = find(formerTitle);
		if (!toFire) {
			return false; //if the person doesnt exist than we cant fire them
		}
		else {
			if (toFire->left) {
				TreeNode * currentRight = toFire->right; //gotta navigate to the right until we find a null
				while (currentRight) {
					currentRight = currentRight->right;

				}
				currentRight = toFire->left; //set the left child equal to its own node
				currentRight->parent = toFire->parent; //set the parent of that node to the parent of the one to delete
				toFire->right->right = currentRight; //set the node to the left of toFire rights value to the right of toFire
				TreeNode * replacement = toFire->parent->left; //used to know where we need to replace our toFire
				TreeNode * previous = toFire->parent->left; //used to keep track of the previous value
				while (replacement != toFire) { //navigate through until we find the value to delete
					previous = replacement;
					replacement = replacement->right;
				}
				previous->right = replacement->right; //set the previous right value to the replacement right so we can delete the toFire
				delete toFire;
				size--;
			}
		}
		return true;
	}

	TREENODEPTR leftMostChild(TREENODEPTR node) {
		if (!node || !node->left) { //if the node is null then return null
			return TREENULLPTR;
		}
		else {
			TreeNode * replacement = node; //iterates through to find the furthest left child and returns it
			while (replacement->left) {
				replacement = replacement->left;
			}
			return replacement;
		}
	}

	TREENODEPTR rightSibling(TREENODEPTR node) {
		if (!node || !node->right) { //if the node is null then return null
			return TREENULLPTR;
		}
		else {
			return node->right; // as long as there is something to the right return it!
		}
	}

	bool read(string fileName) {
		string title, name, junk;
		ifstream file;
		file.open(fileName);
		if (!file.is_open()) { //if the files isnt open then houston we've got a problem
			return false;
		}
		TREENODEPTR tree = 0;
		getline(file, title, ',');
		getline(file, name);
		addRoot(title, name); //add a root for the first found data
		tree = find(title);
		char done = 0;
		while (!file.eof()) { //as long as there is stuff in the file do things
			if (file.peek() == ')') { //if you find one of those empty it out and change where the tree is looking
				getline(file, junk);
				tree = tree->parent;
			}
			else {
				getline(file, title, ','); //hire a new person with the given data and then set the tree to them as a potential manager
				getline(file, name);
				hire(tree, title, name);
				tree = find(title);
			}
		}
		return true;
	}

	void write(string fileName) {
		string title, name;
		ofstream file;
		file.open(fileName);
		file << head->title << ", " << head->name << endl; //prints root
		writeRecursive(file, head->left); //calls a recursive write that is just like the print
		file << ")"; // tacks on that last one
		file.close();
	}

private:
	TREENODEPTR findRecursive(TREENODEPTR current, string title) {
		if (!current) {
			return TREENULLPTR; //base case
		}
		if (current->title == title) {
			return current; //found the title
		}
		else {
			TREENODEPTR returner = findRecursive(current->left, title); // call a recursive search on the left side
			if (returner) {
				return returner;
			}
			return findRecursive(current->right, title); // call a recursive search on the right side
		}
	}

	void printSubTreeRecursive(TREENODEPTR root, int count) {
		if (!root) {
			return; //base case
		}
		else {
			for (int i = 0; i < count; i++) {
				cout << "\t";
			}
			cout << root->title << ": " << root->name << endl; //prints out the current node
			count++;
			printSubTreeRecursive(root->left, count); //calls itself to the left
			count--;
			printSubTreeRecursive(root->right, count); //calls itself to the right
		}
	}

	void writeRecursive(ofstream &file, TREENODEPTR head) {
		if (!head) {
			return; //base case
		}
		else {
			file << head->title << ", " << head->name << endl; //prints out the current node
			writeRecursive(file, head->left); //calls itself to the left
			file << ")" << endl;
			writeRecursive(file, head->right); //calls itself to the right
		}
	}
};