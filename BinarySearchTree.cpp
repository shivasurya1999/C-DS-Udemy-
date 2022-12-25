/*
C++ code for Binary search tree 
*/

#include<iostream>
using namespace std;

class Node {
public:
	Node* lchild;
	int data;
	Node* rchild;
};

class BST {
private:
	Node* root;
public:
	BST(Node* p) { root = p; };
	void CreateBST(Node* p,int next_node_value);
	void Inorder(Node* p);
	Node* getRoot() { return root; };
};

void BST::CreateBST(Node* p, int next_node_value) {
	if (next_node_value != -1) {
		Node* inserted_node;
		inserted_node = new Node;
		inserted_node->data = next_node_value;
		inserted_node->lchild = NULL;
		inserted_node->rchild = NULL;
		if (p->data > inserted_node->data) {
			if (p->lchild) CreateBST(p->lchild,next_node_value);
			else {
				p->lchild = inserted_node;
				cout << endl << "Enter the next value. To terminate enter -1 : ";
				cin >> next_node_value;
				CreateBST(getRoot(), next_node_value);
			}
		}
		else {
			if (p->rchild) CreateBST(p->rchild,next_node_value);
			else {
				p->rchild = inserted_node;
				cout << endl << "Enter the next value. To terminate enter -1 : ";
				cin >> next_node_value;
				CreateBST(getRoot(), next_node_value);
			}
		}
	}
}

void BST::Inorder(Node* p) {
	if (p) {
		Inorder(p->lchild);
		cout << p->data << ", ";
		Inorder(p->rchild);
	}
}

int main() {
	int root_data;
	cout << "Enter the elements of the Binary Search Tree one by one: " << endl;
	cout << "Enter the first value: ";
	cin >> root_data;
	Node* root_node;
	root_node = new Node;
	root_node->data = root_data;
	root_node->lchild = NULL;
	root_node->rchild = NULL;
	BST t(root_node);
	int next_node_value;
	cout << endl << "Enter the next value. To terminate enter -1 : ";
	cin >> next_node_value;
	t.CreateBST(t.getRoot(),next_node_value);
	cout << endl<<"Inorder traversal of the created BST: ";
	t.Inorder(t.getRoot());
}