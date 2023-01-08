/*
Created by: Shiva Surya Lolla
Date: 6th January 2023 
C++ code for hashing methods 
A hash map stores elements in the form of array of linked lists. A power factor (lambda) is defined for every hash map which is the avg number of elements in the linked list of each index of the array
In the below hash map, 
1. Chaining - elements stored in linked list in array of linked lists using hash function. Elements with the same remainder when divided by 10 are stored at the index equal to that remainder in sorted linked list manner 
2. Linear Probing - maximum power factor can be 0.5. We cannot delete elements using linear probing because we will have to shift other elements as per the spaces created (rehashing) which is difficult 
*/

#include<iostream>
using namespace std;

class Node { //Node class to store element data in the form of linked list 
public:
	int data;
	Node* next;
};

void InsertInSorted(Node* first,int a_val) { //The below code performs element insertion in a sorted linked list 
	Node* val_node;
	val_node = new Node;
	val_node->data = a_val;
	val_node->next = NULL;
	Node* p;
	p = new Node;
	p = first->next;
	Node* t; //tail pointer to 'p' 
	t = new Node;
	t = first;
	while (p) {
		if (val_node->data > p->data) { //if value of element is greater than the data 'p' is pointing to, advance 'p' and 't'
			p = p->next;
			t = t->next;
		}
		else break;
	}
	val_node->next = p; //insert node before 'p'
	t->next = val_node; //insert node after 't'

}

void InsertInHash(int a_val,Node** H) { //Given the value of an element and the hash map, insert the element into the hash map 
	if (H[a_val % 10]->next) { //if the index contains elements linked already then insertion needs to take place in that list 
		InsertInSorted(H[a_val % 10], a_val);
	}
	else { //else fresh insertion 
		Node* val_node;
		val_node = new Node;
		val_node->data = a_val;
		val_node->next = NULL;
		H[a_val % 10]->next = val_node;
	}
}

void CreateHashMap(int A[],Node** H,int n) { //Function that creates a Hash Map H from an array of integers A and the number of integers n
	int a_val;
	for (int i = 0; i < n; i++) {
		a_val = A[i]; //Take array elements one by one 
		InsertInHash(a_val,H); //Insert in hash map
	}
}

bool SearchHashMap(Node** H,int elem) { //Searches hash map H for elem and returns 1 if elem is found. Else returns 0  
	int elem_remainder = elem % 10;
	Node* p;
	p = new Node;
	if (H[elem_remainder]->next) {
		p = H[elem_remainder]->next;
		while (p) {
			if (elem > p->data) p = p->next;
			else {
				if (elem == p->data) {
					cout << "Element found in Hash Map." << endl; //if anywhere in the entire process if elem matches the data in 'p', then it is found 
					return 1;
				}
			}
		}
	}
	cout << "Element not found in Hash Map." << endl; //if the loop has exited it means elem was not found 
	return 0;
}

void DeleteInHash(int elem,Node** H) { //Function to delete elem in hash map H 
	cout << "Request to delete element " << elem << " from the Hash Map." << endl;
	if (SearchHashMap(H, elem)) { //if elem is found in Hash map 
		Node* n;
		n = new Node;
		Node* t;
		t = new Node;
		int index = elem % 10;
		n = H[index]->next;
		t = H[index];
		while (n->data != elem) { 
			n = n->next;
			t = t->next;
		}
		t->next = n->next; //navigate to elem location and delete its corresponding node 
		cout << "Element deleted from Hash Map" << endl;
	}
	else cout << "Element not found in Hash Map so cannot delete." << endl;
}

void InsertLP(int A[], int elem) { //Function to insert elem in an array using linear probing 
	if (!A[elem % 10]) { //if no value is present at index elem%10 
		A[elem % 10] = elem; //insert at elem%10
	}
	else { //else insert in the next available space in the hash map 
		int i;
		for (i = 0; A[i + elem % 10]; i = i++) {

		}
		A[i + elem % 10] = elem;
	}
}

void SearchLP(int A[],int elem) { //Function to search elem in array where elements were inserted using linear probing 
	if (A[elem % 10] == elem) cout << "Element found at index: " << elem % 10 << endl; //if elem found at index elem%10 
	else { 
		int i;
		for (i = 0; A[i + elem % 10]; i = i++) { //keep checking the consecutive array indices until elem is found  
			if (A[i + elem % 10] == elem) {
				cout << "Element found at index: " << i + elem % 10 << endl;
				break;
			}
		}
		if (!A[i + elem % 10]) cout << "Element not found in hash table." << endl; //if there is a white space while searching => elem does not exist in hash table 
	}
}

int main() {
	/*Chaining*/
	int A[] = {16,12,25,39,6,122,5,68,75};
	/*Hash map initialization starts*/
	Node** H;
	H = new Node * [10];
	int n = sizeof(A) / sizeof(int);
	Node* head;
	for (int j = 0; j < 10; j++) {
		head = new Node;
		head->data = 0;
		head->next = NULL;
		H[j] = head;
	}
	/*Hash map initialization ends*/
	CreateHashMap(A,H,n);
	int elem = 122;
	SearchHashMap(H, elem);
	DeleteInHash(122, H);
	SearchHashMap(H, elem);

	/*Linear probing*/
	int HT[10] = { 0 };
	InsertLP(HT, 12);
	InsertLP(HT,25);
	InsertLP(HT,35);
	InsertLP(HT,26);
	SearchLP(HT,35);
}