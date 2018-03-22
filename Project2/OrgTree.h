#pragma once
#define TREENODEPTR TreeNode*
#define TREENULLPTR NULL
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/*Gotta fill the Tree with something! Why not some TreeNodes?*/
class TreeNode {
public:
	string title;
	string name;
	TreeNode * parent;
	TreeNode * left;
	TreeNode * right;
	//constructor
	TreeNode(string newTitle, string newName) {
		title = newTitle;
		name = newName;
		left = TREENULLPTR;
		right = TREENULLPTR;
		parent = TREENULLPTR;
	}
};

/*The requested class to hold the TreeNodes and make everything look pretty
	Size requirement per node: 104 bytes*/
class OrgTree {
public:
	TreeNode * head;
	int size;
	//Constructor
	OrgTree() {
		head = TREENULLPTR;
		size = 0;
	}

	/*Adds a root node to the tree or replaces the current one.
		Runtime: theta n*/
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

	/*Returns the pointer to the root of the tree as long there is one
		Runtime: theta n*/
	TREENODEPTR getRoot() {
		if (!head) {
			return TREENULLPTR;
		}
		return head; //return the head or root
	}

	/*Prints the entire subtree of a given root node
		Runtime: theta n*/
	void printSubTree(TREENODEPTR subTreeRoot) {
		if (subTreeRoot) { //checks to make sure the root isnt a null value
			cout << subTreeRoot->title << ": " << subTreeRoot->name << endl; //prints root
			int counter = 1;
			printSubTreeRecursive(subTreeRoot->left, counter); //calls recursion to print everything
		}
	}

	/*Adds a new hire under a given node or root
		Runtime: theta n*/
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

	/*Finds a person from there given title recursively
		Runtime: theta n*/
	TREENODEPTR find(string title) {
		if (head->title == title) { //if the head = the title than you found it! Way to go!
			return head;
		}
		return findRecursive(head, title); // call the recursive method because its way easier
	}

	/*Returns the size of the tree (how many people are in it)
		Runtime: theta 1*/
	unsigned int getSize() {
		return size;
	}

	/*Finds a person with a formerTitle and removes them from the tree then re orients the tree to replace them
		Runtime: theta n*/
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
				TreeNode * previous = toFire->parent->left; //used to keep track of the previous value
				while (currentRight) {
					currentRight = currentRight->right;

				}
				while (previous->right != toFire) {
					previous = previous->right;
				}
				currentRight = toFire->left; //set the left child equal to its own node
				currentRight->parent = toFire->parent; //set the parent of that node to the parent of the one to delete
				TreeNode * replacement = toFire->parent->left; //used to know where we need to replace our toFire
				if (replacement == toFire) {
					toFire->parent->left = previous;
				}
				else {
					previous->right = currentRight; //set the node to the left of toFire rights value to the right of toFire
				}
			}
			else {
				toFire->parent->left = TREENULLPTR;
			}
			delete toFire;
			size--;
			return true;
		}
	}

	/*Returns the left child of the given node
		Runtime: theta 2*/
	TREENODEPTR leftMostChild(TREENODEPTR node) {
		if (!node || !node->left) { //if the node is null then return null
			return TREENULLPTR;
		}
		else {
			return node->left; // as long as there is something to the left return it!
		}
	}

	/*Returns the right sibling of the given node
		Runtime: theta 2*/
	TREENODEPTR rightSibling(TREENODEPTR node) {
		if (!node || !node->right) { //if the node is null then return null
			return TREENULLPTR;
		}
		else {
			return node->right; // as long as there is something to the right return it!
		}
	}

	/*Reads in a tree from a given file
		Runtime: theta n*/
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

	/*Writes the tree to a given file recursively
		Runtime: theta n*/
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
	/*Recursion call for find from above
		Runtime: theta n*/
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

	/*Recursion call for the print function
		Runtime: theta n*/
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

	/*Recursion call for write function
		Runtime: theta n*/
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