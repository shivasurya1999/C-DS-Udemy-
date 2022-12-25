/*
* Date: 24 December 2022 
* Created by: Shiva Surya Lolla 
C++ code for Binary search tree 
1. Create BST
2. Traverse BST inorder 
3. Search an element in BST, print its location or insert if the node does not exist in the BST 
*/

#include<iostream>
using namespace std;

class Node { //Node class with left child, right child and data 
public:
	Node* lchild;
	int data;
	Node* rchild;
};

class BST { //Class for binary search tree with root node 
private:
	Node* root;
public:
	BST(Node* p) { root = p; };
	void CreateBST(Node* p,int next_node_value);
	void Inorder(Node* p);
	Node* getRoot() { return root; };
	void SearchAndInsert(Node* p, int element);
};

void BST::CreateBST(Node* p, int next_node_value) { //Function that creates BST from a given root node and a set of node values input by the user 
	if (next_node_value != -1) { //keep adding nodes to the BST until user inputs a value of -1 
		//create inserted node with the element value input by the user 
		Node* inserted_node;
		inserted_node = new Node;
		inserted_node->data = next_node_value;
		inserted_node->lchild = NULL;
		inserted_node->rchild = NULL;
		if (p->data > inserted_node->data) { //in this condition node needs to be inserted at the left of p by definition of BST 
			if (p->lchild) CreateBST(p->lchild,next_node_value); //if left child exists move to it and use recursion to proceed to insert next_node_value
			else { //else insert the next_node_value as the left child of p 
				p->lchild = inserted_node;
				cout << endl << "Enter the next value. To terminate enter -1 : ";
				cin >> next_node_value;
				CreateBST(getRoot(), next_node_value);
			}
		}
		else { //in this condition node needs to be inserted at the right of p by definition of BST 
			if (p->rchild) CreateBST(p->rchild,next_node_value); //if right child exists move to it and use recursion to proceed to insert next_node_value
			else { //else insert the next_node_value as the right child of p 
				p->rchild = inserted_node;
				cout << endl << "Enter the next value. To terminate enter -1 : ";
				cin >> next_node_value;
				CreateBST(getRoot(), next_node_value);
			}
		}
	}
}

void BST::Inorder(Node* p) { //Inorder traversal for BST and printing of nodes inorder 
	if (p) {
		Inorder(p->lchild);
		cout << p->data << ", ";
		Inorder(p->rchild);
	}
}

void BST::SearchAndInsert(Node* p,int element) { //Function to search and insert an element in a BST given its root 
	//create a null pointer that follows the pointer 'n'
	Node* t;
	t = new Node;
	t->data = 0;
	t->lchild = NULL;
	t->rchild = NULL;
	//Create a pointer 'n' to the root of the BST 
	Node* n;
	n = new Node;
	n->data = 0;
	n->lchild = NULL;
	n->rchild = p;
	//Create a new node to be inserted into the BST if the element is non existent in the BST 
	Node* new_elem_node;
	new_elem_node = new Node;
	new_elem_node->data = element;
	new_elem_node->lchild = NULL;
	new_elem_node->rchild = NULL;
	//Note:No insertion occurs in the below while loop. Only 'n' and 't' are updated and made ready for insertion 
	while (n->rchild) { //keep looping until 'n' points to null 
		if (n->rchild->data > element) { //if the node value to which n points to is greater than the new_elem_node value 
			t->rchild = n->rchild; //update the tail pointer to the node that 'n' is pointing to 
			n->rchild = n->rchild->lchild; //update 'n' to point to the left child of the current node it points to 
		}
		else if (n->rchild->data < element) { //if the node value to which n points to is less than the new_elem_node value
			t->rchild = n->rchild; // update the tail pointer to the node that 'n' is pointing to
			n->rchild = n->rchild->rchild; //update 'n' to point to the right child of the current node it points to 
		}
		else { //if the node value to which n points to is equal than the new_elem_node value, then we have found the element in our BST, so no need to insert again 
			if (t->rchild) cout << "Element found and is a child of " << t->rchild->data << endl;
			else cout<<"Element found at root." << endl;
			return;
		}
	}
	if (t->rchild) { //if 't' does not point to null 
		if (element < t->rchild->data) t->rchild->lchild = new_elem_node; //if element value is less than the value of the node 't' points to, add the element to the left of the node 't' points to
		else t->rchild->rchild = new_elem_node; //else add the element to the right of the node 't' points to  
	}

}

int main() {
	//initialize root by taking value from user 
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
	//Create BST from root and its next node value (we assume that the BST we create has atleast 2 nodes including root and node with next_node_value)
	t.CreateBST(t.getRoot(),next_node_value);
	cout << endl<<"Inorder traversal of the created BST: ";
	t.Inorder(t.getRoot()); //print the BST inorder 
	t.SearchAndInsert(t.getRoot(), 7); //search and insert element in the BSt 
	cout << endl;
	cout << endl << "Inorder traversal of the BST after inserting element: ";
	t.Inorder(t.getRoot()); //print BST inorder after performing search and insert 
}