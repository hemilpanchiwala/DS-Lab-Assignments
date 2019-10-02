/**
 * @file prims.cpp
 * @author Hemil Panchiwala
 * @brief This program creates minimum spanning tree using Prim's algorithm using Fibonacci heap data structure
 * @date 2019-09-23
 * 
 * 
 */
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <time.h>

using namespace std;

/**
 * @brief This keeps the note of destination and weight of particular node
 * 
 */
struct Adjacency_List_Node
{
	int destination;
	float weight;
	struct Adjacency_List_Node *next;
};

struct Adjacency_List
{
	struct Adjacency_List_Node *head;
};

/**
 * @brief This is single Graph node
 * 
 */
struct Graph
{
	int number_of_vertices;
	struct Adjacency_List* array;
};

/**
 * @brief This function creates the edge between two nodes with its weight
 * 
 * @param dest 
 * @param weight 
 * @return struct AdjListNode* 
 */
struct Adjacency_List_Node* New_Adjacency_List_Node(int destination,float weight)
{
	struct Adjacency_List_Node* new_node = (struct Adjacency_List_Node*)malloc(sizeof(Adjacency_List_Node));
	new_node->destination=destination;
	new_node->weight=weight;
	new_node->next=NULL;
	return new_node;
}

/**
 * @brief Create a Graph object
 * 
 * @param V 
 * @return struct Graph* 
 */
struct Graph* Create_New_Graph(int number_of_vertices)
{
	struct Graph* new_graph=(struct Graph*)malloc(sizeof(struct Graph));
	new_graph->number_of_vertices=number_of_vertices;
	new_graph->array=(struct Adjacency_List*)malloc(number_of_vertices*sizeof(struct Adjacency_List));
	for (int k = 0; k < number_of_vertices; ++k)
	{
		new_graph->array[k].head=NULL;
	}
	return new_graph;
}

/**
 * @brief This function adds an edge to the graph
 * 
 * @param graph 
 * @param src 
 * @param dest 
 * @param weight 
 */
void Add_New_Edge(struct Graph* graph,int source,int destination,float weight)
{
	struct Adjacency_List_Node* new_node;
	new_node=New_Adjacency_List_Node(destination, weight);
	new_node->next=graph->array[source].head;
	graph->array[source].head=new_node;
	new_node=New_Adjacency_List_Node(source, weight);
	new_node->next=graph->array[destination].head;
	graph->array[destination].head=new_node;
}

/**
 * @brief This is node for fibonacci heap
 * 
 */
struct Fib_Heap_Node
{
	int v;
	float key;
};

/**
 * @brief This nodes keeps the parameters for the fibonacci heap
 * 
 */
struct Fib_Heap
{
	int number_of_heap_nodes;
	int capacity;
	int *pos;
	struct Fib_Heap_Node **array;	
};

/**
 * @brief This node creates the new fibonacci heap node
 * 
 * @param v 
 * @param key 
 * @return struct fibheapNode* 
 */
struct Fib_Heap_Node* New_Fib_Heap_Node(int v,int key)
{
	struct Fib_Heap_Node* Fib_Heap_node=(struct Fib_Heap_Node*)malloc(sizeof(struct Fib_Heap_Node));
	Fib_Heap_node->v=v;
	Fib_Heap_node->key=key;
	return Fib_Heap_node;
}

struct Fib_Heap* Create_Fib_Heap(int capacity)
{
	struct Fib_Heap* Fib_Heap=(struct Fib_Heap*)malloc(sizeof(struct Fib_Heap));
	Fib_Heap->pos=(int *)malloc(capacity*sizeof(int));
	Fib_Heap->number_of_heap_nodes=0;
	Fib_Heap->capacity=capacity;
	Fib_Heap->array=(struct Fib_Heap_Node**)malloc(capacity*sizeof(struct Fib_Heap_Node*));
	return Fib_Heap;
}

/**
 * @brief This function swaps the nodes of fibonacci heap
 * 
 * @param a 
 * @param b 
 */
void Swap_Fib_Heap_Nodes(struct Fib_Heap_Node** a,struct Fib_Heap_Node** b)
{
	struct Fib_Heap_Node* temp=*a;
	*a=*b;
	*b=temp;
}

/**
 * @brief This functions performs the heapify method
 * 
 * @param fibheap 
 * @param idx 
 */
void Fib_Heapify(struct Fib_Heap* Fib_Heap,int index)
{
	int smallest,left,right;
	smallest=index;
	left=2*index+1;
	right=2*index+2;
	if(left<Fib_Heap->number_of_heap_nodes && Fib_Heap->array[left]->key<Fib_Heap->array[smallest]->key)
	{
		smallest=left;
	}
	if(right<Fib_Heap->number_of_heap_nodes && Fib_Heap->array[right]->key<Fib_Heap->array[smallest]->key)
	{
		smallest=right;
	}
	if(smallest != index)
	{
		Fib_Heap_Node *smallest_node=Fib_Heap->array[smallest];
		Fib_Heap_Node *index_node=Fib_Heap->array[index];
		Fib_Heap->pos[smallest_node->v]=index;
		Fib_Heap->pos[index_node->v]=smallest;
		Swap_Fib_Heap_Nodes(&Fib_Heap->array[smallest],&Fib_Heap->array[index]);
		Fib_Heapify(Fib_Heap,smallest);
	}
}

/**
 * @brief This function checks whether min heap is empty or not
 * 
 * @param fibheap 
 * @return int 
 */
int Is_Empty(struct Fib_Heap* Fib_Heap)
{
    return Fib_Heap->number_of_heap_nodes == 0;
}

/**
 * @brief Get the Fibonacci object
 * 
 * @param getFib 
 * @return int 
 */
int getFibonacci(int getFib) {
	int a1 = 1;
	int a2 = 1;
	int fibNum = 0;
	for(int i=2;i<getFib;i++){
		a2 = a1 + a2;
		a1 = a2;
	}
	return a2;
}

/**
 * @brief This function extracts the minimum from the min heap
 * 
 * @param fibheap 
 * @return struct fibheapNode* 
 */
struct Fib_Heap_Node* Extract_Minimum(struct Fib_Heap* Fib_Heap)
{
	if(Is_Empty(Fib_Heap))
	{
		return NULL;
	}
	struct Fib_Heap_Node* root_of_heap=Fib_Heap->array[0];
	struct Fib_Heap_Node* last_node_of_heap=Fib_Heap->array[Fib_Heap->number_of_heap_nodes-1];
	Fib_Heap->array[0]=last_node_of_heap;
	Fib_Heap->pos[root_of_heap->v]=Fib_Heap->number_of_heap_nodes-1;
	Fib_Heap->pos[last_node_of_heap->v]=0;
	Fib_Heap->number_of_heap_nodes = Fib_Heap->number_of_heap_nodes - 1;

	int getFib = 5;
	getFibonacci(getFib);

	Fib_Heapify(Fib_Heap,0);
	return root_of_heap;
}

void Decrease_Key(struct Fib_Heap* Fib_Heap,int v,float key)
{
	int i=Fib_Heap->pos[v];
	Fib_Heap->array[i]->key=key;
	
	while(i && ((Fib_Heap->array[i]->key) < (Fib_Heap->array[(i-1)/2]->key)))
	{
        int p = (i-1)/2;
		Fib_Heap->pos[Fib_Heap->array[i]->v]=p;
		Fib_Heap->pos[Fib_Heap->array[p]->v]=i;
		Swap_Fib_Heap_Nodes(&Fib_Heap->array[i], &Fib_Heap->array[p]);
		i=p;	
	}
	
}

/**
 * @brief This function checks whether the node is in min heap or not
 * 
 * @param fibheap 
 * @param v 
 * @return true 
 * @return false 
 */
bool Is_In_Fib_Heap(struct Fib_Heap* Fib_Heap,int v)
{
	if(Fib_Heap->pos[v] < Fib_Heap->number_of_heap_nodes)
	{
		return true;
	}
	return false;
}

int minimum(int a , int b)
{
	if(a<b)return a;
	return b;
}

int maximum(int a , int b)
{
	if(a>b)return a;
	return b;
}

vector<pair<float,pair<int, int>>> arr1;

/**
 * @brief This function prints the minimum spanning tree using Prim's algorithm
 * 
 * @param node 
 * @param weight 
 * @param n 
 */
void Print_An_Array(int array[],float weight[],int size,float sum)
{
	arr1.resize(size);
	for (int l = 1; l < size; ++l)
	{
		arr1[l].first=weight[l];
		arr1[l].second.first=minimum(array[l],l);
		arr1[l].second.second=maximum(array[l],l);
	}
	sort(arr1.begin(), arr1.end());
    cout << "Node1 Node2 Weight"<< endl;
	for (int i = 1; i < size; ++i)
	{
		if(arr1[i].first>-1000000 && arr1[i].first<1000000)
		{
            char start = (char) (arr1[i].second.first+65);
			char end = (char) (arr1[i].second.second+65);
            cout<<start<<" "<<end<<" ";
			cout<<arr1[i].first<<endl;
		}
	}
}

/**
 * @brief This function performs the prim's algorithm
 * 
 * @param graph 
 */
void Prim_Minimum_Spanning_Tree(struct Graph* graph)
{
	int number_of_vertices=graph->number_of_vertices;
	int parent[number_of_vertices];
	float key[number_of_vertices];
	float sum=0;
	struct Fib_Heap* Fib_Heap= Create_Fib_Heap(number_of_vertices);
	for (int v = 1; v < number_of_vertices; ++v)
	{
		parent[v]=-1;
		key[v]=2000000000;
		Fib_Heap->array[v]=New_Fib_Heap_Node(v,key[v]);
		Fib_Heap->pos[v]=v;
	}
	
	key[0]=0;
	Fib_Heap->array[0]=New_Fib_Heap_Node(0,key[0]);
	Fib_Heap->pos[0]=0;
	
	Fib_Heap->number_of_heap_nodes=number_of_vertices;
	
	while(!Is_Empty(Fib_Heap))
	{
		struct Fib_Heap_Node* Fib_Heap_node=Extract_Minimum(Fib_Heap);
		int minimum_vertex=Fib_Heap_node->v;
		struct Adjacency_List_Node* traversal_node=graph->array[minimum_vertex].head;
		
		while(traversal_node!=NULL)
		{
			int v=traversal_node->destination;
			
			if(Is_In_Fib_Heap(Fib_Heap,v) && traversal_node->weight < key[v])
			{
				
				key[v]=traversal_node->weight;
				
				parent[v]=minimum_vertex;
				Decrease_Key(Fib_Heap,v,key[v]);
			}
			
			traversal_node=traversal_node->next;
		}
		
	}
	
	for (int j = 1; j < number_of_vertices; ++j)
	{

		if(key[j]>-1000000 && key[j]<1000000)
		{
			sum=sum+key[j];
		}
	}
	cout<<"The total weight of minimum spanning tree is "<<sum<<endl;
	Print_An_Array(parent,key,number_of_vertices,sum);
}

/**
 * @brief This function takes input from the file and executes different functions to find the MST Tree using Prim's algorithm
 * 
 * @return int 
 */
int main()
{
    
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    int u,v,nodes;
	nodes = 6;
	float w;
	struct Graph* graph = Create_New_Graph(nodes);
	ifstream fin; 
	fin.open("2019_CSN_261_L5_P2.csv"); 
	string line,s;
	vector<string> words;
    getline(fin, line);
	string max="";

	cout<<"Node1 Node2 Weight"<<endl;
    while (fin) {
        vector<string> words;
        stringstream ss(line); 
        string tok;
        while(getline(ss, tok, ',')) {
            words.push_back(tok);
        }
  		s = words[0]+words[1];
  		max = (max>s)?max:(words[0]>words[1]?words[0]:words[1]);
  		
		cout<<words[0]<<" "<<words[1]<<" "<<stoi(words[2])<<endl;

        int start = (int) words[0][0] - 65;
        int end = (int) words[1][0] - 65;
        int weight = stoi(words[2]);

        Add_New_Edge(graph, start, end, weight);

		getline(fin, line);
    } 
    Prim_Minimum_Spanning_Tree(graph);

    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f\n", cpu_time_used);
	return 0;
}