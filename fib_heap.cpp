#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

bool DEBUG=0;

struct node
{
    int rank; //Rank of Node
    char mark; //Is node Marked? "0"==No, "1"==Yes
    int vertex; //Vertex that node represents
    int weight; //Weight of least edge attatched to node
    node* parent; //Pointers relative to node
    node* child;
    node* left;
    node* right;
};


class FibonacciHeap{
private:
    int size; //Total size of heap
    node* H; //root node
public:
    node* Make_Heap();
    void Insert(int, int);
    node* New_Heap_With_Node(int,int);
    void Meld(node*);
    void Display_Heap(void);
    void Display_Node(node* p);
    void Delete_Min(void);
    node* Extract_Min(void);
    node* Link(node*, node*);
    void Consolidate(void);
    void Decrease_Key(int,int);
    FibonacciHeap()
    {
        H = Make_Heap();
        size = 0;
    }
};

//Fibbonaci Heap
node* FibonacciHeap::Make_Heap()
{
    node* np = NULL;
    return np;
}//Create empty heap

void FibonacciHeap::Insert(int weight_, int vertex_)
{   
    //Create empty heap, with one node 
    //Union new heap and root heap
    //cout<<"Inserting:"<<endl;
    node *p = New_Heap_With_Node(weight_,vertex_);
    Meld(p);
    //Display_Node(p);
}//Inserts node with argument values into existing heap


node* FibonacciHeap::New_Heap_With_Node(int weight_,int vertex_)
{
    //Create new node struct and populate with data/defualt values
    node* p = new node;

    p->weight = weight_;
    p->vertex = vertex_;
    p->rank = 0;
    p->mark = '0';

    p->parent = NULL;
    p->child = NULL;
    p->left = p;
    p->right = p;
    return p;
}//Technically creates new heap with one node, but since that is represented by a pointer to root node, this is the same thing


void FibonacciHeap::Display_Node(node* p){
    cout<<"Node"<<endl;
    cout<<"    Vertex: "<<p->vertex<<endl;
    cout<<"    Weight: "<<p->weight<<endl;
    cout<<"    Rank: "<<p->rank<<endl;
    cout<<"    Marked: "<<p->mark<<endl;
    cout<<"    Left: "<<p->left->vertex<<endl;
    cout<<"    Right: "<<p->right->vertex<<endl;
    if(p->parent!=NULL)
        cout<<"    Parent: "<<p->parent->vertex<<endl;
    if(p->child!=NULL)
        cout<<"    Child: "<<p->child->vertex<<endl;
    
    
}


void FibonacciHeap::Meld(node* p)
{
    
    node*np=NULL;
    if(H==np){
        //No current elements, simply return node
        //cout<<"    Empty Heap"<<endl;
        H=p;
    }
    else{
        
        //Merge root linked lists
        node* x = p->right;
        p->right=H->right;
        (H->right)->left=p;
        H->right = x;
        x->left = H;

        //Return lowest weight as new root
        //cout<<p->weight<<"<"<<H->weight<<"?"<<endl;
        if(p->weight<H->weight){
            H=p;
        }
    }

    size++; //Only works for insertion
}//Merge root nodes, return lowest weight node

void FibonacciHeap::Display_Heap()
{
    if(H==NULL){
        cout<<"No nodes in heap!"<<endl;
    }
    else{
        cout<<size<<endl;
        cout<<"Root Rank: "<<H->rank<<endl;
        node* p=H;
        do{
            cout<<p->vertex<<"("<<p->weight<<")->";
            p=p->left;
        }
        while(p!=H);
        cout<<endl;
    }
    
    
}

node* FibonacciHeap::Extract_Min()
{
    node* p=H;
    if(DEBUG){cout<<"Extracting: "<<p->vertex<<endl;}
    Delete_Min();
    return p;
}

void FibonacciHeap::Delete_Min()
{
    //If empty heap, dont do anything
    if (H != NULL){
        //While there are children, remove them from children and place in root
        while (H->child!=NULL){
            if(DEBUG){cout<<"Child Found, Adding to Root."<<endl;}
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
        


        //Check that there are other root nodes
        if(H->left==H){
            //There where no other root nodes, and no children to add to the root
            H = NULL;
            size--;
        }
        else{
            if(DEBUG){cout<<"Consolidating"<<endl;}
            
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
    if(DEBUG){cout<<h1->weight<<"<"<<h2->weight<<"?"<<endl;}
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
    if(root->child!=NULL){
        child->left = root->child;
        child->right = (root->child)->right;
        (child->left)->right = child;
        (child->right)->left=child;
        //If new child is less, update
        if(child->weight<(root->child)->weight){
            root->child = child;
        }
    }
    else{
        root->child=child;
        child->left=child;
        child->right=child;
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
    for(int i=0;i<max_depth;i++){
        ranks[i]=NULL;
    }

    node*p = H;
    //For each root node, check if conflicting degree
    do
    {
        int r = p->rank;
        if(DEBUG){cout<<"Vertex: "<<p->vertex<<" Rank: "<<p->rank<<endl;}
        while(ranks[r]!=NULL)
        {
            //If conflict, link conflicting trees, and try to store new tree.
            if(DEBUG){cout<<"    Conflict: "<<ranks[r]->vertex<<","<<p->vertex<<endl;}
            if(p==H||ranks[r]==H){
                p=Link(p,ranks[r]);
                H=p;
            }
            else{
                p=Link(p,ranks[r]);
            }
            ranks[r]=NULL;
            r=p->rank;
        }
        
        ranks[r]=p;
        p=p->left;
    }
    while(p!=H);
    

    //Search for new minimum root
    p=H;
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
    //Cut node and move to root
    //Cut stuff
}//Decreases the node associated with vertex_'s key by del_, and places node as root node




int main(){
	FibonacciHeap F; //Create new Heap

    
    srand (time(NULL));
    int max;
    cin>>max;
    for(int i = 1;i<=max;i++){
        int weight = rand()%100;
        F.Insert(weight,i);
    }
    F.Display_Heap();
    F.Consolidate();
    //cout<<"Extracting: "<<F.Extract_Min()->vertex<<endl;
    
    F.Display_Heap();
	return 0;
}



