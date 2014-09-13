fib_heap
========

Fibonacci Heap Implementation for C++

Primarily References [￼Fibonacci Heaps and Their Uses in Improved Network Optimization Algorithms](http://www.cl.cam.ac.uk/~sos22/supervise/dsaa/fib_heaps.pdf)

#Notes
This was primarily implemented for use in [Prim's Algorithm](http://en.wikipedia.org/wiki/Prim's_algorithm). Graph vertecies are stored in the heap, and ordered by an edge weight associated with each vertex. As such, each node in this implementation takes a vertex integer and weight integer and the heap uses the weight property for organization. 

```c++
struct node
{
    int rank;
    char mark;
    
    int vertex;
    int weight;
    
    node* parent;
    node* child;
    node* left;
    node* right;
};
```

#Heap Operations
####Creating a Heap

```c++
FibonacciHeap F;
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
####Display Heap (Only use on small heaps)
```c++
F.Display_Heap();
```
