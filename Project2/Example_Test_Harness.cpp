#include "stdafx.h"
#include "Orgtree.h"
#include <string>
#include <iostream>
using namespace std;

// This is not the complete test harness/driver for project 2, but
// is a good starting point.  You should test your project completely
// by adding additional tests for each item in the grading rubric!

int main() {
	OrgTree o1, o2, o3;
	
	// Adding roots should make a linear tree
	cout << "Adding Roots test" << endl;
	o1.addRoot("VP Sales", "Mark Zuckerberg");
	o1.addRoot("Director of Marketing", "George Lucas");
	o1.addRoot("Digital Media Specialist", "Al Gore");
	o1.printSubTree(o1.getRoot()); //printSubTree from root
	cout << endl;

	cout << "Hire test" << endl;
	o1.hire(o1.getRoot(), "Director of Public Relations", "Kurt Vonnegut");
	o1.printSubTree(o1.getRoot());
	cout << endl;

	cout << "Find test" << endl;
	cout << o1.find("Digital Media Specialist")->name << endl;
	cout << o1.find("Director of Marketing")->name << endl;
	cout << o1.find("Director of Public Relations")->name << endl;
	cout << endl;
	
	//add two children to root
	cout << "Adding children to root test" << endl;
	o1.hire(o1.getRoot(), "R3C1", "R3C1");
	o1.hire(o1.getRoot(), "R3C2", "R3C2");
	o1.printSubTree(o1.getRoot());
	cout << endl;
	
	cout << "Find and hire off of test" << endl;
	o1.hire(o1.find("R3C1"), "R3C1C1", "R3C1C1");//test find on leaf node and hire to it
	o1.printSubTree(o1.getRoot());
	cout << endl;
	
	cout << "Size test" << endl;
	cout << o1.getSize() << endl;
	o1.printSubTree(o1.getRoot()); //printSubTree from root
	cout << endl;	   

	cout << "Fire test" << endl;
	o1.fire("R3C1"); //fire an internal node
	cout << o1.getSize() << endl;
	o1.printSubTree(o1.getRoot());
	cout << endl;

	cout << "Left most child test" << endl;
	cout << o1.leftMostChild(o1.getRoot())->name << endl;
	cout << o1.leftMostChild(o1.find("Director of Marketing"))->name << endl; //if it returns a TREENULLPTR value cout wont know how to print it
	cout << endl;

	cout << "Right sibling test" << endl;
	cout << o1.rightSibling(o1.find("Director of Marketing"))->name << endl;
	cout << endl;
	
	cout << "Copying down his exact tree and writing it to a file" << endl;
	// Write out a tree and read it back in to a new tree, then print
	o2.addRoot("President", "George Orwell");
	o2.hire(o2.find("President"), "VP Sales", "Mark Zuckerberg");
	o2.hire(o2.find("VP Sales"), "Director of Marketing", "George Lucas");
	o2.hire(o2.find("Director of Marketing"), "Digital Media Specialist", "Al Gore");
	o2.hire(o2.find("Director of Marketing"), "Head of Television and Print Advertising", "George Martin");
	o2.hire(o2.find("VP Sales"), "Director of Public Relations", "Kurt Vonnegut");
	o2.hire(o2.find("President"), "VP Operations", "Bill Gates");
	o2.hire(o2.find("President"), "VP Software Development", "Ayn Rand");
	o2.hire(o2.find("VP Software Development"), "MagicBag Team Leader", "Wil Wheaton");
	o2.hire(o2.find("MagicBag Team Leader"), "Software Engineer I", "Donald Knuth");
	o2.hire(o2.find("MagicBag Team Leader"), "Software Engineer II", "Marvin Minsky");
	o2.hire(o2.find("VP Software Development"), "Cloud Development", "Bob Ross");
	o2.printSubTree(o2.getRoot());
	o2.write("output.txt");
	cout << endl;

	cout << "Reading his given tree" << endl;
	o3.read("output.txt");
	o3.printSubTree(o3.getRoot()); //printSubTree from root

	system("PAUSE");
	return 0;
}