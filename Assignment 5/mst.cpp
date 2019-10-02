/**
 * @file mst.cpp
 * @author Hemil Panchiwala
 * @brief This program creates minimum spanning tree using Kruskal's algorithm using UNION FIND data structure
 * @date 2019-09-23
 * 
 * 
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <time.h>
using namespace std;

/**
 * @brief This is class for Graph
 * 
 */
class Graph {
private:
    vector<pair<int, pair<int,int>>> G; 
    vector<pair<int, pair<int,int>>> T; 
    int *parent;
    int V; 
public:
    Graph(int V);
    void AddWeightedEdge(int u, int v, int w);
    int find_set(int i);
    void union_set(int u, int v);
    void kruskal();
    void print();
};

/**
 * @brief Construct a new Graph object
 * 
 * @param V 
 */
Graph::Graph(int V) {
    parent = new int[V];
 
    for (int i = 0; i < V; i++)
        parent[i] = i;
        
}

/**
 * @brief This function adds an edge to the graph
 * 
 * @param u 
 * @param v 
 * @param w 
 */
void Graph::AddWeightedEdge(int u, int v, int w) {
    G.push_back(make_pair(w, pair<int,int>(u, v)));
}

/**
 * @brief This function finds a set in graph
 * 
 * @param i 
 * @return int 
 */
int Graph::find_set(int i) {
    if (i == parent[i]){
        return i;
    }else{
        return find_set(parent[i]);
    }
}
 
/**
 * @brief This function creates an union set 
 * 
 * @param u 
 * @param v 
 */
void Graph::union_set(int u, int v) {
    parent[u] = parent[v];
}

/**
 * @brief This function applies kruskal's algorithm to the graph to find MST tree 
 * 
 */
void Graph::kruskal() {
    int i, repeatedU, repeatedV;
    sort(G.begin(), G.end());
    for (i = 0; i < G.size(); i++) {
        repeatedU = find_set(G[i].second.first);
        repeatedV = find_set(G[i].second.second);
        if (repeatedU != repeatedV) {
            T.push_back(G[i]);
            union_set(repeatedU, repeatedV);
        }
    }
}

/**
 * @brief This function prints the minimum spanning tree
 * 
 */
void Graph::print() {
    cout << "Node1 Node2 Weight"<< endl;

    FILE *fp;

    if((fp = fopen("graph1.dot", "w")) != NULL){
        fprintf(fp, "graph G {\n");

        int sum = 0;

    for (int i = 0; i < T.size(); i++) {

        char start = (char) (T[i].second.first+65);
        char end = (char) (T[i].second.second+65);

        fprintf(fp, "\t%c -- %c [label=\"%d\"]\n", start, end, T[i].first);

        cout <<start<<" "<<end<<" "<< T[i].first;
        sum = sum + T[i].first;
        cout << endl;
    }

    cout<<"The total weight of minimum spanning tree is "<<sum<<endl;

    fprintf(fp, "}\n");
    fclose(fp);

    }else{
        printf("\nfopen() failed\n");
    }
}

/**
 * @brief This function takes input from the file and executes different functions to find the MST Tree using Kruskal's algorithm
 * 
 * @return int 
 */
int main() {

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    Graph g(6);
    ifstream fin; 
	fin.open("2019_CSN_261_L5_P2.csv"); 
	string line,s;
	vector<string> words;
    getline(fin, line);
	string max="";

    FILE *fp1;

    if((fp1 = fopen("graph2.dot", "w")) != NULL){
        fprintf(fp1, "graph G {\n");

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

        fprintf(fp1, "\t%c -- %c [label=\"%d\"]\n", words[0][0], words[1][0], stoi(words[2]));

        int start = (int) words[0][0] - 65;
        int end = (int) words[1][0] - 65;
        int weight = stoi(words[2]);

        g.AddWeightedEdge(start, end, weight);

		getline(fin, line);
    } 

    fprintf(fp1, "}\n");
    fclose(fp1);

    g.kruskal();
    g.print();
    }else{
        printf("\nfopen() failed\n");
    }

    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f\n", cpu_time_used);

    return 0;
}