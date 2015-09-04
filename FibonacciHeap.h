//Dongyu Li
//study by myself in Data Structure and Algorithm Analysis 
#include <string>   
#include <vector>   
#include <algorithm>   
#include <iostream> 
using namespace std;
#include<algorithm>

template<class T>
class FibonacciHeap
{
public:
    struct node
	{
        T value;
        node* parent;
        node* child;
        node* left;
        node* right;
		//whether the node lost a child
        bool mark;
        int  degree;
        node(T val=T()):value(val),parent(NULL),child(NULL),
			mark(false),degree(0)
        {
			left=this;
			right=this;
		}
    };
public:
	node* currentnode;
    FibonacciHeap():min(NULL),size(0){ }
	void insert(T);
	inline int getsize()
	{
		return size;
	}
    node* extractMin();
	~FibonacciHeap();
   
private:
	node* min;
    int size;
	void deleteNode(node*);  
	void addRoots(node*,node*);
	node* extractNode(node*); 
	void consolidate();  
};
template<class T>
//insert the new node to circular doubly list;
void FibonacciHeap<T>::insert(T value)
{
        node* n= new node(value);
        if(min==NULL)
            min=n;
        else
		{ 
            addRoots(min,n);
            if(n->value < min->value)
                min=n;
        }
        size+=1;
        currentnode=min;
}
template<class T>
//delete all the nodes from the heap
FibonacciHeap<T>::~FibonacciHeap()
{
    while (min != NULL && min != min->right)
        {
            node* temp=min;
            min=min->right;
            extractNode(temp);
            deleteNode(temp);
        }
        deleteNode(min);
        min = NULL;
}
//delete nodes from the heap
template<class T>
void  FibonacciHeap<T>::deleteNode(node * n)
{
        if(n != NULL)
        {
            while (n->child != NULL)
            {
                node* tmp=extractNode(n->child);
                deleteNode(tmp);
            }
            delete n;
            n= NULL;
        }
}
//add nodes to the root list
template<class T>
void  FibonacciHeap<T>::addRoots(node* curnode, node* n )
{
        if(curnode!=NULL)
		{
            curnode->right->left=n;
            n->right=curnode->right;
            curnode->right=n;
            n->left=curnode;
            n->parent=curnode->parent;
            if (curnode->parent != NULL)
                curnode->parent->degree += 1;
        }
}
//find the min node and release it from the heap;
template<class T>
typename FibonacciHeap<T>::node* FibonacciHeap<T>::extractMin()
{ 
        node* temp=min;
        if(temp!= NULL)
		{
            while( temp -> child != NULL)
			{
				
                node* n = extractNode(temp->child);
                addRoots(min,n);
            }
            if (temp == temp->right)
			{
                min=NULL;
            }
            else{
                min = temp->right;
                temp = extractNode(temp); 
                consolidate();
            }
            size -= 1;
        }
        return temp;
}

template<class T>
//combine two nodes that have the same degrees
void  FibonacciHeap<T>::consolidate()
{
		if(min == NULL)
            return; 
		//compute the theoretical biggest degree in the heap
		const float base = 2;
		const float arg = static_cast<float>(size);
        const int max=int(log(arg)/log(base)) + 1;
        node **A=new node*[max];
		//create the temporary array to store the node
        for(int i=0; i!=max; ++i)
		 A[i]=NULL;
        node *n=min;
        int degree= n->degree;
        while (n != A[degree])
		{
            if(A[degree] != NULL)
			{
                if (A[degree]->value < n->value)
                    swap(A[degree],n);
                if (n->child == NULL)
				{
                    A[degree]=extractNode(A[degree]);
                    n->child = A[degree];
                    A[degree]->parent = n;
                    n->degree +=1;
                }   
                else
				{
                    A[degree] = extractNode(A[degree]);
                    addRoots(n->child, A[degree]);
                }
                A[degree]=NULL;
            }
            else
			{
                A[degree]=n;
                n=n->right;
            }
            degree= n->degree;
        };
        min=NULL;
        for (int i= 0; i!= max; ++i)
		{
            if (A[i] != NULL)
                if (min==NULL)
                    min=A[i];
                else
                    if (A[i]->value < min-> value)
                        min=A[i];
        }
        delete A;
}
//extract node from the heap
template<class T>
typename FibonacciHeap<T>::	node*  FibonacciHeap<T>::extractNode(node* n)
{
        if (n == NULL)
            return NULL;
        if(n->parent != NULL)
		{
            n->mark=false;
            if (n->right != n)
                n->parent->child = n->right;
            else
                n->parent->child = NULL;
            if (n->parent->parent != NULL)
                n->parent->mark=true;
            n->parent->degree -=1;
            n->parent=NULL;
        }
        if (n->left != n)
		{
            n->left->right = n->right;
            n->right->left = n->left;
            n->left=n;
            n->right=n;
        }
        n->mark=false;
        return n;
}