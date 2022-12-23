/*
C++ code to create and print a binary tree by traversing it in multiple ways 
1. User enters the tree values and the tree is created. If -1 is enterd, it means that the node has no child (left or right)
2. The tree is traversed in 3 ways. Preorder, Inorder and Postorder and is printed to the output screen respectively 
*/

#include<iostream>
using namespace std;

class Node { //Create the node class. The basic element of the tree consists of the node data, address of its left node and address of its right node 
public:
	int data;
	Node* left;
	Node* right;
};

class CircularQueue { //Create circular queue to hold addresses of each tree node 
public:
	int front;
	int rear;
	int size;
	Node** Q; //Create a pointer to an array of type Node*
};

bool isEmpty(CircularQueue* q) { //Returns 1 if the queue is empty else returns 0 
	if (q->front == q->rear) {
		cout << "Queue is empty" << endl;
		return 1;
	}
	return 0;
}

bool isFull(CircularQueue* q) { //Returns 1 if the queue is full else returns 0
	if (((q->rear) + 1) % (q->size) == q->front) return 1;
	else return 0;
}

void enqueueCircular(CircularQueue* q,Node* element) { //enqueue operation using circular queue 
	if (isFull(q)) cout << "Queue overflow" << endl;
	else {
		q->rear = ((q->rear) + 1) % (q->size);
		q->Q[q->rear] = element;
	}
}

Node* dequeueCircular(CircularQueue* q) { //dequeue operation using circular queue 
	Node* n = NULL;
	if (isEmpty(q)) {
		cout << "Queue underflow"<<endl;
	}
	else {
		n = q->Q[((q->front) + 1) % (q->size)];
		q->front = ((q->front) + 1) % (q->size);
	}
	return n;
}

void CreateBinaryTree(Node* root,CircularQueue* q) { //Function to create binary tree using user inputs 
	enqueueCircular(q,root); //enqueue root element in circular queue
	while (!isEmpty(q)) { //repeat until queue is empty 
		Node* n;
		n = new Node;
		n = dequeueCircular(q); //dequeue q
		//enter left node value of the dequeued node. enter -1 if there is no left node 
		int left_value;
		cout << "Enter the left node value of "<<n->data<<": " << endl;
		cin >> left_value;
		if (left_value != -1) {
			//create left node if the entered value is not -1 and enqueue it into q
			Node* left_node;
			left_node = new Node;
			left_node->data = left_value;
			left_node->left = NULL;
			left_node->right = NULL;
			n->left = left_node;
			enqueueCircular(q, left_node);
		}
		//enter right node value of the dequeued node. enter -1 if there is no right node
		int right_value;
		cout << "Enter the right node value of "<<n->data<<": " << endl;
		cin >> right_value;
		if (right_value != -1) {
			//create right node if the entered value is not -1 and enqueue it into q
			Node* right_node;
			right_node = new Node;
			right_node->data = right_value;
			right_node->left = NULL;
			right_node->right = NULL;
			n->right = right_node;
			enqueueCircular(q, right_node);
		}
	}
}

void PrintTreePreorder(Node* root) { //Recursive preorder traversal 
	cout << root->data << ", ";
	if (root->left != NULL) PrintTreePreorder(root->left);
	if(root->right != NULL) PrintTreePreorder(root->right);
}

void PrintTreeInorder(Node* root) { //Recursive inorder traversal
	if (root->left != NULL) PrintTreeInorder(root->left);
	cout << root->data << ", ";
	if (root->right != NULL) PrintTreeInorder(root->right);
}

void PrintTreePostorder(Node* root) { //Recursive postorder traversal
	if (root->left != NULL) PrintTreePostorder(root->left);
	if (root->right != NULL) PrintTreePostorder(root->right);
	cout << root->data << ", ";
}

int main() {
	//create root node 
	Node* root;
	root = new Node;
	int root_value;
	cout << "Enter the root node value: " << endl; 
	cin >> root_value; //user to input value of root node 
	root->data = root_value;
	root->left = NULL;
	root->right = NULL;
	//create empty circular queue 
	CircularQueue *q;
	q = new CircularQueue;
	int queue_size;
	cout << "Enter the queue size to store tree element addresses: " << endl;
	cin >> queue_size;
	q->front = 0;
	q->rear = 0;
	q->size = queue_size;
	q->Q = new Node*[q->size]; //create array with number of elements q->size and elements type is Node*
	CreateBinaryTree(root,q); //create binary tree 
	cout << "Preorder: ";
	PrintTreePreorder(root); //preorder traversal 
	cout << endl;
	cout << "Inorder: ";
	PrintTreeInorder(root); //inorder traversal 
	cout << endl;
	cout << "Postorder: ";
	PrintTreePostorder(root); //postorder traversal 
	cout << endl;

}