/*
C++ code for AVL trees 
Created by: Shiva Surya Lolla
Date: 28th December 2022
Why AVL trees: AVL trees are height balancing BSTs. Their height is O(logn) while height of BSTs is O(n). Therefore searching an element is much faster in AVL trees 
1. Create AVL tree from user input 
2. Insert node in AVL tree 
2. Delete node in AVL tree and balance the tree 
*/

#include <iostream>
#include<algorithm>
using namespace std;

class Node { //Node class same as BST but with an additional 'height' field for each node that gives its height from the leaf nodes 
public:
    Node* lchild;
    int data;
    int height;
    Node* rchild;
};

//Use of the below queue is for level order traversal of AVL tree 
class Queue { //Create a queue class with size,front,rear and an array that contains Node* type elements 
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

class AVL { //AVL tree class that creates a default root node of NULL type 
public:
    Node* root;
    AVL() { root = nullptr; };
    
    int NodeHeight(Node* p);
    int BalanceFactor(Node* p);
    void CreateTree();
    void InsertNode(Node* p,Node* t,int element);
    Node* FindInOrderPOrS(Node* p);
    void Delete(Node* p, int element);
    bool isTreeUnbalanced();
    int BalanceType(int element);
    void LLBalance();
    void LRBalance();
    void RRBalance();
    void RLBalance();
    void BalanceTree(int element);
    void DeleteElementAVL(Node* p, int element);
    void Inorder(Node* p);
    void LevelOrder(Node* p);
};

int AVL::NodeHeight(Node* p) { //Function to give the node height. height of single node is considered as 1
    if (p) {
        if ((p->lchild) && (p->rchild)) { //If a node has both its left and right children 
            return std::max(NodeHeight(p->lchild) + 1, NodeHeight(p->rchild) + 1); //return max height of left and right child 
        }
        else if (p->lchild) return NodeHeight(p->lchild) + 1; //if only left child is there, return height of left child +1
        else if (p->rchild) return NodeHeight(p->rchild) + 1; //if only right child is there return height of right child +1
        else return 1; //if no children 
    }
    else return 0; //if p is null 
}

int AVL::BalanceFactor(Node* p) { //returns the balance factor which is equal to (height of lchild - height of rchild)
    if (p) return NodeHeight(p->lchild) - NodeHeight(p->rchild);
}

void AVL::InsertNode(Node* p, Node* t, int element) { //This function just inserts an element into the tree without balancing the tree. p is the pointer to root, t is its tail pointer 
    Node* element_node;
    element_node = new Node;
    element_node->data = element;
    element_node->height = 1;
    element_node->lchild = NULL;
    element_node->rchild = NULL;
    while (element != -1) { //if user inputs -1 stop inserting 
        if (p) { //keep moving until 'p' is null 
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
        else { //if 'p' has become null, then its time to insert 
            if (t) {
                if (element < t->data) t->lchild = element_node; //insertion is done as the left child of tail pointer 
                else t->rchild = element_node; //insertion is done as the right child of tail pointer 
                break;
            }
        }
    }
}

Node* AVL::FindInOrderPOrS(Node* p) { //returns the inorder successor if existing in the tree, else the inorder predecessor. If left and right child of p are null, then returns NULL
    Node* t;
    t = new Node;
    t = p;
    if (p->rchild) { //to find inorder successor go to the right child of the node and then keep going left until null 
        t = p->rchild;
        while (t->lchild) {
            t = t->lchild;
        }
        return t;
    }
    else if (p->lchild) { //to find inorder predecessor go to the left child of the node and then keep going right until null
        t = p->lchild;
        while (t->rchild) {
            t = t->rchild;
        }
        return t;
    }
    else return NULL; //if no inorder predecessor or successor, return NULL 
}

void AVL::Delete(Node* p, int element) { //Function that deletes element from tree without balancing it  
    //create a pointer that points to the node 'p'
    Node* n;
    n = new Node;
    n = p;
    //create a null pointer that follows the pointer 'n'
    Node* t;
    t = new Node;
    t = NULL;
    while (n) { //keep looping until 'n' points to null 
        if (n->data > element) { //if the node value to which n points to is greater than the new_elem_node value 
            t = n; //update the tail pointer to the node that 'n' is pointing to 
            n = n->lchild; //update 'n' to point to the left child of the current node it points to 
        }
        else if (n->data < element) { //if the node value to which n points to is less than the new_elem_node value
            t = n; // update the tail pointer to the node that 'n' is pointing to
            n = n->rchild; //update 'n' to point to the right child of the current node it points to 
        }
        else {
            //get inorder successor or predecessor 
            Node* replace_node;
            replace_node = new Node;
            replace_node = FindInOrderPOrS(n);
            if (replace_node) { //if found
                int elem = replace_node->data; //copy data into an int variable 
                Delete(n, replace_node->data); //Delete that node 
                n->data = elem; //copy the data of the replace_node deleted previoudly into the n
                return;
            }
            else { //if no successor or predecessor then we have to remove that node from the BST 
                if (t) {
                    if (n == t->lchild) t->lchild = NULL; //if 'n' is the left child of t
                    else t->rchild = NULL;
                }
                else cout << endl << "Requirement was to delete the only node in the BST. Cannot do that. " << endl; //If BST has only one node, we cannot delete it 
                return;
            }
        }
    }
}


bool AVL::isTreeUnbalanced() { //returns 1 if tree is unbalanced. else returns 0 
    if (std::abs(BalanceFactor(root)) > 1) return 1; //if balance factor of the root is 2, then it has become unbalanced 
    else return 0;
}

int AVL::BalanceType(int element){ //returns 1 for LL, 2 for LR, 3 for RR and 4 for RL imbalance 
    if (element < root->data) { //if after the insertion, we check the inserted element's location wrt root and we find that we have to move to the left in first step, and then again to the left, then it is LL
        if (root->lchild) {
            if (element < root->lchild->data) return 1; //LL imbalance
            else return 2; //LR imbalance is step 1 to the left and then step 2 to the right 
        }
    }
    else {
        if (root->rchild) {
            if (element > root->rchild->data) return 3; //RR imbalance is step 1 to the right and then step 2 to the right 
            else return 4; //RL imbalance is step 1 to the right and then step 2 to the left 
        }
    }
}

void AVL::LLBalance() { //function to balance LL imbalance 
    //copy root node to another node 
    Node* n;
    n = new Node;
    n = root;
    //the below sequence of steps achieve LL balance 
    root = root->lchild;
    n->lchild = root->rchild;
    root->rchild = n;
}

void AVL::LRBalance() { //function to balance LR imbalance 
    //copy root to another node 
    Node* n;
    n = new Node;
    n = root;
    Node* t;
    t = new Node;
    //the below sequence of steps achieve LR balance
    root = root->lchild->rchild;
    //copy the new roots left child into 't' for using in the future 
    t = root->lchild;
    root->lchild = n->lchild;
    n->lchild = root->rchild;
    root->rchild = n;
    root->lchild->rchild = t;
}

void AVL::RRBalance() { //function to balance RR imbalance
    //copy root to another node 
    Node* n;
    n = new Node;
    n = root;
    //the below sequence of steps achieve RR balance
    root = root->rchild;
    n->rchild = root->lchild;
    root->lchild = n;
}

void AVL::RLBalance() { //function to balance RL imbalance
    //copy root to another node 
    Node* n;
    n = new Node;
    n = root;
    Node* t;
    t = new Node;
    //the below sequence of steps achieve RL balance
    root = root->rchild->lchild;
    //copy the new roots right child into 't' for using in the future 
    t = root->rchild;
    root->rchild = n->rchild;
    n->rchild = root->lchild;
    root->lchild = n;
    root->rchild->lchild = t;
}

void AVL::BalanceTree(int element) { //depending upon the type of imbalance, this function balances the tree 
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

void AVL::CreateTree() { //Function to create a tree starting with the root node taking user input. If the user enters -1, then the tree creation is complete 
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
    //pointer to root initially 
    Node* p;
    p = new Node;
    p = root;
    //tail pointer to 'p'
    Node* t;
    t = new Node;
    t = NULL;
    while (element != -1) {
        InsertNode(p, t, element); //Insert node in tree 
        if (isTreeUnbalanced()) { //check if tree is unbalanced 
            BalanceTree(element); //balance tree 
        }
        //reinitializing 'p' and 't' for using in the next insertion
        p = root;
        t = NULL;
        cout << "Enter the next node. Enter -1 to finish creation: ";
        cin >> element;
    }
}

void AVL::DeleteElementAVL(Node* p, int element) { //Function to delete node from AVL tree and then balance the resulting tree 
    if (p) {
        Delete(p, element); //perform deletion without balancing yet 
        if (isTreeUnbalanced()) { //check if tree is unbalanced 
            if (element < root->data) { //if the deleted element is to the left of the root, then the imbalance must be to the right of the root
                if (BalanceFactor(root->rchild) <= 0) RRBalance();  //if the balance factor of the right child of the root is 0 or -1, it means that there is RR imbalance (incase of 0, we can choode RL also) 
                else RLBalance(); //else there is RL imbalalnce that needs to be balanced 
            }
            else {
                if (BalanceFactor(root->lchild) >= 0) LLBalance(); //if the balance factor of the left child of the root is 0 or 1, it means that there is LL imbalance (incase of 0, we can choode LR also) 
                else LRBalance(); //else there is LR imbalalnce that needs to be balanced
            }
        }
    }
}

void AVL::Inorder(Node* p) { //Recursive Inorder traversal for BST and printing of nodes inorder 
    if (p) {
        Inorder(p->lchild);
        cout << p->data << ", ";
        Inorder(p->rchild);
    }
}

void AVL::LevelOrder(Node* p) { //Function to print level order traversal of a tree with input as root of the tree. Uses queue for traversal 
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
    t.CreateTree();  //Create tree vis user inputs 
    /*t.Inorder(t.root);*/
    cout << "New root is : " << t.root->data<<endl;
    cout << "Level order traversal of the balanced AVL tree: "; 
    t.LevelOrder(t.root); //level order traversal after creating the tree 
    Node* q;
    q = new Node;
    q = t.root;
    Node* r;
    r = new Node;
    r = NULL;
    //user input given to verify for the below further inputs : 7,6,10,11,8,9 and then -1  
    t.InsertNode(q, r, 12);
    q = t.root;
    r = NULL;
    t.InsertNode(q, r, 13);
    if (t.isTreeUnbalanced()) {
        t.BalanceTree(13);
    }
    cout << endl;
    cout << "New root is : " << t.root->data << endl;
    cout << "Level order traversal of the balanced AVL tree after insertion of 12 and 13: ";
    t.LevelOrder(t.root); 
    t.DeleteElementAVL(t.root, 12);
    t.DeleteElementAVL(t.root, 13);
    cout << endl;
    cout << "Level order traversal of the balanced AVL tree after deletion of 12 and 13: ";
    t.LevelOrder(t.root);
}




