#include <iostream>
#include <sstream>
#include "AVL.h"

/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

bool validName(string name) {

	name.erase(0, 1);
	name.pop_back();

	int nameCount = 0;

	for (int i = 0; i < name.length(); i++) {
		for (int j = 65; j <= 122; j++) {

			if (name[i] == char(j) || name[i] == ' ') {
				nameCount++;
			}

			if (nameCount == name.length()) {
				return true;
			}
		}
	}

	cout << "unsuccessful" << endl;
	return false;
}

bool validID(string ID) {

	int IDCount = 0;

	if (ID.length() != 8) {
		cout << "unsuccessful" << endl;
		return false;
	}

	for (int i = 0; i < ID.length(); i++) {
		for (int j = 48; j <= 57; j++) {

			if (ID[i] == char(j)) {
				IDCount++;
			}
			if (IDCount == ID.length()) {
				return true;
			}
		}

	}

	cout << "unsuccessful" << endl;
	return false;
}

Student makeStudent(string name, string _ID) {

	int ID = stoi(_ID);
	return Student(name, ID);
}

int main() {

	AVL tree;

	string _run;
	cin >> _run;
	int run = stoi(_run);

	for (int i = 0; i <= run; i++) {

		string line;
		getline(cin, line);

		istringstream in(line);

		string command;
		in >> command;

		if (command == "insert") {
			string name;
			in >> name;
			string ID;
			in >> ID;

			if (validName(name) && validID(ID)) {

				name.erase(0, 1);
				name.pop_back();
				tree.insert(makeStudent(name, ID));
			}
		}
		else if (command == "remove") {
			string next;
			in >> next;
			if (validID(next)) {
				tree.remove(stoi(next));
			}
		}
		else if (command == "search") {
			string next;
			in >> next;
			if (next[0] == '"') {
				next.erase(0, 1);
				next.pop_back();
				tree.searchName(next);
			}
			else {
				tree.searchID(stoi(next));
			}
		}
		else if (command == "printInorder") {
			tree.printInorder();
		}
		else if (command == "printPreorder") {
			tree.printPreorder();
		}
		else if (command == "printPostorder") {
			tree.printPostorder();
		}
		else if (command == "printLevelCount") {
			tree.printLevelCount();
		}
		else if (command == "removeInorder") {
			string next;
			in >> next;
			tree.removeInorder(stoi(next));
		}
		else {
			if (command != "") {
				cout << "unsuccessful" << endl;
			}
		}
	}

	return 0;
}
