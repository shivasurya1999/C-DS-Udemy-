/*
Linked list functions : KEY LESSON - try to avoid assigning header to the newly created nodes directly. Instead assign header->next to the 'next' of new nodes. Otherwise there will be mutability issues 
The below code consists of functions for 
a) Inserting elements into a linked list (unsorted and sorted)
b) Checking whether a linked list is sorted 
c) Reversing a linked list using sliding pointers and recursion 
d) Merging two sorted linked lists
*/

#include<iostream>
using namespace std;

class Node { //A node class is created with members as the data in the node and the address of the subsequent node 
public:
	int data;
	Node* next;
};

void Display(Node* first) { //Displays the elements of the linked list 
	Node* p;
	p = first;
	while (p->next != NULL) {
		p = p->next;
		cout << p->data << "->";
	}
}

void Insert(Node* first,int position,int value) { //Inserts element of 'value' in a linked list with 'first' as the header node, at a 'position' 
	Node* n; 
	n = new Node;
	n->data = value; //A node is created and the value is stored 
	if (position == 0) { //If the insertion needs to take place at the begining of the list 
		n->next = first->next;
		first->next = n;
	}
	else {
		Node* p;
		p = new Node;
		p = first;
		for (int i = 0; i < position; i++) {
			if (p->next == NULL) { //If the position of insertion is greater than the linked list size 
				cout << "Position requested exceeded the list bounds. Inserting the node requested at last" << endl;
				break;
			}
			p = p->next; //p is incremented until the desired position
		}
		n->next = p->next; //node pointing to the next element of p 
		p->next = n; //p pointing to the node 
	}
}

bool IsSorted(Node* first) { //checks whether a list is sorted, returns 0 when unsorted, returns 1 when sorted 
	Node* p;
	Node* q;
	p = new Node;
	q = new Node;
	q = first->next;
	p = q->next;
	while (p->next != NULL) {
		if ((p->data) < (q->data)) {
			return 0;
		}
		q = q->next;
		p = p->next;
	}
	return 1;

}

void InsertInSortedList(Node* first,int value) { //Use this function to insert an element of 'value' only in a sorted list with the header node 'first'
	Node* n;
	n = new Node;
	n->data = value;
	Node* p;
	Node* q;
	p = new Node;
	q = new Node;
	q = first; //tailing pointer 
	p = q->next; //header pointer 
	while (p->data < n->data) { //keep incrementing p and q until you find a node with data greater than the value to be inserted 
		q = q->next;
		p = q->next;
	}
	n->next = q->next; //point n->next to p 
	q->next = n; //insert n after q
}

void ReverseUsingSliding(Node* first) { //Reverse linkedlist using sliding pointers 
	Node* p;
	Node* q;
	Node* r;
	Node* s;
	p = new Node; //3 pointers are used so that the address of p is not lost at every step 
	q = new Node;
	r = new Node;
	s = new Node;
	p = first;
	r = NULL;
	q = NULL;
	while (p != NULL) {
		r = q;
		q = p;
		p = p->next;
		q->next = r;
	}
	first = q;
	cout <<endl<<"The reversed list is: " << endl;
	Display(first);
}

void ReverseUsingRecursion(Node* p,Node* q,Node* first) { //Reverse linkedlist using recursion  
	if (p->next != NULL) {
		ReverseUsingRecursion(p->next,p,first);
	}
	else
	{
		(first->next)->next = NULL; //the first node of the list is pointed to null, making it the last node 
		first->next = p;  //header is pointed to the last node 
	}
	p->next = q; //every node is pointed to its previous node 

}

void MergeSortedLists(Node* first, Node* second) { //Merge two sorted linked lists
	Node* third; //Create the header of the merged list 
	Node* last; //Create the tail of the merged list 
	third = new Node;
	last = new Node;
	if ((first->next)->data < (second->next)->data) { //if first node data of first list is less than first node data of second list 
		third->next = first->next; //put third on first 
		last->next = first->next; //put last on first 
		first->next = (first->next)->next; //update first to point to the second node of the first list 
		(last->next)->next = NULL;  //make the first node's next as null 
	}
	else { //else condition with similar code but for second list 
		third->next = second->next;
		last->next = second->next;
		second->next = (second->next)->next;
		(last->next)->next = NULL;
	}


	while ((first->next != NULL) && (second->next != NULL)) {
		if ((first->next)->data < (second->next)->data) { 
			(last->next)->next = first->next; //(last->next)->next was null, update it here so that the node first->next is added to the merged list 
			last->next = first->next; //put last on first 
			first->next = (first->next)->next;  //update first to point to the next node of the first list 
			(last->next)->next = NULL; //make the first node's next as null 
		}
		else { //else condition with similar code but for second list 
			(last->next)->next = second->next;
			last->next = second->next;
			second->next = (second->next)->next;
			(last->next)->next = NULL;
		}
	}
	if (first->next == NULL) { //if first list gets exhausted 
		while (second->next != NULL) {
			(last->next)->next = second->next;
			last->next = second->next;
			second->next = (second->next)->next;
			(last->next)->next = NULL;
		}
	}
	else {
		while (first->next != NULL) { //if second list gets exhausted 
			(last->next)->next = first->next;
			last->next = first->next;
			first->next = (first->next)->next;
			(last->next)->next = NULL;
		}
	}
	Display(third);
}


int main() {
	Node* first;
	Node* second;
	first = new Node;
	first->data = 0; //first node of the linked list with data equals zero by default 
	first->next = NULL; //The header node initially does not point towards anything 
	second = new Node;
	second->data = 0; //first node of the linked list with data equals zero by default 
	second->next = NULL; //The header node initially does not point towards anything 
	Insert(first, 0,1); //special case: inserting node at first 
	Insert(first, 1, 3);
	Insert(first, 2, 5);
	Insert(first, 5, 7); //special case: exceeding the bounds for insertion
	Insert(first, 1, 2); 
	Insert(second, 0, 4);
	Insert(second, 1, 6);
	Insert(second, 2, 8);
	Insert(second, 3, 9);
	//cout << "before insertion" << endl;
	//display(first);
	//if (IsSorted(first)) {
	//	cout <<endl<< "sorted" << endl;
	//	InsertInsortedList(first, 4);
	//	cout <<"after insertion" << endl;
	//	Display(first);
	//}
	//else cout << "unsorted" << endl;
	//ReverseUsingSliding(first);
	//Node* q;
	//q = new Node;
	//q = first->next;
	//ReverseUsingRecursion(q->next, q, first);
	//cout << endl << "The reversed list is: " << endl;
	//Display(first);

	Display(first);
	cout << endl;
	Display(second);
	cout << endl;
	MergeSortedLists(first,second);
}