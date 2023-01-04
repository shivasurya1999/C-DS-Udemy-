/*
C++ code for sorting algorithms 
1. Bubble Sort 
*/

#include<iostream>
using namespace std;

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
	BubbleSort(A, n);
	PrintArray(A,n);
}