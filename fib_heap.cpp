#include <cmath>
#include <iostream>
#include "fib_heap.hpp"
using namespace std;

//Fibbonaci Heap
node* FibonacciHeap::Make_Heap()
{
        
    node* np;
    np = NULL;
    return np;
}//Create empty heap

void FibonacciHeap::Insert(int weight_, int vertex_)
{
        
    //Create empty heap, with one node
    node *newNode = New_Heap_With_Node(weight_, vertex_);
    
    //Union new heap and root heap
    H = Meld(H, newNode);
}//Inserts node with argument values into existing heap

node* FibonacciHeap::New_Heap_With_Node(int weight_,int vertex_)
{

    //Create new node struct and populate with data/defualt values
    node* newNode = new node;
    newNode->weight = weight_;
    newNode->rank = 0;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->left = newNode;
    newNode->right = newNode;
    newNode->mark = '0';
    newNode->vertex = vertex_;
    return newNode;
}//Technically creates new heap with one node, but since that is represented by a pointer to root node, this is the same thing

node* FibonacciHeap::Meld(node* N1,node* N2)
{
    
    //Merge root linked lists
    node*p = N1->left;
    (N2->right)->left = N1;
    N1->left = N2->right;
    N2->right = p;
    p->left = N2;
    
    //Return lowest weight as new root
    if(N1->weight<N2->weight){
        return N1;
    }
    else{
        return N2;
    }
    size++; //Only works for insertion
}//Merge root nodes, return lowest weight node

node* FibonacciHeap::Extract_Min()
{
    node* p=H;
    Delete_Min();
    return p;
}

void FibonacciHeap::Delete_Min()
{
    
    
    //If empty heap, dont do anything
    if (H != NULL){
        //While there are children, remove them from children and place in root
        do {
            //Get current child
            node* c = H->child;
            
            //Case: last child
            if(c->left==c){
                //Eliminate Child List
                H->child=NULL;
            }
            //Case at least one more child
            else{
                //Assign new child to H
                H->child = c->left; //Doesnt matter which one, we will remove them all
                
                //Merge linked list
                (c->left)->right=c->right;
                (c->right)->left=c->left;
            }
            
            //Place c in root list, for now doesnt matter if sorted, will be consolidated
            (H->right)->left=c;
            c->right=(H->right);
            c->left = H;
            H->right = c;
            c->parent=NULL;
            
        }
        while (H->child!=NULL);
    
    
        //Check that there are other root nodes
        if(H->left==H){
            //There where no other root nodes, and no children to add to the root
            H = NULL;
            size--;
        }
        else{
            //There are roots to consolidate
            (H->right)->left=H->left;
            (H->left)->right=H->right;
            
            //No longer need H, pass another root to consolidate, which will return new root
            H=(H->left);
            size--;
            
            Consolidate();
        }
        
    }
}//Removes root node, links children with root nodes and consolidates FHeap

node* FibonacciHeap::Link(node* h1, node* h2)
{
    //This shouldnt affect the root pointer, so it will not be touched
    //Links two roots
    node*root;
    node*child;
    if(h1->weight<h2->weight){
        root = h1;
        child = h2;
    }
    else{
        root = h2;
        child = h1;
    }
    

    //Set child's new parent
    child->parent=root;
    //remove child from root list
    (child->right)->left=child->left;
    (child->left)->right=child->right;
    
    //insert child into children
    child->left = root->child;
    child->right = (root->child)->right;
    (child->left)->right = child;
    (child->right)->left=child;
    
    //If new child is less, update
    if(child->weight<(root->child)->weight){
        root->child = child;
    }
    
    //Increase degree of new root
    (root->rank)++;
    return root;
} 

void FibonacciHeap::Consolidate()
{
    int max_depth = ceil(log2(size)); //Figure out the maximum depth possible
    
    node *ranks[max_depth]; //Use array to keep track of conflicting degrees
    
    //Array for checking depth
    node*np=NULL;
    for(int i=0;i<max_depth;i++){
        ranks[i]=np;
    }
    
    node*p = H->left;
    //For each root node, check if conflicting degree
    do{
        int r = p->rank;
        
        do{
            //If conflict, link conflicting trees, and try to store new tree.
            p=Link(p,ranks[r]);
            ranks[r]=np;
            r=p->rank;
        }
        while(ranks[r]!=NULL);
        ranks[r]=p;
        p=p->left;
    }
    while(p!=H);
    
    //Search for new minimum root
    p=H->left;
    node* root=H;
    do{
        if(p->weight<root->weight){
            root=p;
        }
        p=p->left;
    }
    while(p!=H);
    
    H=root;
}

void FibonacciHeap::Decrease_Key(int vertex_,int del_){
        //Decreases the node associated with vertex_'s key by del_, and places node as root node
}

int main(){
	cout<<"Cool Beans"<<endl;
	return 0;
}