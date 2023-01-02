/*
Heap is composed of elements of binary tree arranged in an array with the rule: node at i, left child at 2*i and right child at 2*i + 1 and no gap inbetween array elements 
1. C++ code to create a heap by inserting elements into it 
2. Delete element from the heap 
3. Sort elements in increasing order using heap sort 
*/

#include<iostream>
using namespace std;

void Insert(int H[], int n) { //Function to insert element in heap. The heap initially has 'n-1' elements and the new element is inserted at index 'n'
	int temp, i = n;
	temp = H[i]; //copy inserted element value into temp variable 
	while ((i > 1)&&(temp > H[i / 2])) { //greater element should be above smaller element in heap so comparision is done 
		H[i] = H[i / 2]; //smaller element moved to a lower position 
		i = i / 2;
	}
	H[i] = temp; //insertion of element at proper position after previous steps 
}

int Delete(int H[],int n) { //Function to delete root element from heap out of 'n' elements, adjust remaining elements to adhere to heap rules and insert the deleted element at last of the heap 
	int root_value = H[1]; //root value is copied into a variable 
	int temp;
	H[1] = H[n]; //The last element of heap array is copied to the root, otherwise the array will be left with a gap in between which is against heap rules 
	//The below code works on adjusting the heap after the previous step 
	int i = 1;
	int j = 2*i;
	while (j < n) { //stop adjusting positions after the adjustment is done wrt the element at root position 
		if (H[j] > H[j + 1]) { //compare two children of the node and swap the max value amongst them with the root 
			temp = H[i];
			H[i] = H[j];
			H[j] = temp;
			i = j;
			j = 2 * i;
		}
		else {
			temp = H[i];
			H[i] = H[j+1];
			H[j + 1] = temp;
			i = j + 1;
			j = 2 * i;
		}
	}
	H[n] = root_value; //this step is responsible for heap sort because we are storing the max value (root value that has been deleted) from max heap at last of the array 
	return root_value;
}

int main() {
	int H[] = {0,10,20,30,25,5,40,35}; //initial array that need to be converted to a max heap 
	for (int i = 2; i < 8; i++) { //convert the array H[] to max heap 
		Insert(H, i);
	}
	for (int j = 1; j < 8; j++) { //output array after conversion 
		cout << H[j] << ",";
	}
	for (int k = 7; k >= 1; k--) { //Delete elements of heap one by one and store them at the array end to sort the heap 
		Delete(H, k);
	}
	cout << endl << "Array after heap sort: " << endl;
	for (int m = 1; m < 8; m++) { //output array after heap sort 
		cout << H[m] << ",";
	}
}