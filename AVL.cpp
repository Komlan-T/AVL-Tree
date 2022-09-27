#include <iostream>
#include <vector>
#include <queue>
#include <string>
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

	/*==== Construction / Destruction ====*/
	AVL();
	//~AVL();
	//void destruct(Node* root);

	/*==== Insertion / Deletion ====*/
	Node* insertHelper(Node* root, Student student);
	void insert(Student student);

	/*==== Search ====*/
	Node* searchName_Helper(Node* root, string name);
	Node* searchID_Helper(Node* root, int ID);
    void searchID(int ID);
    void searchName(string name);

	/*==== Behaviors ====*/
    int findHeight(Node* node);
	Node* rotateLeft(Node* node);
	Node* rotateRight(Node* node);
	void printInOrder_Helper(Node* root);
    void printInOrder();
	void printPostOrder_Helper(Node* root);
    void printPostOrder();
	void printPreOrder_Helper(Node* root);
    void printPreOrder();
	void printLevelCount();
};

AVL::AVL() {
	_root = nullptr;
};

// void AVL::destruct(Node* root) 
// {
//   if (root->left){
//     destruct(root->left);
//   }
//   if (root->right){
//     destruct(root->right);
//   }
//   delete root;
// }

// AVL::~AVL(){

// 	destruct(_root);
// }

int AVL::findHeight(Node* node){

	int levels = 0;
    queue<Node*> nodes;

    if(node != nullptr){
      nodes.push(node);
    }

    while(!nodes.empty()){

      if(nodes.front()->left != nullptr){
        nodes.push(nodes.front()->left);
      }
      if(nodes.front()->right != nullptr){
        nodes.push(nodes.front()->right);
      }
      
	  levels++;
      nodes.pop();
    }

	return levels;
}

AVL::Node* AVL::rotateLeft(Node* node){

	Node* grandchild = node->right->left;
	Node* newParent = node->right;
	newParent->left = node;
	node->right = grandchild;
	return newParent;
}

AVL::Node* AVL::rotateRight(Node* node){

	Node* grandchild = node->left->right;
	Node* newParent = node->left;
	newParent->right = node;
	node->left = grandchild;
	return newParent;
}

AVL::Node* AVL::insertHelper(Node* root, Student student) {

	if (root == nullptr) {
		cout << "successful" << endl;
		return new Node(student);
	}
	else if (student.ID < root->student.ID) {
		root->left = insertHelper(root->left, student);
	}
	else if (student.ID > root->student.ID) {
		root->right = insertHelper(root->right, student);
	}
	root->height = findHeight(root);
	
	//subtree is right heavy
	if(findHeight(root->left) - findHeight(root->right) < -1){
		if(findHeight(root->right->left) - findHeight(root->right->right) > 1){
			//right left rotation & update height
			root = rotateLeft(rotateRight(root));
			root->height = findHeight(root);
		}
		else{
			//left rotation & update height
			root = rotateRight(rotateLeft(root));
			root->height = findHeight(root);
		}
	}
	//subtree is left heavy
	if(findHeight(root->left) - findHeight(root->right) > 1){
		if(findHeight(root->left->left) - findHeight(root->left->right) < -1){
			//left right rotation & update height
			root = rotateLeft(root);
			root = rotateRight(root);
			root->height = findHeight(root);
		}
		else{
			//right rotation & update height
			root = rotateRight(root);
			root = rotateLeft(root);
			root->height = findHeight(root);
		}
	}
	return root;
}

void AVL::insert(Student student){

    _root = insertHelper(_root, student);
}

//Complete
AVL::Node* AVL::searchID_Helper(Node* root, int ID){

	if(root == nullptr){
		cout << "unsuccessful" << endl;
		return nullptr;
	} else{
		if(root->student.ID == ID){
			cout << root->student.name << endl;
			return root;
		}
		else if(ID < root->student.ID){
			root->left = searchID_Helper(root->left, ID);
		}
		else if(ID > root->student.ID){
			root->right = searchID_Helper(root->right, ID);
		}
	}
	return nullptr;
}

void AVL::searchID(int ID){

    _root = searchID_Helper(_root, ID);
}

AVL::Node* AVL::searchName_Helper(Node* root, string name){
	
	if(root == nullptr){
		cout << "unsuccessful" << endl;
		return nullptr;
	}
	else{
		if(root->student.name == name){
			cout << root->student.ID << endl;
			return root;
		}
		else{
			root->left = searchName_Helper(root->left, name);
			root->right = searchName_Helper(root->right, name);
		}
	}
	return nullptr;
}

void AVL::searchName(string name){
	
	_root = searchName_Helper(_root, name);
}

void AVL::printPreOrder_Helper(Node* root){

	if(root == nullptr){
		return;
	}
	else{
		cout << root->student.name << ", ";
		printPreOrder_Helper(root->left);
		printPreOrder_Helper(root->right);
	}
}

void AVL::printPreOrder(){

    printPreOrder_Helper(_root);
    cout << endl;
}

void AVL::printInOrder_Helper(Node* root) {

	if (root == nullptr) {
		return;
	}
	else {
		printInOrder_Helper(root->left);
		cout << root->student.name << ", ";
		printInOrder_Helper(root->right);
	}

}

void AVL::printInOrder(){

    printInOrder_Helper(_root);
    cout << endl;
}

void AVL::printPostOrder_Helper(Node* root){

	if(root == nullptr){
		return;
	}
	else{
		printPostOrder_Helper(root->left);
		printPostOrder_Helper(root->right);
		cout << root->student.name << ", ";
	}
}

void AVL::printPostOrder(){

    printPostOrder_Helper(_root);
    cout << endl;
}

void AVL::printLevelCount(){

	int levels = findHeight(_root);
	cout << levels << endl;
}
