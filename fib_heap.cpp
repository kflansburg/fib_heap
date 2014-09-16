#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>


#define filename "fib.json"
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
    int roots; //Keep track of number of roots
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
    void Decrease_Key(node*,int);
    void EnumerateChildren(std::ofstream&,node*);
    void Display_Root(void);
    FibonacciHeap()
    {
        H = Make_Heap();
        size = 0;
        roots=0;
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

void FibonacciHeap::Display_Root(){
    node*p=H;
    do{
        Display_Node(p);
        p=p->left;
    }
    while(p!=H);
}

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
    roots++;
}//Merge root nodes, return lowest weight node

void FibonacciHeap::Display_Heap()
{
    if(H==NULL){
        cout<<"No nodes in heap!"<<endl;
    }
    else{
        ofstream jsonfile;
        jsonfile.open(filename);
        node*p=H;
        jsonfile<<"{\"name\":\"min="<<H->vertex<<"\",\"children\":[";
        do{
            jsonfile<<"\n{\"name\":\""<<p->vertex<<"("<<p->weight<<")\",\"weight\":\""<<p->weight<<"\",\"children\":[";
            
            Display_Node(p);
            EnumerateChildren(jsonfile,p);
            
            jsonfile<<"]}";

            if(p->left!=H){
                jsonfile<<",";
            }
            p=p->left;
        }
        while(p!=H);

        jsonfile<<"]}";
        jsonfile.close();


        
    }  
}

void FibonacciHeap::EnumerateChildren(std::ofstream& file,node*h){

    if(h->child){
        node*p=h->child;

        do{
            file<<"\n{\"name\":\""<<p->vertex<<"("<<p->weight<<")\",\"weight\":\""<<p->weight<<"\",\"children\":[";
                Display_Node(p);
                EnumerateChildren(file,p);
            file<<"]}";
            if(p->left!=h->child){
                file<<",";
            }

            p=p->left;
        }
        while(p!=h->child);

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
            (H->rank)--;
            roots++;

        }
        


        //Check that there are other root nodes
        if(H->left==H){
            //There where no other root nodes, and no children to add to the root
            H = NULL;
            size--;
            roots--;
        }
        else{
            if(DEBUG){cout<<"Consolidating"<<endl;}
            
            //There are roots to consolidate
            (H->right)->left=H->left;
            (H->left)->right=H->right;

            //No longer need H, pass another root to consolidate, which will return new root
            H=(H->left);
            size--;
            roots--;
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
    roots--;
    return root;
}

void FibonacciHeap::Consolidate()
{
    int max_depth = ceil(log2(size)/log2(1.618)); //Figure out the maximum depth possible
    if(DEBUG){cout<<"Max Depth: "<<max_depth<<endl;}
    if(DEBUG){cout<<"Roots: "<<roots<<endl;}
    node *ranks[max_depth]; //Use array to keep track of conflicting degrees

    //Array for checking depth
    for(int i=0;i<max_depth;i++){
        ranks[i]=NULL;
    }

    //Build list of roots to check
    node*p = H;
    node* rootlist[roots];
    for(int i = 0;i<roots;i++){
        rootlist[i]=p;
        p=p->left;
    }



    int old_roots = roots; //Roots is gonna change in the loop
    //For each root node, check if conflicting degree
    for(int i = 0;i<old_roots;i++)
    {   
        p=rootlist[i];
        int r = p->rank;
        if(DEBUG){cout<<"Vertex: "<<p->vertex<<" Rank: "<<p->rank<<endl;}
        while(ranks[r]!=NULL)
        {
            //If conflict, link conflicting trees, and try to store new tree.
            if(DEBUG){cout<<"    Conflict: "<<ranks[r]->vertex<<","<<p->vertex<<endl;}
            p=Link(p,ranks[r]);
            ranks[r]=NULL;
            r=p->rank;
        }
        
        ranks[r]=p;
    }
    

    //Search for new minimum root
    
    node* root=p; //Some root node
    do{
        if(p->weight<root->weight){
            root=p;
        }
        p=p->left;
    }
    while(p!=root);

    H=root;
}

void FibonacciHeap::Decrease_Key(node *h,int del_){
    //Decrease Key
    h->weight-=del_;

    //Check if new key violates heap
    if(h->weight<(h->parent)->weight){
        

        //Cut and place in root

        //Check parent for marked (recursive)
            //YES
                //Cut and place in root, unmark
                //Check Parent
            //NO
                //Mark
    }
}//Decreases the node associated with vertex_'s key by del_, and places node as root node

//Cut Function

//Check Parent Function




int main(){
	FibonacciHeap F; //Create new Heap

    while(true){
        cout<<"1. Generate Random Heap [size]."<<endl;
        cout<<"2. Display Heap."<<endl;
        cout<<"3. Extract Minimum."<<endl;
        cout<<"4. Generate Random List and Sort [length]."<<endl;
        int command;
        int max;
        cin>>command;
        switch(command){
            case 1:
                cin>>max;
                srand (time(NULL));
                for(int i = 1;i<=max;i++){
                    int weight = rand()%max;
                    F.Insert(weight,i);
                }
                break;
            case 2:
                F.Display_Heap();
                break;
            case 3:
                node* min;
                min=F.Extract_Min();
                if(min==NULL){
                    cout<<"Empty Tree!"<<endl;
                }
                else{
                    cout<<min->vertex<<"("<<min->weight<<")"<<endl;
                }
                break;
            case 4:
                cin>>max;
                srand (time(NULL));
                cout<<"LIST: "<<endl;
                for(int i = 1;i<=max;i++){
                    int weight = rand()%max;
                    F.Insert(weight,i);
                    cout<<weight<<endl;
                }
                cout<<"SORTED LIST: "<<endl;
                for(int i = 1;i<=max;i++){
                    cout<<F.Extract_Min()->weight<<endl;
                }
                break;
            default:
                break;
        }
    }
	return 0;
}



