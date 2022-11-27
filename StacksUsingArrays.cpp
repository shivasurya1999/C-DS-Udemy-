//Stack operations: push(x),pop(),peek(index),StackTop(),isEmpty(),isFull()
//Use pointers to data structures in callback functions only when the data structure is being modified. Otherwise we can just use the data structure directly in case of accessing elements from it 
/*
Implementation of a stack using array 
*/

#include<iostream>
using namespace std;

class Stack { //Create stack with attributes size,top index and array of stack elements
public:
	int size;
	int top;
	int* s;
};

bool isFull(Stack st) { //If stack is full returns 1, else returns 0
	if (st.top == st.size - 1) return 1;
	else return 0;
}

bool isEmpty(Stack st) { //If stack is empty returns 1, else returns 0
	if (st.top == -1) return 1;
	else return 0;
}

int StackTop(Stack st) { //Returns the top element of stack, returns -1 if the stack is empty 
	if (isEmpty(st)) return -1;
	else return st.s[st.top];
}

void push(Stack* st, int element) { //pushes element into the stack. If stack is full, prints stack overflow
	if (st->top==(st->size)-1) cout << "Stack overflow"<<endl;
	else {
		st->top++;
		(st->s)[st->top] = element;
	}
}

int pop(Stack* st) { //pops element out of the stack and returns it. If stack is empty, prints there are no elements and returns -1
	int x = -1;
	if (st->top == -1) cout << "No elements left to pop out in stack" << endl;
	else {
		x = st->s[st->top];
		st->top--;
	}
	return x;
}

int peek(Stack st, int index) { //peeks at a desired stack index from the top and returns stack element at that index 
	int stack_index = (st.top) - index + 1;
	if (st.top == -1) cout << "Empty stack,nothing to peek" << endl;
	else if (stack_index <= -1) cout << "Index out of stack bounds" << endl;
	else return st.s[stack_index];
}

void printStack(Stack st) { //prints the entire stack 
	if (isEmpty(st)) cout << "Empty stack, nothing to print" << endl;
	else {
		for (int i = st.top; i > -1; i--) {
			cout << st.s[i] << endl;
		}
	}
}

int main() {
	Stack st; //create stack 
	cout << "Enter the number of elements of the stack: ";
	cin >> st.size;
	st.s = new int[st.size]; //allocates memory to the stack array 
	st.top = -1; //by default the top index of an empty stack is -1 
	push(&st, 2);
	push(&st, 5);
	push(&st, 9);
	int x = pop(&st);
	cout << "element popped = " << x<<endl;
	push(&st, 14);
	cout << "Peeking at index 3,the element is: " << peek(st, 3) << endl;
	printStack(st);

}