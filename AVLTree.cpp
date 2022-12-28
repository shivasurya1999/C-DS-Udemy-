/*
C++ code for AVL trees 
*/

#include <iostream>
#include<algorithm>
using namespace std;

class Node {
public:
    Node* lchild;
    int data;
    int height;
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

class AVL {
public:
    Node* root;
    AVL() { root = nullptr; };
    
    int NodeHeight(Node* p);
    int BalanceFactor(Node* p);
    void CreateTree();
    void InsertNode(Node* p,Node* t,int element);
    bool isTreeUnbalanced();
    int BalanceType(int element);
    void LLBalance();
    void LRBalance();
    void RRBalance();
    void RLBalance();
    void BalanceTree(int element);
    void Inorder(Node* p);
    void LevelOrder(Node* p);
};

int AVL::NodeHeight(Node* p) {
    if (p) {
        if ((p->lchild) && (p->rchild)) {
            return std::max(NodeHeight(p->lchild) + 1, NodeHeight(p->rchild) + 1);
        }
        else if (p->lchild) return NodeHeight(p->lchild) + 1;
        else if (p->rchild) return NodeHeight(p->rchild) + 1;
        else return 1;
    }
    else return 0;
}

int AVL::BalanceFactor(Node* p) {
    if (p) return NodeHeight(p->lchild) - NodeHeight(p->rchild);
}

void AVL::InsertNode(Node* p, Node* t, int element) {
    Node* element_node;
    element_node = new Node;
    element_node->data = element;
    element_node->height = 1;
    element_node->lchild = NULL;
    element_node->rchild = NULL;
    while (element != -1) {
        if (p) {
            if (element < p->data) {
                t = p;
                p = p->lchild;
            }
            else if (element > p->data) {
                t = p;
                p = p->rchild;
            }
            else {
                cout << "Element " << element << "exists in the tree already not inserting again." << endl;
            }
        }
        else {
            if (t) {
                if (element < t->data) t->lchild = element_node;
                else t->rchild = element_node;
                break;
            }
        }
    }
}

bool AVL::isTreeUnbalanced() {
    if (std::abs(BalanceFactor(root)) > 1) return 1;
    else return 0;
}

int AVL::BalanceType(int element){
    if (element < root->data) {
        if (root->lchild) {
            if (element < root->lchild->data) return 1; //LL imbalance
            else return 2; //LR imbalance 
        }
    }
    else {
        if (root->rchild) {
            if (element > root->rchild->data) return 3; //RR imbalance 
            else return 4; //RL imbalance 
        }
    }
}

void AVL::LLBalance() {
    Node* n;
    n = new Node;
    n = root;
    root = root->lchild;
    n->lchild = root->rchild;
    root->rchild = n;
}

void AVL::LRBalance() {
    Node* n;
    n = new Node;
    n = root;
    Node* t;
    t = new Node;
    root = root->lchild->rchild;
    t = root->lchild;
    root->lchild = n->lchild;
    n->lchild = root->rchild;
    root->rchild = n;
    root->lchild->rchild = t;
}

void AVL::RRBalance() {
    Node* n;
    n = new Node;
    n = root;
    root = root->rchild;
    n->rchild = root->lchild;
    root->lchild = n;
}

void AVL::RLBalance() {
    Node* n;
    n = new Node;
    n = root;
    Node* t;
    t = new Node;
    root = root->rchild->lchild;
    t = root->rchild;
    root->rchild = n->rchild;
    n->rchild = root->lchild;
    root->lchild = n;
    root->rchild->lchild = t;
}

void AVL::BalanceTree(int element) {
    if (BalanceType(element) == 1) {
        LLBalance();
    }
    else if (BalanceType(element) == 2) {
        LRBalance();
    }
    else if (BalanceType(element) == 3) {
        RRBalance();
    }
    else if (BalanceType(element) == 4) {
        RLBalance();
    }
}

void AVL::CreateTree() {
    cout << "Enter the root node: ";
    int element;
    cin >> element;
    root = new Node;
    root->data = element;
    root->height = 1;
    root->lchild = NULL;
    root->rchild = NULL;
    cout << "Enter the next node. Enter -1 to finish creation: ";
    cin >> element;
    Node* p;
    p = new Node;
    p = root;
    Node* t;
    t = new Node;
    t = NULL;
    while (element != -1) {
        InsertNode(p, t, element);
        if (isTreeUnbalanced()) {
            BalanceTree(element);
        }
        p = root;
        t = NULL;
        cout << "Enter the next node. Enter -1 to finish creation: ";
        cin >> element;
    }
}

void AVL::Inorder(Node* p) { //Inorder traversal for BST and printing of nodes inorder 
    if (p) {
        Inorder(p->lchild);
        cout << p->data << ", ";
        Inorder(p->rchild);
    }
}

void AVL::LevelOrder(Node* p) {
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

int main() {
    AVL t;
    t.CreateTree();
    /*t.Inorder(t.root);*/
    cout << "New root is : " << t.root->data<<endl;
    cout << "Level order traversal of the balanced AVL tree: "; 
    t.LevelOrder(t.root);
    Node* q;
    q = new Node;
    q = t.root;
    Node* r;
    r = new Node;
    r = NULL;
    t.InsertNode(q, r, 12);
    q = t.root;
    r = NULL;
    t.InsertNode(q, r, 13);
    if (t.isTreeUnbalanced()) {
        t.BalanceTree(13);
    }
    cout << endl;
    cout << "New root is : " << t.root->data << endl;
    cout << "Level order traversal of the balanced AVL tree: ";
    t.LevelOrder(t.root);
}




