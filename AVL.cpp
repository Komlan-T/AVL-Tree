#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Student {
	string name;
	int ID;

	Student() {
		name = "Name";
		ID = 12345678;
	}
	Student(string name, int ID) {
		this->name = name;
		this->ID = ID;
	}
};

struct AVL {
	struct Node {
		Student student;
		Node* left;
		Node* right;
		int height;

		Node(Student student) {
			this->student = student;
			left = nullptr;
			right = nullptr;
			height = 0;
		}
	};

	Node* _root;
	int nodeCount;

	/*==== Construction / Destruction ====*/
	AVL();
	~AVL();
	void destruct(Node* root);

	/*==== Insertion / Deletion ====*/
	Node* insert_Helper(Node* root, Student student);
	Node* remove_Helper(Node* root, int ID);
	void insert(Student student);
	void remove(int ID);
	void removeInOrder_Helper(int N, int& increment, Node* root);
	void removeInorder(int N);


	/*==== Search ====*/
	Node* searchName_Helper(Node* root, string name);
	Node* searchID_Helper(Node* root, int ID);
	void searchID(int ID);
	void searchName(string name);
	bool nameExist(Node* root, string name);
	bool IDExist(Node* root, int ID);

	/*==== Behaviors ====*/
	int findHeight(Node* node);
	Node* rotateLeft(Node* node);
	Node* rotateRight(Node* node);
	Node* findLeftMost(Node* node);
	void printPreOrder_Helper(Node* root, vector<string>& names);
	void printPreorder();
	void printInOrder_Helper(Node* root, vector<string>& names);
	void printInorder();
	void printPostOrder_Helper(Node* root, vector<string>& names);
	void printPostorder();
	void printLevelCount();
};

AVL::AVL() {
	_root = nullptr;
	nodeCount = 0;
};

void AVL::destruct(Node* root)
{
	if (root->left) {
		destruct(root->left);
	}
	if (root->right) {
		destruct(root->right);
	}
	delete root;
}

AVL::~AVL() {

	destruct(_root);
}

int AVL::findHeight(Node* node) {

	if (node == nullptr) {
		return 0;
	}
	else {
		return 1 + max(findHeight(node->left), findHeight(node->right));
	}
}

bool AVL::nameExist(Node* root, string name) {

	queue<Node*> nodes;

	if (root != nullptr) {
		nodes.push(root);
	}

	while (!nodes.empty()) {

		if (nodes.front()->left != nullptr) {
			nodes.push(nodes.front()->left);
		}
		if (nodes.front()->right != nullptr) {
			nodes.push(nodes.front()->right);
		}

		if (nodes.front()->student.name == name) {
			return true;
		}
		nodes.pop();
	}
	return false;
}

bool AVL::IDExist(Node* root, int ID) {

	queue<Node*> nodes;

	if (root != nullptr) {
		nodes.push(root);
	}

	while (!nodes.empty()) {

		if (nodes.front()->left != nullptr) {
			nodes.push(nodes.front()->left);
		}
		if (nodes.front()->right != nullptr) {
			nodes.push(nodes.front()->right);
		}

		if (nodes.front()->student.ID == ID) {
			return true;
		}
		nodes.pop();
	}
	return false;
}

AVL::Node* AVL::rotateLeft(Node* node) {

	Node* grandchild = node->right->left;
	Node* newParent = node->right;
	newParent->left = node;
	node->right = grandchild;
	return newParent;
}

AVL::Node* AVL::rotateRight(Node* node) {

	Node* grandchild = node->left->right;
	Node* newParent = node->left;
	newParent->right = node;
	node->left = grandchild;
	return newParent;
}

/*Add a Student object into the tree with the specified name, NAME and GatorID number, ID.
Balance the tree automatically if necessary.
The ID must be unique.
The ID and NAME must satisfy the constraints stated below.
Also, prints “successful” if insertion is successful and prints “unsuccessful” otherwise.
NAME identifier will be separated by double inverted commas for parsing, e.g. "Josh Smith".*/

AVL::Node* AVL::insert_Helper(Node* root, Student student) {

	if (IDExist(_root, student.ID) == false) {
		if (root == nullptr) {
			cout << "successful" << endl;
			nodeCount++;
			return new Node(student);
		}
		else if (student.ID < root->student.ID) {
			root->left = insert_Helper(root->left, student);
		}
		else if (student.ID > root->student.ID) {
			root->right = insert_Helper(root->right, student);
		}

		//subtree is right heavy
		if (findHeight(root->left) - findHeight(root->right) < -1) {
			//subtree's right is left heavy
			if (findHeight(root->right->left) - findHeight(root->right->right) > 0) {
				//right left rotation & update height
				root->right = rotateRight(root->right);
				root = rotateLeft(root);
				root->height = findHeight(root);
			}
			else {
				//left rotation & update height
				root = rotateLeft(root);
				root->height = findHeight(root);
			}
		}
		//subtree is left heavy
		if (findHeight(root->left) - findHeight(root->right) > 1) {
			//subtree's left is right heavy
			if (findHeight(root->left->left) - findHeight(root->left->right) < 0) {
				//left right rotation & update height
				root->left = rotateLeft(root->left);
				root = rotateRight(root);
				root->height = findHeight(root);
			}
			else {
				//right rotation & update height
				root = rotateRight(root);
				root->height = findHeight(root);
			}
		}
	}
	else {
		cout << "unsuccessful" << endl;
	}
	return root;
}

void AVL::insert(Student student) {

	_root = insert_Helper(_root, student);
}

AVL::Node* AVL::findLeftMost(Node* node) {

	while (node->left != nullptr) {
		node = node->left;
	}
	return node;
}

/*Find and remove the account with the specified ID from the tree.
[Optional: Balance the tree automatically if necessary. We will test your code only on cases where the tree will be balanced before and after the deletion. So you can implement a BST deletion and still get full credit]
If deletion is successful, print “successful”.
If the ID does not exist within the tree, print “unsuccessful”.
You must prioritize replacing a removed node with its inorder successor for the case where the deleted node has two children.*/

AVL::Node* AVL::remove_Helper(Node* root, int ID) {

	if (IDExist(_root, ID)) {
		if(root == nullptr){
			return nullptr;
		}
		if(ID < root->student.ID){
			root->left = remove_Helper(root->left, ID);
		}
		else if(ID > root->student.ID){
			root->right = remove_Helper(root->right, ID);
		}
		else if(ID == root->student.ID){
			if(root->left == nullptr && root->right == nullptr){
				nodeCount--;
				cout << "successful" << endl;
				return nullptr;
			}
			else if((root->left != nullptr && root->right == nullptr) || (root->left == nullptr && root->right != nullptr)){
				if(root->left == nullptr){
					Node* temp = root->right;
					delete root;
					nodeCount--;
					cout << "successful" << endl;
					return temp;
				}
				else if(root->right == nullptr){
					Node* temp = root->left;
					delete root;
					nodeCount--;
					cout << "successful" << endl;
					return temp;
				}	
			}
			else if(root->left != nullptr && root->right != nullptr){
				Node* successor = findLeftMost(root->right);
				root->student.name = successor->student.name;
				root->student.ID = successor->student.ID;
				root->right = remove_Helper(root->right, successor->student.ID);
				return root;
			}
		}
	}
	else {
		cout << "unsuccessful" << endl;
	}
	return root;
}


void AVL::remove(int ID) {

	_root = remove_Helper(_root, ID);
}

void AVL::removeInOrder_Helper(int N, int& increment, Node* root) {

	if (N < 0 || N > nodeCount) {
		cout << "unsuccessful" << endl;
		return;
	}
	if (root == nullptr) {
		return;
	}
	else {
		removeInOrder_Helper(N, increment, root->left);
		if (root->left == nullptr) {
			increment++;
		}
		if (increment == N) {
			remove(root->student.ID);
			increment++;
			return;
		}
		removeInOrder_Helper(N, increment, root->right);
		if (root->right == nullptr) {
			increment++;
		}
	}
}

void AVL::removeInorder(int N) {

	int increment = -1;
	removeInOrder_Helper(N, increment, _root);
}

/*Search for the student with the specified ID from the tree.
If the ID was found, print out their NAME.
If the ID does not exist within the tree, print “unsuccessful”.*/

AVL::Node* AVL::searchID_Helper(Node* root, int ID) {

	if (root == nullptr) {
		cout << "unsuccessful" << endl;
		return nullptr;
	}
	else {
		if (root->student.ID == ID) {
			cout << root->student.name << endl;
			return root;
		}
		else if (ID < root->student.ID) {
			root->left = searchID_Helper(root->left, ID);
		}
		else if (ID > root->student.ID) {
			root->right = searchID_Helper(root->right, ID);
		}
	}
	return nullptr;
}

void AVL::searchID(int ID) {

	Node* temp = searchID_Helper(_root, ID);
}

/*Search for the student with the specified name, NAME in the tree.
If the student name was found, print the associated ID.
If the tree has more than one object with the same NAME, print each ID on a new line with no other spaces and in the same relative order as a pre-order traversal.
If the name does not exist within the tree, print “unsuccessful”.
NAME identifier will be surrounded by double quotes for parsing, e.g. "Josh Smith".*/

AVL::Node* AVL::searchName_Helper(Node* root, string name) {

	if (nameExist(_root, name)) {
		if (root == nullptr) {
			return nullptr;
		}
		else {
			if (root->student.name == name) {
				cout << root->student.ID << endl;
				return root;
			}
			root->left = searchName_Helper(root->left, name);
			root->right = searchName_Helper(root->right, name);
		}
	}
	else {
		cout << "unsuccessful" << endl;
	}
	return nullptr;
}

void AVL::searchName(string name) {

	Node* temp = searchName_Helper(_root, name);
}

/*Print out a comma separated preorder traversal of the names in the tree.*/

void AVL::printPreOrder_Helper(Node* root, vector<string>& names) {

	if (root == nullptr) {
		return;
	}
	else {
		names.push_back(root->student.name);
		names.push_back(", ");
		printPreOrder_Helper(root->left, names);
		printPreOrder_Helper(root->right, names);
	}
}

void AVL::printPreorder() {

	vector<string> names;
	printPreOrder_Helper(_root, names);
	for (int i = 0; i < names.size() - 1; i++) {
		cout << names[i];
	}
	cout << endl;
}

/*Print out a comma separated inorder traversal of the names in the tree.*/

void AVL::printInOrder_Helper(Node* root, vector<string>& names) {

	if (root == nullptr) {
		return;
	}
	else {
		printInOrder_Helper(root->left, names);
		names.push_back(root->student.name);
		names.push_back(", ");
		printInOrder_Helper(root->right, names);
	}
}

void AVL::printInorder() {

	vector<string> names;
	printInOrder_Helper(_root, names);
	for (int i = 0; i < names.size() - 1; i++) {
		cout << names[i];
	}
	cout << endl;
}

/*Print out a comma separated postorder traversal of the names in the tree.*/

void AVL::printPostOrder_Helper(Node* root, vector<string>& names) {

	if (root == nullptr) {
		return;
	}
	else {
		printPostOrder_Helper(root->left, names);
		printPostOrder_Helper(root->right, names);
		names.push_back(root->student.name);
		names.push_back(", ");
	}
}

void AVL::printPostorder() {

	vector<string> names;
	printPostOrder_Helper(_root, names);
	for (int i = 0; i < names.size() - 1; i++) {
		cout << names[i];
	}
	cout << endl;
}

/*Prints the number of levels that exist in the tree.
Prints 0 if the head of the tree is null. For example, the tree in Fig. 1 has 4 levels.*/

void AVL::printLevelCount() {
	
	cout << findHeight(_root) << endl;
}
