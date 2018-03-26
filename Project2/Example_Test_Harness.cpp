#include "stdafx.h"
#include "Orgtree.h"
#include <string>
#include <iostream>
using namespace std;

// This is not the complete test harness/driver for project 2, but
// is a good starting point.  You should test your project completely
// by adding additional tests for each item in the grading rubric!

int main() {
	OrgTree o1, o2, o3, o4, o5;
	o1.addRoot("President", "George Orwell");
	o1.hire(o1.find("President"), "VP Sales", "Mark Zuckerberg");
	o1.hire(o1.find("VP Sales"), "Director of Marketing", "George Lucas");
	o1.hire(o1.find("Director of Marketing"), "Digital Media Specialist", "Al Gore");
	o1.hire(o1.find("Director of Marketing"), "Head of Television and Print Advertising", "George Martin");
	o1.hire(o1.find("VP Sales"), "Director of Public Relations", "Kurt Vonnegut");
	o1.hire(o1.find("President"), "VP Operations", "Bill Gates");
	o1.hire(o1.find("President"), "VP Software Development", "Ayn Rand");
	o1.hire(o1.find("VP Software Development"), "MagicBag Team Leader", "Wil Wheaton");
	o1.hire(o1.find("MagicBag Team Leader"), "Software Engineer I", "Donald Knuth");
	o1.hire(o1.find("MagicBag Team Leader"), "Software Engineer II", "Marvin Minsky");
	o1.hire(o1.find("VP Software Development"), "Cloud Development", "Bob Ross");
	o1.printSubTree(o1.getRoot());
	cout << o1.getSize() << endl;

	//add root test
	o1.addRoot("Test New Root", "Test1");
	o1.printSubTree(o1.getRoot());
	cout << o1.getSize() << endl;

	cout << endl;
	//get root test
	cout << o1.getRoot() << endl;
	cout << o2.getRoot() << endl; 

	cout << endl;
	//leftMostChild test
	cout << o1.leftMostChild(o1.getRoot())->name << endl;
	cout << o1.leftMostChild(o1.find("VP Software Development"))->name << endl;
	cout << o2.leftMostChild(o2.getRoot()) << endl;

	cout << endl;
	//rightySibling Test
	cout << o1.rightSibling(o1.getRoot()) << endl;
	cout << o1.rightSibling(o1.find("VP Software Development")) << endl;
	cout << o1.rightSibling(o1.find("VP Operations"))->name << endl;
	cout << o1.rightSibling(o2.getRoot()) << endl;

	cout << endl;
	//print Test
	o1.printSubTree(o1.getRoot());
	o1.printSubTree(o1.find("VP Operations"));

	cout << endl;
	//read Test
	cout << o2.read("shenanigans.txt") << endl;
	cout << o2.read("output.txt") << endl;
	o2.printSubTree(o2.getRoot());
	
	cout << endl;
	//write Test
	o1.write("test2.txt");
	o3.read("test2.txt");
	o3.printSubTree(o3.getRoot());

	cout << endl;
	//hire Test
	o3.hire(o3.getRoot(), "hireTester", "John Doe");
	o3.hire(o3.find("Software Engineer II"), "hireTester2", "Jane Doe");
	o3.printSubTree(o3.getRoot());
	o3.write("test2.txt");
	o4.read("test2.txt");
	o4.printSubTree(o4.getRoot());

	cout << endl;
	//fire Test
	cout << o3.fire("I dont exist") << endl;
	cout << o3.fire("hireTester2") << endl;
	o3.printSubTree(o3.getRoot());
	cout << o3.fire("Test New Root") << endl;
	cout << o3.fire("VP Software Development") << endl;
	o3.printSubTree(o3.getRoot());

	cout << endl;
	//another read Test
	cout << o5.read("test3.txt") << endl;
	o5.printSubTree(o5.getRoot());
	system("PAUSE");
	return 0;
}