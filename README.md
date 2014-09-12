fib_heap
========

Fibonacci Heap Implementation for C++

Primarily References [￼Fibonacci Heaps and Their Uses in Improved Network Optimization Algorithms](http://www.cl.cam.ac.uk/~sos22/supervise/dsaa/fib_heaps.pdf)

#Notes
This was primarily implemented for use in [Prim's Algorithm](http://en.wikipedia.org/wiki/Prim's_algorithm). Graph vertecies are stored in the heap, and ordered by an edge weight associated with each vertex. As such, each node in this implementation takes a vertex integer and weight integer and the heap uses the weight property for organization. 

```c++
struct node
{
    int rank; //Rank of Node
    char mark; //Is node Marked? "0"==No, "1"==Yes
    
    int vertex; //Vertex that node represents
    int weight; //Weight of edge attatched to node
    
    node* parent; //Pointers relative to node
    node* child;
    node* left;
    node* right;
};
```

#Heap Operations
####Creating a Heap

```c++
FibonacciHeap F;
F.Make_Heap();
```
####Extract Min O(log(n))
```c++
node* h = F.Extract_Min();
```
####Insert O(1)
```c++
F.Insert(int weight,int vertex);
```
####Decrease Key O(1)
Weight is decreased by change. 
```c++
F.Decrease_Key(int vertex, int change); 
```
####Merge O(1)
Merges heap in argument into main heap. 
```c++
F.Union(node* h);
```
