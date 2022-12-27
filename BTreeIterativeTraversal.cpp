/*
* Created by: Shiva Surya 
* Date: 24 December 2022 
C++ code of a binary tree with additional functions of :
1. Iterative preorder traversal 
2. Level order traversal 
3. Number of nodes of tree 
4. Height of tree 
5. Number of leaf nodes of tree 
*/
#include<iostream>
using namespace std;

class Node { //Create a binary tree node class with left child, right child and data fields 
public:
    Node* lchild;
    int data;
    Node* rchild;
};

class Queue { //Create a queue class with size,front,rear and an array that contains Nod* type elements 
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

Queue::Queue(int size) { //Default constructor 
    this->size = size;
    front = -1;
    rear = -1;
    Q = new Node * [size];
}

Queue::~Queue() { //destructor 
    delete[] Q;
}

bool Queue::isEmpty() { //returns 1 if queue is empty 
    if (front == rear) {
        return true;
    }
    return false;
}

bool Queue::isFull() { //retirns 1 if queue is full 
    if (rear == size - 1) {
        return true;
    }
    return false;
}

void Queue::enqueue(Node* x) { //enqueue the queue with tree node pointer  
    if (isFull()) {
        cout << "Queue Overflow" << endl;
    }
    else {
        rear++;
        Q[rear] = x;
    }
}

Node* Queue::dequeue() { //dequeue the queue and return the dequeued node address 
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

class Stack { //class for stack for usage in iterative tree traversal. Consists of stack size, top index and array holding elements of type Node*
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

Stack::Stack(int sz) { //Default constructor 
    size = sz;
    top = -1;
    s = new Node * [size];
}

bool Stack::isFull() { //returns 1 if stack is full 
    if (size - 1 == top) return 1;
    else return 0;
}

bool Stack::isEmpty() { //returns 1 if stack is empty 
    if (top == -1) return 1;
    else return 0;
}

void Stack::push(Node* element) { //pushes node address into stack 
    if (!isFull()) {
        top++;
        s[top] = element;
    }
    else cout << "Stack overflow." << endl;
}

Node* Stack::pop() { //pop node address from stack 
    Node* x;
    x = new Node;
    x = NULL;
    if (!isEmpty()) {
        x = s[top];
        top--;
    }
    return x;
}

Node* Stack::top_most() { //peek into the stack and return topmost node address without popping the stack 
    Node* x;
    x = new Node;
    x = NULL;
    if (!isEmpty()) {
        x = s[top];
    }
    return x;
}


class Tree { //Tree class
private:
    Node* root; //root node of tree 
public:
    Tree() { root = nullptr; } //default constructor 
    ~Tree(); //destructor 
    void CreateTree();
    void Preorder() { Preorder(root); }  // Passing Private Parameter in Constructor
    void Preorder(Node* p);
    void IterativePreOrder() { IterativePreorder(root); }
    void IterativePreorder(Node* p);
    Node* getRoot() { return root; }
    void LevelOrder(Node* p);
    int CountOfNodes(Node* p);
    int Height(Node* p);
    int CountLeafNodes(Node* p);
};

void Tree::CreateTree() { //create a tree using user input 
    Node* p;
    Node* t;
    int x;

    Queue q(25);
    root = new Node;
    cout << "Enter root value: " << flush;
    cin >> x; //user enters the root node value of the tree 
    root->data = x;
    root->lchild = nullptr;
    root->rchild = nullptr;
    q.enqueue(root); //root is enqueued into q 

    while (!q.isEmpty()) { //while q is not empty the elements are dequeued one by one and left and right nodes need to be entered by user for creating them 
        p = q.dequeue();

        cout << "Enter left child value of " << p->data << ": " << flush;
        cin >> x;
        if (x != -1) { //if user enters -1, it means that there is no left child of p 
            t = new Node;
            t->data = x;
            t->lchild = nullptr;
            t->rchild = nullptr;
            p->lchild = t;
            q.enqueue(t); //left child is enqueued 
        }

        cout << "Enter right child value of " << p->data << ": " << flush;
        cin >> x;
        if (x != -1) { //if user enters -1, it means that there is no right child of p 
            t = new Node;
            t->data = x;
            t->lchild = nullptr;
            t->rchild = nullptr;
            p->rchild = t;
            q.enqueue(t); //right child is enqueued 
        }
    }
}

void Tree::Preorder(Node* p) { //prints preorder traversal of a binary tree using recursion 
    if (p) {
        cout << p->data << ", " << flush;
        Preorder(p->lchild);
        Preorder(p->rchild);
    }
}

void Tree::IterativePreorder(Node* p) { //prints iterative preorder traversal of a binary tree using recursion
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

void Tree::LevelOrder(Node* p) { //Function that prints level order traversal of a tree 
    Queue q(20); //initialize queue 
    cout << p->data << ", "; //print the root 
    q.enqueue(p); //enqueue the root for getting its left and right children 
    while (!q.isEmpty()) { //repeat until queue is not empty 
        Node* n = q.dequeue(); //dequeue q
        if (n->lchild) { //if left child exists 
            cout << n->lchild->data << ", "; //print it 
            q.enqueue(n->lchild); //store it in queue for printing its left and right children in future 
        }
        if (n->rchild) {  //if right child exists
            cout << n->rchild->data << ", "; //print it 
            q.enqueue(n->rchild); //store it in queue for printing its left and right children in future
        }
    }
}

int Tree::CountOfNodes(Node* p) { //Don't run this with iterative preorder because iterative preorder changes the original tree. This function returns the number of tree nodes 
    if (!p) return 0;
    else return CountOfNodes(p->lchild) + CountOfNodes(p->rchild) + 1; //Current node + number of left children + number of right children 
}

int Tree::Height(Node* p) { //function to return tree's height. height of single node is considered as 1  
    if (p) {
        if ((p->lchild) && (p->rchild)) {
            return std::max(Height(p->lchild) + 1, Height(p->rchild) + 1); //return max height of left and right child 
        }
        else if (p->lchild) return Height(p->lchild) + 1; //return height of left child +1
        else if (p->rchild) return Height(p->rchild) + 1; //return height of right child +1
        else return 1;
    }
    else return 0;
}

int Tree::CountLeafNodes(Node* p) { //Don't run this with iterative preorder because iterative preorder changes the original tree. This function returns the number of leaf nodes of tree  
    if ((!p->lchild) && (!p->rchild)) return 1; //if both left and right children are null then it is a leaf node 
    else {
        if(!p->lchild) return CountLeafNodes(p->rchild); //if left child null run the function with right child 
        else if(!p->rchild) return CountLeafNodes(p->lchild); //if right child null run the function with left child 
        else return CountLeafNodes(p->lchild) + CountLeafNodes(p->rchild); //proceed to left and right children to count leaf nodes at or after them 
    }
}

Tree::~Tree() { //destructor 
    // TODO
}


int main() {

    Tree t; //initialize tree 

    t.CreateTree(); //create a tree 

    //cout << "IterativePreorder: " << flush;
    //t.IterativePreorder(t.getRoot());
    //cout << endl;
    cout << "Level order traversal: ";
    t.LevelOrder(t.getRoot()); //print level order traversal 

    cout << "Number of nodes in the tree: " << t.CountOfNodes(t.getRoot()) << endl;
    cout << "Height of the tree: " << t.Height(t.getRoot()) << endl;
    cout << "Number of leaf nodes in the tree: " << t.CountLeafNodes(t.getRoot()) << endl;

}





