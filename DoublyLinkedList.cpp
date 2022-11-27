/*
Code to create and display a doubly linked list 
Why doubly list is powerful? : Because nodes can be reached either way. This saves us the effort and time of using two pointers for operations on the list 
*/

#include<iostream>
using namespace std;

class Node {
public:
	int data;
	Node* prev;
	Node* next;
};

void CreateDoubly(Node* first,int A[],int size) { //create a doubly list 
	Node* p;
	p = new Node;
	p->data = A[0];
	p->prev = first; //next node points to previous node 
	first->next = p; //previous node points to next node 
	p->next = NULL;
	Node* q;
	for (int i = 1; i <size; i++) {
		q = new Node; //make a new node 
		q->data = A[i];
		q->prev = p; //next node points to previous node 
		p->next = q; //previous node points to next node 
		q->next = NULL;
		p = q; //update previous node to current node 
	}
}

void DisplayDoubly(Node* first) { //display a doubly list 
	Node* p;
	p = new Node;
	p = first->next;
	for (int i = 0; p->next != NULL; i++) {
		cout << p->data << "<->";
		p = p->next;
	}
	cout << p->data;
}

int main() {
	Node* first;
	first = new Node;
	first->data = 0;
	first->prev = NULL;
	first->next = NULL;
	int A[] = {3,5,7,8,10};
	int size = (sizeof(A)) / (sizeof(int));
	CreateDoubly(first, A,size);
	DisplayDoubly(first);
	
}