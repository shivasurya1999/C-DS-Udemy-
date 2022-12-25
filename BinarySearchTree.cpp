/*
* Date: 24 December 2022 
* Created by: Shiva Surya Lolla 
C++ code for Binary search tree 
1. Create BST
2. Traverse BST inorder 
3. Search an element in BST, print its location or insert if the node does not exist in the BST 
4. Delete a node from BST 
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
	void Delete(Node* p, int element);
	Node* FindInOrderPOrS(Node* p);
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

Node* BST::FindInOrderPOrS(Node* p) { //returns the inorder successor if existing in the BST else the inorder predecessor. If left and right child of p are null, then returns NULL
	Node* t;
	t = new Node;
	t->data = 0;
	t->lchild = NULL;
	t->rchild = p;
	if (p->rchild) { //to find inorder successor go to the right child of the node and then keep going left until null 
		t->rchild = p->rchild;
		while (t->rchild->lchild) {
			t->rchild = t->rchild->lchild;
		}
		return t->rchild;
	}
	else if (p->lchild) { //to find inorder predecessor go to the left child of the node and then keep going right until null
		t->rchild = p->lchild;
		while (t->rchild->rchild) {
			t->rchild = t->rchild->rchild;
		}
		return t->rchild;
	}
	else return NULL; //if no inorder predecessor or successor, return NULL 
}

void BST::Delete(Node *p,int element) {
	//create a pointer that points to the node 'p'
	Node* n;
	n = new Node;
	n->data = 0;
	n->lchild = NULL;
	n->rchild = p;
	//create a null pointer that follows the pointer 'n'
	Node* t;
	t = new Node;
	t->data = 0;
	t->lchild = NULL;
	t->rchild = NULL;
	while (n->rchild) { //keep looping until 'n' points to null 
		if (n->rchild->data > element) { //if the node value to which n points to is greater than the new_elem_node value 
			t->rchild = n->rchild; //update the tail pointer to the node that 'n' is pointing to 
			n->rchild = n->rchild->lchild; //update 'n' to point to the left child of the current node it points to 
		}
		else if (n->rchild->data < element) { //if the node value to which n points to is less than the new_elem_node value
			t->rchild = n->rchild; // update the tail pointer to the node that 'n' is pointing to
			n->rchild = n->rchild->rchild; //update 'n' to point to the right child of the current node it points to 
		}
		else{
			//get inorder successor or predecessor 
			Node* replace_node;
			replace_node = new Node;
			replace_node = FindInOrderPOrS(n->rchild);
			if (replace_node) { //if found
				int elem = replace_node->data; //copy data into an int variable 
				Delete(n->rchild,replace_node->data); //Delete that node 
				n->rchild->data = elem; //copy the data of the replace_node deleted previoudly into the n->rchild 
				return;
			}
			else { //if no successor or predecessor then we have to remove that node from the BST 
				if (t->rchild) {
					if (n->rchild == t->rchild->lchild) t->rchild->lchild = NULL; //if the right child of 'n' is the left child of t->rchild
					else t->rchild->rchild = NULL;
				}
				else cout <<endl <<"Requirement was to delete the only node in the BST. Cannot do that. " << endl; //If BST has only one node, we cannot delete it 
				return;
			}
		}
	}
	if (t->rchild) cout <<endl<<"Element not found, therefore cannot delete it from the tree. " << endl;
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
	//Node* inOrder;
	//inOrder = new Node;
	//inOrder = t.FindInOrderPOrS(t.getRoot());
	//cout << endl;
	//cout << "The inorder predecessor or successor is: " << inOrder->data << endl;
	t.Delete(t.getRoot(),30);
	cout << endl << "Inorder traversal of the BST after deleting element: ";
	t.Inorder(t.getRoot());
}