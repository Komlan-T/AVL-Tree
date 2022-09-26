#include <iostream>
#include <string>
#include "AVL.h"

/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

bool validStudent(string name, string ID){

	int j = 65;
	int k = 48;
	int nameCount = 0;
	int IDCount = 0;

	if(ID.length() != 8){
		return false;
	}

	for(int i = 0; i < name.length(); i++){
		while(j <= 122){
			if(name[i] == char(j) || name[i] == char(32)){
				nameCount++;
			}
			j++;
		}
	}

	for(int i = 0; i < ID.length(); i++){
		while(k <= 57){
			if(ID[i] == char(k)){
				IDCount++;
			}
			k++;
		}
	}
	
	if(IDCount == ID.length() && nameCount == name.length()){
		return true;
	}
	cout << "unsuccessful" << endl;
	return false;
}

Student makeStudent(string name, string _ID){

	int ID = stoi(_ID);
	return Student(name, ID);
}

int main() {

	AVL tree;
	tree.insert(makeStudent("Adam Stewart", "23847510"));
	//tree.insert(makeStudent("Faith Goodwin", "47103842"));
	//tree.insert(makeStudent("John Proctor", "35268629"));
	return 0;
}

