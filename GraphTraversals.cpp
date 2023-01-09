/*
Created by: Shiva Surya Lolla
Date: 8th January 2023
C++ code for graph traversal using:
1. Breadth First Search (BFS)
2. Depth First Search (DFS)
*/

#include<iostream>
using namespace std;

/*Algorithm for BFS:
1. Take user i/p to form adjacency list
2. Create an empty queue 'Q' with sufficient space 
3. Create an array to maintain visited nodes 'V' with all initial values as zero 
4. Visit first element of adj list. Add it to queue. Update the visited array value from zero to one at the index corresponding to the visited element. Print the visited node's value to terminal
5. Explore the visited node (its neighbours), check each neighbour's value in visited array and add it to queue incase that value is zero
6. Dequeue 'Q' and update the dequeued node's index value in 'V' from zero to one. Print the visited node's value to terminal 
7. Repeat steps 4,5 and 6 until the 'Q' is empty 
*/

class Node { 
public:
	int data;
	Node* next;
};

class Queue {
public:
	int front;
	int rear;
	int size;
	int* q;
	Queue(int size);
};

Queue::Queue(int s) { //default constructor 
	size = s;
	front = 0;
	rear = 0;
	q = new int[s + 1];
}

void Enqueue(int visited, Queue* Q) { //enqueue an element in queue 
	Q->rear++;
	Q->q[Q->rear] = visited;
}

int Dequeue(Queue* Q) { //dequeue an element from a queue and return its value. If queue is empty return -1
	if (Q->front != Q->rear) {
		Q->front++;
		return Q->q[Q->front];
	}
	else return -1;
}

void CreateGraph(Node** G) { //Function to create adjacency list from user input 
	for (int i = 1; i <= 6; i++) {
		int n;
		cout << "Enter a neighbour for " << i << ". Enter -1 if all neighbours have been entered." << endl;
		cin >> n;
		while (n != -1) {
			Node* neigh_node;
			neigh_node = new Node;
			neigh_node->data = n;
			neigh_node->next = G[i]->next;
			G[i]->next = neigh_node;
			cout << "Enter a neighbour for " << i << ". Enter -1 if all neighbours have been entered." << endl;
			cin >> n;
		}
	}
}

void BFS(Node** G, Queue Q, int V[]) { //Program to implement BFS and print the explored nodes to the terminal. G is an adjacency list graph, Q is an empty queue initially and V indicates elem visited or not 
	Enqueue(1, &Q); //enqueue the first node of the graph 
	int elem = Dequeue(&Q); //dequeue the first node to get its value 
	while (elem != -1) { //while queue is not empty 
		if (V[elem] == 0) { //if node has not been visited
			cout << elem << ", "; //output the node value 
			V[elem] = 1; //mark the node as visited by changing its value in 'V'
			Node* explored;
			explored = new Node;
			explored = G[elem]->next; //explore the visited node's neighbour 
			while (explored) { //while there is a neighbour 
				if (V[explored->data] != 1) { //if neighbour has not been visited 
					Enqueue(explored->data, &Q); //enqueue its value 
				}
				explored = explored->next; //explore next node in the linked list 
			}
		}
		elem = Dequeue(&Q); //Dequeue 'Q' to visit the next element 
	}
}

/*Algorithm for DFS
1. Take adjacency list representation of a graph as input 
2. Create an array 'V' for maintaining the visited nodes initially containing all zeros 
3. Start with a node of the graph. Print its value, update the value at index 'V' as 1 and run DFS from its next node 
*/

int isAllVisited(int V[]) { //calculates sum of all array elements and returns it 
	int sum = 0;
	for (int i = 1; i <= 6; i++) {
		sum += V[i];
	}
	return sum;
}

void DFS(Node** G,int V[],int elem){ //Program to implement DFS and print the explored nodes to the terminal. G is an adjacency list graph, V is an array that indicates an index of it is visited or not
	if (isAllVisited(V) == 6) return; //if all nodes in graph are traversed then return 
	else {
		if (V[elem] == 0) { //if element is not visited 
			V[elem] = 1; //visit it
			cout << elem << ", "; //print its value 
			Node* explored; 
			explored = new Node;
			explored = G[elem]->next; //go to its neighbour in graph 
			while (explored) { //while neighbour is not null 
				if (V[explored->data] != 0) explored = explored->next; //if that neighbour has already been explored, then go to the neighbour's neighbour 
				else DFS(G, V, explored->data); //if neighbour not explored, perform DFS from it 
			}
		}
	}
}

int main() {
	Node** G;
	G = new Node * [7];
	for (int i = 0; i <= 6; i++) {
		Node* n;
		n = new Node;
		n->data = 0;
		n->next = NULL;
		G[i] = n;
	}
	CreateGraph(G);
	Queue Q(15);
	int V[7];
	for (int j = 0; j <= 6; j++) {
		V[j] = 0;
	}
	cout << endl << "Traversal using BFS: ";
	BFS(G,Q,V);

	for (int j = 0; j <= 6; j++) {
		V[j] = 0;
	}
	cout <<endl<<"Traversal using DFS: ";
	DFS(G,V,1);
}
