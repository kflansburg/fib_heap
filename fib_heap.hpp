#pragma once

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
    node* Meld(node*,node*);
    node* Extract_Min();
    void Delete_Min();
    node* Link(node*, node*);
    void Consolidate(void);
    void Decrease_Key(int,int);
    
    FibonacciHeap()
    {
        H = Make_Heap();
        size = 0;
    }
};
