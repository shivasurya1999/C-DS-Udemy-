/*
Created by: Shiva Surya Lolla
Date: 9th January, 2023
C++ code to obtain a minimum spanning tree from a graph using 
1. Prim's algorithm 
*/

#include<iostream>
#define I ((int)(32767)) //define an integer with a very high value 'I'

using namespace std;

/*Prim's Algorithm 
1. Given is graph of the form adjacency matrix. cost[i][j] = cost of edge if (i,j) is a graph edge. cost[i][j] = I if there is no edge between i and j where I is a very large number 
2. 't' is an array that maintains the edges that have been selected by Prim's algorithm. (t[0][k],t[1][k]) is such an edge. Where k = 0,1,2...5 as there are 6 edges of the spanning tree 
3. 'near' is an array that maintains smallest distance at an index from the index to the elements already selected by Prim's. near[index] = 0 if index belongs to the min spanning tree 
4. Find the min edge in the graph and update 't' by adding the edge to it and 'near' by making the array values at the edge node valued array indices to be zero
5. While all the elements in 'near' are not zero, select the next minimum valued edge from the nodes already selected by Prim's, Update 't' and 'near'
6. Now 't' contains all the edges selected by Prim's. Print those to terminal 
*/

void FindMinEdge(int& i, int& j, int cost[][8]) { //The function finds the minimum edge from the entire graph and updates the initial edge values i and j accordingly 
	int min = cost[i][j];
	for (int k = 1; k <= 7; k++) { //process only upper triangle of the matrix, because elements repeat in lower triangle of the adjacency matrix  
		for (int l = k + 1; l <= 7; l++) {
			if (cost[k][l] < min) {
				i = k;
				j = l;
				min = cost[k][l];
			}
		}
	}
}

bool AllZerosInNear(int near[]) { //check if the 'near' matrix has all  zeros to stop Prim's algorithm 
	int sum = 0;
	for (int i = 1; i <= 7; i++) {
		sum += near[i];
	}
	if (sum == 0) return 1;
	else return 0;
}

int GetMinDistIndex(int near[],int j, int cost[][8]) { //returns the node value that is closest to j from the values that have been already selected by Prim's 
	int index;
	int dist;
	for (int i = 1; i <= 7; i++) { //initialize to return some local minimum
		if (near[i] == 0) {
			index = i;
			dist = cost[j][i];
			break;
		}
	}
	for (int k = 1; k <= 7; k++) {
		if (near[k] == 0) {
			if (cost[j][k] < dist) {
				index = k; //update index to return global minimum 
				dist = cost[j][k]; //update min distance to return global minimum 
			}
		}
	}
	return index;
}

void UpdateNear(int near[],int cost[][8]) { //Once there are new zeros in 'near', this function updates other index values accordingly 
	int index = 0;
	for (int j = 1; j <= 7; j++) {
		if (near[j] != 0) { //the value of this index must be updated to contain the node found by Prim's that is closest to 'j'
			near[j] = GetMinDistIndex(near, j, cost); //update near[index] with its closest Prim node's value 
		}
	}
}

int GetMinNearIndex(int near[], int cost[][8]) { //Finds the minimum edge from the 'near' matrix and returns the index corresponding to it. This index is the new node selected by Prim's 
	int index = 0;
	int min = I;
	for (int i = 1; i <= 7; i++) {
		if (near[i] != 0) {
			if (cost[i][near[i]] < min) { //if cost of the edge i,near[i] is less than the local minimum  
				index = i; //update i 
				min = cost[i][near[i]]; //update local minimum cost which will eventually converge to global minimum cost 
			}
		}
	}
	return index; //return the node value selected by Prim's 
}

void Prim(int cost[][8], int near[], int t[][6]) {
	int i = 1, j = 1;
	int k = 0;
	FindMinEdge(i, j, cost); //Find minimum edge cost in grap and update i and j in the process (using call by reference)
	t[0][k] = i; //update 't' 
	t[1][k] = j; //update 't'
	k++; //increment k for storing the next edge 
	near[i] = 0; //update near to store the selected nodes values as 0 
	near[j] = 0; //update near to store the selected nodes values as 0
	UpdateNear(near, cost); //update the non zero values in near corresponding to the freshly added zeros to it 
	while (!AllZerosInNear(near)) {   //while the 'near' matrix does not have all zeros, continue Prim's algorithm
		int from_node = GetMinNearIndex(near,cost); //get a node of the minimum edge that is connected to the nodes already chosen by Prim's  
		int to_node = near[from_node]; //get a node of the minimum edge that is connected to the nodes already chosen by Prim's  
		t[0][k] = from_node; //update 't'
		t[1][k] = to_node; //update 't'
		k++; //increment k for storing the next edge 
		near[from_node] = 0; //update near to store the selected node value as 0
		UpdateNear(near, cost); //update the non zero values in near corresponding to the freshly added zeros to it 
	}
}


int main() {
	int cost[8][8] = { {I,I,I,I,I,I,I,I},{I,I,25,I,I,I,5,I},{I,25,I,12,I,I,I,10},
					{I,I,12,I,8,I,I,I},{I,I,I,8,I,16,I,14},{I,I,I,I,16,I,20,18},
					{I,5,I,I,I,20,I,I},{I,I,10,I,14,18,I,I} };  //adjacency matrix representation of graph 

	int near[8] = { I,I,I,I,I,I,I,I }; //initialize 'near' 
	int t[2][6]; //initialize 't'
	Prim(cost,near,t); //run prim's algorithm 
	cout << "After running Prim's algorithm, the minimum spanning tree consists of edges: "<<endl;
	for (int i = 0; i <= 5; i++) {
		cout << t[0][i] << ", " << t[1][i] << endl; //print edges selected by Prim's
	}
}

