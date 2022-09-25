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

	/*==== Construction / Destruction ====*/
	AVL();
	~AVL();
	void destruct(Node* root);

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
	void printInOrder_Helper(Node* root);
    void printInOrder();
	void printPostOrder_Helper(Node* current);
    void printPostOrder();
	void printPreOrder_Helper(Node* current);
    void printPreOrder();
};

AVL::AVL() {
	_root = nullptr;
};

void AVL::destruct(Node* root) 
{
  if (root->left){
    destruct(root->left);
  }
  if (root->right){
    destruct(root->right);
  }
  delete root;
}

AVL::~AVL(){

	destruct(_root);
}

int AVL::findHeight(Node* node){

	int levels = 0;
    queue<Node*> nodes;

	if(node->left == nullptr && node->right == nullptr){
		return 0;
	}

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
	node->height = levels;

	return levels;
}

AVL::Node* AVL::insertHelper(Node* root, Student student) {

	if (root == nullptr) {
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
	if(root->left->height - root->right->height < -1){
		if(root->right->left->height - root->right->right->height > 1){
			//right left rotation & update height
		}
		else{
			//left rotation & update height
		}
	}
	//subtree is left heavy
	if(root->left->height - root->right->height > 1){
		if(root->left->left->height - root->left->right->height < -1){
			//left right rotation & update height
		}
		else{
			//right rotation & update height
		}
	}
	return root;
}

void AVL::insert(Student student){

    _root = insertHelper(_root, student);
}

AVL::Node* AVL::searchID_Helper(Node* root, int ID){

	if(_root == nullptr){
        cout << "unsuccessful" << endl;
        return _root;
    }
    if(root->student.ID == ID){
        cout << root->student.name << endl;
        return root;
    }
    else if (root->student.ID < ID && root->left != nullptr) {
		root->left = searchID_Helper(root->left, ID);
	}
	else if (root->student.ID > ID && root->right != nullptr) {
		root->right = searchID_Helper(root->right, ID);
	}
	return root;
}

void AVL::searchID(int ID){

    _root = searchID_Helper(_root, ID);
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
