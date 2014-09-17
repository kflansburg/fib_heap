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


class FibonacciHeap
{
private:
    int size; //Total size of heap
    node* H; //root node
    int roots; //Keep track of number of roots
public:
    node* Make_Heap();
    node* Insert(int, int);
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
    void Cut(node*);
    FibonacciHeap()
    {
        H = Make_Heap();
        size = 0;
        roots=0;
    }
};