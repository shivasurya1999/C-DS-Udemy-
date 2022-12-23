/*
C++ code of a binary tree creation (includes iterative traversal)
Code documented only for IterativePreorder as it is the only new function 
*/
#include<iostream>
using namespace std;

class Node {
public:
    Node* lchild;
    int data;
    Node* rchild;
};

class Queue {
private:
    int size;
    int front;
    int rear;
    Node** Q;  // [Node*]*: Pointer to [Pointer to Node]
public:
    Queue(int size);
    ~Queue();
    bool isFull();
    bool isEmpty();
    void enqueue(Node* x);
    Node* dequeue();
};

Queue::Queue(int size) {
    this->size = size;
    front = -1;
    rear = -1;
    Q = new Node * [size];
}

Queue::~Queue() {
    delete[] Q;
}

bool Queue::isEmpty() {
    if (front == rear) {
        return true;
    }
    return false;
}

bool Queue::isFull() {
    if (rear == size - 1) {
        return true;
    }
    return false;
}

void Queue::enqueue(Node* x) {
    if (isFull()) {
        cout << "Queue Overflow" << endl;
    }
    else {
        rear++;
        Q[rear] = x;
    }
}

Node* Queue::dequeue() {
    Node* x = nullptr;
    if (isEmpty()) {
        cout << "Queue Underflow" << endl;
    }
    else {
        front++;
        x = Q[front];
    }
    return x;
}

class Stack {
private:
    int size;
    int top;
    Node** s;
public:
    Stack(int sz);
    bool isFull();
    bool isEmpty();
    void push(Node* element);
    Node* pop();
    Node* top_most();
};

Stack::Stack(int sz) {
    size = sz;
    top = -1;
    s = new Node * [size];
}

bool Stack::isFull() {
    if (size - 1 == top) return 1;
    else return 0;
}

bool Stack::isEmpty() {
    if (top == -1) return 1;
    else return 0;
}

void Stack::push(Node* element) {
    if (!isFull()) {
        top++;
        s[top] = element;
    }
    else cout << "Stack overflow." << endl;
}

Node* Stack::pop() {
    Node* x;
    x = new Node;
    x = NULL;
    if (!isEmpty()) {
        x = s[top];
        top--;
    }
    return x;
}

Node* Stack::top_most() {
    Node* x;
    x = new Node;
    x = NULL;
    if (!isEmpty()) {
        x = s[top];
    }
    return x;
}


class Tree {
private:
    Node* root;
public:
    Tree() { root = nullptr; }
    ~Tree();
    void CreateTree();
    void Preorder() { Preorder(root); }  // Passing Private Parameter in Constructor
    void Preorder(Node* p);
    void IterativePreOrder() { IterativePreorder(root); }
    void IterativePreorder(Node* p);
    Node* getRoot() { return root; }
};

void Tree::CreateTree() {
    Node* p;
    Node* t;
    int x;

    Queue q(25);
    root = new Node;
    cout << "Enter root value: " << flush;
    cin >> x;
    root->data = x;
    root->lchild = nullptr;
    root->rchild = nullptr;
    q.enqueue(root);

    while (!q.isEmpty()) {
        p = q.dequeue();

        cout << "Enter left child value of " << p->data << ": " << flush;
        cin >> x;
        if (x != -1) {
            t = new Node;
            t->data = x;
            t->lchild = nullptr;
            t->rchild = nullptr;
            p->lchild = t;
            q.enqueue(t);
        }

        cout << "Enter right child value of " << p->data << ": " << flush;
        cin >> x;
        if (x != -1) {
            t = new Node;
            t->data = x;
            t->lchild = nullptr;
            t->rchild = nullptr;
            p->rchild = t;
            q.enqueue(t);
        }
    }
}

void Tree::Preorder(Node* p) {
    if (p) {
        cout << p->data << ", " << flush;
        Preorder(p->lchild);
        Preorder(p->rchild);
    }
}

void Tree::IterativePreorder(Node* p) {
    Stack s(20);
    if (p) {
        cout << p->data << ", "; //print root data 
        s.push(p); //push root into stack 
        Node* prev_node;
        prev_node = new Node;
        Node* curr_node;
        curr_node = new Node;
        while (!s.isEmpty()) {
            prev_node = s.top_most(); //peek into stack and get the top element 
            if (prev_node->lchild != NULL) { //if node has left child 
                curr_node = prev_node->lchild; //update current to left child 
                cout << curr_node->data << ", "; //print the current node 
                s.push(curr_node); //push current node into stack 
            }
            else if (prev_node->rchild != NULL) { //if node has right child 
                prev_node = s.pop(); //pop the stack to get the top element 
                curr_node = prev_node->rchild; //update current to right child 
                cout << curr_node->data << ", "; //print the current node
                s.push(curr_node); //push current node into stack
            }
            else { //if node does not have both left and right child 
                Node* null_node;
                null_node = new Node;
                null_node = s.pop(); //pop element out of stack 
                if (!s.isEmpty()) (s.top_most())->lchild = NULL; //make left node of the to element after the previous step pop operation to null because we have already printed its left child 
            }
        }
    }
}

Tree::~Tree() {
    // TODO
}


int main() {

    Tree t;

    t.CreateTree();

    cout << "IterativePreorder: " << flush;
    t.IterativePreorder(t.getRoot());
    cout << endl;

}





