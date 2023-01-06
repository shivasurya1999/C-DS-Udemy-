/*
* Created by: Shiva Surya Lolla
* Date: 4th January 2022
C++ code for sorting algorithms 
1. Bubble Sort- In bubble sort if we perform 1 pass we get the largest element. If we perform 2 passes we get the second largest element and so on 
2. Insertion Sort- we won't get any info from a single pass like the largest element in first pass in case of bubble sort. Also insertion sort is better implemented using linked list than array as no shifting in linked list
3. Selection sort- If we perform 1 pass we get the smallest element. After the 2nd pass we get the second smallest element and so on. We select the index and find element for the index in this 
4. Quick Sort - We select the element and then find an index for that element so that elements on one side are less than the element and on the other side of the index are greater than the element 
5. Merge Sort - Starting from two elements each, perform multiple passes by merging two times more number of elements than the previous pass until merge sort is done for the entire array 
*/

#include<iostream>
#include<cmath>
using namespace std;

class Node {
public:
	int data;
	Node* next;
};

void Swap(int &a, int &b) { //function that swaps elements. pass by reference is used to change the original values when passed 
	if (a == b) return;
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

void QuickSort(int A[],int s,int l) { //Function to sort array using quick sort 
	if (s==l) return; //if only single element return 
	else {
		int n = l; //initiate n as last element of function (l) for later use 
		int pivot = s; //take pivot as starting element of function (s)
		do {
			if (A[s] <= A[pivot]) s++; //increment s if the element at that index is less than pivot because we want all smaller elements to be on one side of pivot 
			else { //if we encounter an element at s which is greater than pivot, it is to be swapped with a smaller element 
				while ((A[l] > A[pivot])&&(s<l)) l--; //while element at l is less than pivot value decrement l 
				Swap(A[s], A[l]); //if element at l has stopped being greater than pivot swap that element with s which is greataer than pivot 
			}
		} while (s < l); //while starting index is less than ending index keep looping 
		l--;
		if (A[pivot] < A[l + 1]) Swap(A[pivot], A[l]);  //take the pivot element to a position so that on one side all elements are less than its value and on other side all elements are greater than its value 
		else Swap(A[pivot], A[l + 1]); //in case of two element and descending order, the above statement won't work so the ncurrent statement
		QuickSort(A, 0, l ); //recursively sort the elements less than pivot element 
		QuickSort(A, s, n); //recursively sort the elements greater than pivot element
	}
}

void Merge(int A[],int low,int mid,int high) { //Function that merges elements of two lists in an array by relatively sorting them. middle is the position which separates the lists in the array   
	int n = high + 1; //number of element of the array 
	int k = low; //starting index of array B 
	int* B; //create an array for the merged elements 
	B = new int[n];
	int i = low; //list 1 starts from low 
	int j = mid + 1; //list 2 starts from middle + 1 
	while ((i <= mid) && (j <= high)) { //while any one of the lists is not fully exhausted 
		if (A[i] < A[j]) { //if element of list 1 is less than element of list 2 
			B[k] = A[i]; //add list 1 element to B 
			i++; //increment index of the list 1
		}
		else { 
			B[k] = A[j]; //add list 2 element to B 
			j++; //increment index of the list 2
		}
		k++; //increment the index of B to further include elements from list 1 or list 2 
	}
	for (; i <= mid; i++) { //if elements of list 1 remain after the above steps, add all of them to B 
		B[k] = A[i];
		k++;
	}
	for (; j <= high; j++) { //if elements of list 2 remain after the above steps, add all of them to B 
		B[k] = A[j];
		k++;
	}
	for (int l = low; l <= high; l++) { //copy elements of B into A so that A contains the merged lists (sorted)
		A[l] = B[l];
	}
}

void IterativeMergeSort(int A[],int n) {//Given an array and the number of elements in the array the function uses merge sort iteratively to sort array elements 
	int p, i, low, mid, high;
	for (p = 2; p <= n; p = p*2) { //in first pass two elements each are considered, in 2nd pass 4 elements each are considered and so on for merging 
		for (i = 0; i + p - 1 < n; i=i+p) {  //'i' will be used to set low,mid and high in each array being considered for merging 
			low = i; 
			high = i + p - 1;
			mid = (low + high) / 2;
			Merge(A, low, mid, high); //merge the two sub arrays in the array being considered
		}
	}
	if (p / 2 < n) { //if the number of elements in A are not powers of 2 
		Merge(A, 0, p / 2 - 1, n-1); //Merge the remaining elements with the sorted array 
	}
}

void RecursiveMergeSort(int A[],int low,int high) { //Given an array, its low index and high index, sorts all the elements between the indices (low and high inclusive)
	if (low < high) { 
		int mid = (low + high) / 2;
		RecursiveMergeSort(A,low,mid); //sort the left half
		RecursiveMergeSort(A,mid+1,high); //sort the right half
		Merge(A, low, mid, high); //merge both halves 
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
	/*Bubble sort*/
	int A[] = {5,3,8,2,7,6,1,9,15,20,10,4};
	//int A[] = { 1,2,3,4,5,6,7,10,9,8};
	//int A[] = { 10,9,8,7,6,5,4,3,2,1 };
	int n = sizeof(A) / sizeof(int);
	cout << endl << "Array A after performing bubble sort: ";
	BubbleSort(A, n);
	PrintArray(A,n);

	/*Insertion sort*/
	Node* first;
	first = new Node;
	first->data = 0;
	first->next = NULL;
	cout << endl << "Performing insertion sort: " << endl;
	InsertionSort(first);
	DisplayLinkedList(first);

	/*Selection sort*/
	int B[] = { 10,9,8,7,5,4,3,2,1 };
	int n_b = sizeof(B) / sizeof(int);
	cout << endl << "Array B after performing selection sort: ";
	SelectionSort(B, n_b);
	PrintArray(B, n_b);

	/*Quick sort*/
	int C[] = { 1,2,3,4,5,6,7,10,9,8 };
	int n_c = sizeof(C) / sizeof(int);
	cout << endl << "Array C after performing quick sort: ";
	QuickSort(C, 0, n_c-1);
	PrintArray(C, n_c);

	/*Merge sort*/
	int D[] = { 10,9,8,7,6,5,4,3,2,1 };
	int n_d = sizeof(D) / sizeof(int);
	IterativeMergeSort(D, n_d);
	cout <<endl<< "Array after merging: ";
	PrintArray(D,n_d);
	int E[] = { 5,6,7,8,9,1,2,3,4 };
	int n_e = sizeof(E) / sizeof(int);
	RecursiveMergeSort(E,0,n_e-1);
	cout << endl << "Array after merging recursively: ";
	PrintArray(E, n_e);

}