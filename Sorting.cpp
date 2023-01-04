/*
C++ code for sorting algorithms 
1. Bubble Sort- In bubble sort if we perform 1 pass we get the largest element. If we perform 2 passes we get the second largest element and so on 
2. Insertion Sort- we won't get any info from a single pass like the largest element in first pass in case of bubble sort. Also insertion sort is better implemented using linked list than array as no shifting in linked list
3. Selection sort- If we perform 1 pass we get the smallest element. After the 2nd pass we get the second smallest element and so on 
*/

#include<iostream>
using namespace std;

class Node {
public:
	int data;
	Node* next;
};

void Swap(int &a, int &b) { //function that swaps elements. pass by reference is used to change the original values when passed 
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void BubbleSort(int A[], int n) { //function that uses bubble sort to sort an array of integers 
	if (n == 1) return; //stop recursion if a single element is passed 
	int flag = 0; 
	for (int i = 0; i < n-1; i++) { //single pass 
		if (A[i] > A[i+1]) { //if current element is greater than consecutive element
			flag = 1; //flag changed if array is not already sorted 
			Swap(A[i], A[i+1]); //swap both the elements 
		} 
	}
	if (flag == 1) {
		BubbleSort(A, n - 1); //recursive bubble sort with one element less because the max element is placed at nth position
	}
	else { //if flag is 0, then no use of sorting further because the array has been sorted 
		cout << "Elements sorted earlier than worst case. Returning..." << endl;
		return;
	}
}

void InsertionSort(Node* first) { //Create Sorted linked list from user input using insertion sort 
	int element;
	cout <<endl <<"Enter the elements to be sorted. Enter -1 to stop creating linked list: " << endl;
	cin >> element;
	Node* n;
	n = new Node;
	n->data = element; //this is the first node and is always sorted because it is the only node 
	n->next = NULL; 
	first->next = n;
	Node* t; //tail pointer to 'n'
	t = new Node;
	t = first;
	cout << "Enter the next element. Enter -1 to stop creating linked list: " << endl; //creation of linked list begins 
	cin >> element;
	while (element != -1) { //if user inputs -1 then creation stopped 
		Node* p; //creating a node for the element 
		p = new Node;
		p->data = element; 
		p->next = NULL;
		while (n) { //while 'n' is not null 
			if (n->data < p->data) { //keep advancing 'n' and 't' if the element value is greater than the value of 'n' 
				n = n->next;
				t = t->next;
			}
			else break;
		}
		t->next = p; //insert the element after the tail pointer 
		p->next = n; //'p' will point to 'n' after insertion (even if 'n' is NULL this works)
		cout << "Enter the next element. Enter -1 to stop creating linked list: " << endl; //user to enter the next element to continue insertion 
		cin >> element;
		while ((p->data < element) && (p->next == NULL)) { //if element is to be inserted in an already sorted list (adaptive code)
			Node* sorted_node;
			sorted_node = new Node;
			sorted_node->data = element;
			sorted_node->next = NULL;
			p->next = sorted_node;
			p = sorted_node;
			cout << "Inserting at last of sorted list, enter the next element. Enter -1 to stop creating linked list: " << endl; //user to enter the next element to continue insertion 
			cin >> element;
		}
		n = first->next; //re-initialize 'n'
		t = first; //re-initialize 't' 
	}
}

void SelectionSort(int A[], int n) { //Function to sort array using selection sort 
	for (int i = 0; i < n; i++) { //iterate over all elements 
		int j = i; //used for exchange of min element with 'i'
		for (int k = j + 1; k < n; k++) { //checks elements further than 'j' to bring 'j' to min value 
			if (A[j] > A[k]) {
				j = k; //value at 'k' is less than that at 'j' so bring 'j' to 'k' and advance 'k' further  
			}
		}
		if (j != i) Swap(A[i], A[j]); //once 'k' is out of the array scope we have the min element at 'j' to be swapped with element at 'i'
	}
}

void DisplayLinkedList(Node* first) { //Display linked list given its header node 
	Node* p;
	p = new Node;
	p = first->next;
	while (p) {
		cout << p->data << "->";
		p = p->next;
	}
}


void PrintArray(int A[],int n) {
	for (int i = 0; i < n; i++) {
		cout << A[i]<<", ";
	}
}

int main() {
	int A[] = {5,3,8,2,7,6,1,9,15,20,10,4};
	//int A[] = { 1,2,3,4,5,6,7,10,9,8};
	//int A[] = { 10,9,8,7,6,5,4,3,2,1 };
	int n = sizeof(A) / sizeof(int);
	cout << endl << "Array A after performing bubble sort: ";
	BubbleSort(A, n);
	PrintArray(A,n);
	Node* first;
	first = new Node;
	first->data = 0;
	first->next = NULL;
	cout << endl << "Performing insertion sort: " << endl;
	InsertionSort(first);
	DisplayLinkedList(first);
	int B[] = { 10,9,8,7,5,4,3,2,1 };
	int n_b = sizeof(B) / sizeof(int);
	cout << endl << "Array B after performing selection sort: ";
	SelectionSort(B, n_b);
	PrintArray(B, n_b);
}