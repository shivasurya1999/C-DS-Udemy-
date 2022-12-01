/*
Author: Shiva Surya Lolla
Date: 01-12-2022
1. Below code implements queue operations using arrays. The operations are enqueue(),dequeue(),isEmpty(),isFull()
2. Implementation of circular queue using arrays 
*/

#include<iostream>
using namespace std;

class Queue { //initialize queue with first index, last index, queue size and array used to maintain the queue 
public:
	int first;
	int last;
	int size;
	int* Q;
};

bool isEmpty(Queue q) { //If queue is empty, will return 1
	if (q.first == q.last) return 1;
	else return 0;
}

bool isFull(Queue q) { //if queue is full will return 1
	if (q.last == q.size - 1) return 1;
	else return 0;
}

void enqueue(Queue* q,int element) {//enqueues "element" into the queue 
	if (isFull(*q)) cout << "Queue is full. Cannot add element "<<element<< endl; 
	else { //need to enqueue only if queue has space 
		q->last++; //increase the last index 
		q->Q[q->last] = element; //add element to the queue 
	}
}

int dequeue(Queue* q) {//dequeues first element of the queue and returns its value 
	int x = -1; //return -1 if queue is empty 
	if (isEmpty(*q)) cout << "Queue is empty. Nothing to dequeue." << endl;
	else { //need to dequeue only if queue has elements 
		x = q->Q[q->first + 1]; //stores first elemsnt 
		cout << "Dequeuing " << x << endl;
		q->first++; //increments the first index, note that when we increment the first index, the queue size is remaining the same. So it is not actual deletion but just an illusion of deletion 
	}
	return x;
}

void DisplayQueue(Queue q) { //Diplays the queue 
	cout << "first-> ";
	int p;
	for (p = q.first + 1; p <= q.last; p++) {
		cout << q.Q[p]<<",";
	}
	cout << " <-last"<<endl;
}

/*
Circular queue has an advantage over normal queue because there can be elements inserted even if the first index approaches the end of the queue in circular queue
This requires incrementing the first index using modulo because in case of the first operator reaching until queue size, it is incremented to reach the first index again in this case 
Even the last index is incremented in a similar manner as the first 
*/

void enqueueCircular(Queue* q,int element) { //enqueue element in circular queue 
	if ((q->last + 1) % q->size == q->first) cout << "Circular queue overflow. Cannot add element "<<element<< endl; //modulo operator is used in the case of spaces before the first element for more element insertion 
	else {
		q->last = (q->last + 1) % q->size; //increment last using modulo 
		q->Q[q->last] = element; //insert element 
	}
}

int dequeueCircular(Queue* q) { //dequeue element from a circular queue and return the element 
	int x = -1;
	if (q->first == q->last) cout << "Circular queue underflow" << endl;
	else {
		q->first = (q->first + 1) % (q->size); //increment first using modulo 
		x = q->Q[q->first]; //save the element to be dequeued 
	}
	return x; //return the dequeued element 
}

void DisplayCircularQueue(Queue q) { //Display circular queue 
	int p;
	cout << "first-> ";
	for (p = (q.first + 1) % (q.size); p != q.first; p = (p + 1) % (q.size)) {
		cout << q.Q[p] << ",";
	}
	cout << " <-last" << endl;
}

int main() {
	Queue q; //initialize a queue 
	cout << "enter the queue size: " << endl;
	cin >> q.size;
	q.first = -1;
	q.last = -1;
	q.Q = new int[q.size]; //create array for the queue 
	enqueue(&q, 18);
	enqueue(&q, 12);
	enqueue(&q, 9);
	enqueue(&q, 6);
	enqueue(&q, 3);
	DisplayQueue(q);
	dequeue(&q);
	DisplayQueue(q);

	Queue cq; //initialize a circular queue 
	cout << "Enter the circular queue size: " << endl;
	cin >> cq.size;
	cq.first = 0;
	cq.last = 0;
	cq.Q = new int[cq.size]; //create array for the circular queue 
	enqueueCircular(&cq, 2);
	enqueueCircular(&cq, 4);
	enqueueCircular(&cq, 6);
	enqueueCircular(&cq, 8);
	enqueueCircular(&cq, 10);
	DisplayCircularQueue(cq);
	dequeueCircular(&cq);
	dequeueCircular(&cq);
	enqueueCircular(&cq, 12);
	enqueueCircular(&cq, 14);
	enqueueCircular(&cq, 16);
	DisplayCircularQueue(cq);
}