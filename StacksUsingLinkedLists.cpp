
//Stack operations: push(x),pop(),peek(index),StackTop(),isEmpty(),isFull()

/*
Implementation of stacks using linked lists
*/

#include<iostream>
using namespace std;

class Node { //Define node of linked list 
public:
	int data;
	Node* next;
};

class Stack { //Define stack using the header linked list node  
public:
	Node *top;
};

void Display(Node* first) { //Displays the elements of the stack as a linked list starting from the top  
	Node* p;
	p = first;
	while (p->next != NULL) {
		p = p->next;
		cout << p->data << "->";
	}
}

bool isEmpty(Stack st) { //Checks if stack is empty or not 
	if (st.top->next == NULL) return 1;
	else return 0;
}

bool isFull(Stack st) { //Checks if a stack is full or not 
	Node* top;
	top = new Node; //unable to create a new node as the stack is full 
	if (top == NULL) return 1;
	else return 0;
}

int StackTop(Stack st) { //returns the top element of the stack. If stack is empty, returns -1 
	if (isEmpty(st)) return -1;
	else return (st.top->next)->data;
}

void push(Stack *st, int element) { //Pushes element into the stack, if stack is full prints stack overflow 
	if (isFull(*st)) cout << "Stack overflow" << endl;
	else {
		Node* inserted_element;
		inserted_element = new Node;
		inserted_element->data = element;
		inserted_element->next = (st->top)->next;
		(st->top)->next = inserted_element;
	}
}

int pop(Stack* st) { //pops the top element out of the stack and returns its value. If stack is empty, returns -1 
	int x = -1;
	if (isEmpty(*st)) return x;
	else {
		x = ((st->top)->next)->data;
		(st->top)->next = ((st->top)->next)->next;
	}
	return x;
}

int peek(Stack st, int index) { //Lookup element at a position starting from the stak top 
	if (isEmpty(st)) return -1;
	else {
		Node* p;
		p = new Node;
		p = st.top->next;
		for (int i = 1; (p != NULL)&&(i<index); i++) {
			p = p->next;
		}
		if (p == NULL) cout << "Requested index is out of bounds for the linked list.";
		else return p->data;
	}
}

int main() {
	Stack st; //create stack 
	st.top = new Node; //create header node 
	st.top->data = 0; //assign data to the header node 
	st.top->next = NULL; 
	push(&st, 3);
	push(&st, 5);
	push(&st, 7);
	int elem_popped = pop(&st);
	cout << "Element popped = " << elem_popped << endl;
	push(&st, 9);
	Display(st.top);
	cout << "Peeking at index 3. Element = " << peek(st, 3) << endl;
}