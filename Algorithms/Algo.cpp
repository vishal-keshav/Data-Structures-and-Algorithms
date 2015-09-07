/*The motivation of creating this file is to touch every possible algorithm used in solving
    problems that appear frequently in coding challanges and algorithm includes are not allowed.
    The main aim is to prepare a exhaustive yet important implementation of algorithm in short way
    such that re implementing such algorithm during challege environment dont take too much time.*/

/*Author-Vishal Keshav
    email-bulletcross@gmail.com
    www.github.com
*/

/*Algorithms implemented
    1. Binary search
    2. n log(n) sort
    3. n sort
    4. Pattern matching
    5. Backtracking
    6. some Graph algorithm
    7. some String algorithm
    8. some Geometric algorithm
    9. some bit algorithm
*/

#include <stdlib.h>
#include <iostream>
#include <cstdio>

using namespace std;

//A generic data structure
struct data{
    int data1;
    int data2;
    int data3;
};

struct heap_data{
    int key;
    int value;
};

//Singly Linked List start************************************************************
struct sll_node{
    int node;
    int weight;
    sll_node * next;
};
//Queue start**************************************************************************
//Uses already created singly linked list structure
void enq(sll_node **head,sll_node **tail,int node){
    sll_node * newnode = (sll_node *)malloc(sizeof(sll_node));
    newnode->node = node;
    newnode->next=NULL;
    if((*tail)==NULL){
        (*head)=newnode;
        (*tail)=newnode;
    }
    else{
        (*head)->next = newnode;
        (*head)=newnode;
    }
}
int deq(sll_node **tail){
    sll_node *newnode = (*tail);
    int node = newnode->node;
    (*tail)=newnode->next;
    free(newnode);
    return node;
}
//Queue end~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Stack start*************************************************************************
//Uses already created singly linked list structure
void push(sll_node **head,int node){
    sll_node *newnode = (sll_node *)malloc(sizeof(sll_node));
    newnode->node=node;
    newnode->next=(*head);
    (*head)=newnode;
}
int pop(sll_node **head){
    sll_node * newnode=(*head);
    (*head)=newnode->next;
    int node=newnode->node;
    free(newnode);
    return node;
}
//Stack end~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Heap Start*****************************************************************************
    //Fixed size heap should be declared
    //Defining functions for min heap
    //This heapify is a non recursive efficient version and does not use unnecessary swap and child functions
    void heapify(heap_data *heap,int index,int current_size){
        int left;
        int right;
        int min_index=index;
        heap_data temp;
        do{
            index=min_index;
            left = 2*index +1;
            right=2*index+2;
            if(left<current_size && heap[min_index].key>heap[left].key){
                min_index = left;
            }
            if(right<current_size && heap[min_index].key>heap[right].key){
                min_index = right;
            }
            temp=heap[min_index];
            heap[min_index]=heap[index];
            heap[index]=temp;
        }while(min_index!=index && min_index<current_size);
    }
    //current size will increase by one assuming all the checks have been done in main code
    void heap_insert(heap_data *heap,int key,int data,int *current_size){
        int index=(*current_size);
        int parent=(index-1)/2;
        heap_data temp;
        heap[index].key=key;
        heap[index].value = data;
        (*current_size)=(*current_size)+1;
        while(index>0 && heap[parent].key>heap[index].key){
            temp=heap[parent];
            heap[parent]=heap[index];
            heap[index]=temp;
            index=parent;
            parent=(index-1)/2;
        }
    }
    //Extracting minimum is based on assumptions that proper checks have been made for empty heap
    heap_data extract_min(heap_data *heap,int *current_size){
        heap_data minimum=heap[0];
        int index = (*current_size)-1;
        (*current_size)=(*current_size)-1;
        heap[0]=heap[index];
        heapify(heap,0,index);
        return minimum;
    }
//Heap end~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Union-find******************************************************************************
//Uses array data structure declared in main(depending on the max size of set)
//Implementing Union-find by rank combined with path compression for constant amortized complexity
int uf_find(int *set_array,int node){
    if(set_array[node]!=set_array[set_array[node]]){
        set_array[node] = uf_find(set_array,set_array[node]);
    }
    return set_array[node];
}

bool uf_union(int *set_array,int *rank_array,int node1,int node2){
    int parent1 = uf_find(set_array,node1);
    int parent2 = uf_find(set_array,node2);
    int temp;
    if(parent1==parent2){
        return false;
    }
    if(rank_array[parent1]>rank_array[parent2]){
        temp = parent1;
        parent1 = parent2;
        parent2 = temp;
    }
    if(rank_array[parent1]==rank_array[parent2]){
        rank_array[parent2]++;
    }
    set_array[parent1]=parent2;
    return true;
}
//Union-find end~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//Binary search is implemented in Data-struct.cpp file*****************************************

//Binary search ends~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Merge sort*************************************************************************************

void merge_data(data *mydata,int start_index,int middle_index,int end_index){
    data *temp = new data[(end_index-start_index) + 1];
    int left_index=start_index;
    int right_index = middle_index+1;
    int running_index = 0;
    while(left_index<=middle_index && right_index<=end_index){
        if(mydata[left_index].data1<=mydata[right_index].data1){
            temp[running_index] = mydata[left_index];
            left_index++;
        }
        else{
            temp[running_index] = mydata[right_index];
            right_index++;
        }
        running_index++;
    }
        while(left_index<=middle_index){
            temp[running_index] = mydata[left_index];
            running_index++;
            left_index++;
        }
        while(right_index<=end_index){
            temp[running_index]= mydata[right_index];
            running_index++;
            right_index++;
        }
    running_index=0;
    left_index = start_index;
    while(left_index<=end_index){
        mydata[left_index] = temp[running_index];
        left_index++;
        running_index++;
    }
}

void merge_sort(data *mydata,int start_index,int end_index){
    if(start_index!=end_index){
        int middle_index = start_index + (end_index-start_index)/2 ;
        merge_sort(mydata,start_index,middle_index);
        merge_sort(mydata,middle_index+1,end_index);
        merge_data(mydata,start_index,middle_index,end_index);
    }
}
//Merge sort end~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//counting sort*****************************************************************************************
void count_sort(data *mydata,int start_index,int end_index){
    int maximum = mydata[start_index].data1;
    int running_index = start_index+1;
    while(running_index<=end_index){
        maximum = mydata[running_index].data1>maximum?mydata[running_index].data1:maximum;
        running_index++;
    }
    int *counter = new int[maximum+1];
    for(int i=0;i<=maximum;i++){
        counter[i] = 0;
    }
    int *temp = new int[(end_index-start_index) + 1];
    for(int i=start_index;i<=end_index;i++){
        counter[mydata[i].data1]++;
    }
    for(int i=1;i<=maximum;i++){
        counter[i] = counter[i]+counter[i-1];
    }
    for(int i=start_index;i<=end_index;i++){
        temp[counter[mydata[i].data1]-1] = mydata[i].data1;
        counter[mydata[i].data1]--;
    }
    for(int i=start_index,j=0;i<=end_index;i++,j++){
        mydata[i].data1 = temp[j];
    }
}
//counting sort end~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//Bonus pseudo code for permutaion generation
    //Obtain next permutaon by
    //Find largest index i such that array[i − 1] < array[i]
    //Find largest index j such that j ≥ i and array[j] > array[i − 1]
    //Swap array[j] and array[i − 1]
    //Reverse the suffix starting at array[i]
//Permutaion generation ends

//Bonus pseudo code for subset generation
/*
    //Obtain number 0 to pow(2,N)
    //Convert each number to bits
    //print the value corresponding to active bits
for(int i=0;i<power(2,N);i++){
    for(int j=0;j<N;j++){
        if(i & 1<<j){
            print arr[j];
        }
    }
    cout << endl;
}
*/
//Subset generation ends

//String matching============================================
    int string_length(char *input){
        int len=0;
        while(*input!='\0'){
            len++;
            input++;
        }
        return len;
    }
    int pattern_match(char *str_main,char *str){
        int ret = -1;
        int n = string_length(str_main);
        int m= string_length(str);
        //Checking corner cases
        if(n<m || n==0){
            return -1;
        }
        //Main case
        int prime = 1000000000+7;
        int hash_str = 0;
        int hash_main=0;
        int base=256;
        int power = 1;
        for(int i=0;i<m;i++){
            hash_str = (hash_str*base + (int)str[i])%prime;
            hash_main = (hash_main*base + (int)str_main[i])%prime;
            if(i<m-1){
                power = (power*base)%prime;
            }
        }
        for(int i=0;i<=n-m;i++){
            if(hash_str==hash_main){
                int j;
                for(j=0;j<m;j++){
                    if(str_main[i+j]!=str[j]){
                        break;
                    }
                }
                if(j==m){
                    ret = i;
                    break;
                }
            }
            if(i<n-m){
                hash_main = (base*(hash_main - power*str_main[i]) + str_main[i+m])%prime;
                if(hash_main<0){
                    hash_main = hash_main + prime;
                }
            }
        }
        return ret;
    }
//String matching ends++++++++++++++++++++++++++++++++++++++++++++

//Graph Algorithms===============================================
// 1. BFS
// 2. DFS
// 3. Single source shortest path (Digstras and Bellman fords)
// 4. Minimum Spanning tree (Kruskals and Prims)
// 5. All pair shortest path (Floyed Warshall)
// 6. Topological sorting (indegree, stack method)
// 7. Maximum Flow algorithm(Ford fulkersons algorithm)

//We will include both adjency matrix and adjency list implementation
//in all algorithms disabling one while checking
//Graph utilities of no use^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
sll_node **Graph_mat_to_list(int **Graph_mat,int V){
    sll_node **G = (sll_node **)malloc(sizeof(sll_node *)*V);
    for(int i=0;i<V;i++){
        G[i] = NULL;
    }
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(Graph_mat[i][j]>=1){
                sll_node *temp = (sll_node *)malloc(sizeof(sll_node));
                temp->node = j;
                temp->weight = Graph_mat[i][j];
                temp->next = G[i];
                G[i] = temp;
            }
        }
    }
    return G;
}
void Graph_directed_to_undirected(int **Graph_mat,int V){
    for(int i=0;i<V;i++){
        for(int j=i+1;j<V;j++){
            Graph_mat[j][i] = Graph_mat[i][j];
        }
    }
}
int dag(int **G,int V,int start_node,bool *visited){
    visited[start_node] = true;
    int ret = 0;
    for(int i=0;i<V;i++){
        if(G[start_node][i]==1){
            if(visited[i]){
                G[start_node][i] = 0;
            }
            else{
                ret = ret + dag(G,V,i,visited);
            }
        }
    }
    return ret+1;
}
bool Graph_directed_to_dag(int **Graph_mat,int V){
    bool *visited = (bool *)malloc(sizeof(bool)*V);
    for(int i=0;i<V;i++){
        visited[i] = false;
    }
    if(dag(Graph_mat,V,0,visited)==V){
        return true;
    }
    else{
        return false;
    }
}
//Graph utilities of no use ends^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//Traversal algorithm
void BFS(sll_node **Graph_list,int V,bool *visited,int start_node){
//void BFS(int **Graph_mat,int V,bool *visited,int start_node){
    sll_node *Q_head = NULL;
    sll_node *Q_tail = NULL;
    enq(&Q_head,&Q_tail,start_node);
    visited[start_node] = true;
    int temp_node;
    while(Q_tail!=NULL){
        temp_node = deq(&Q_tail);
        cout << temp_node << " ";
        //For Mat
        /*for(int i=0;i<V;i++){
            if(Graph_mat[temp_node][i]==1 && (!visited[i])){
                enq(&Q_head,&Q_tail,i);
                visited[i] = true;
            }
        }*/
        //For List
        sll_node *temp = Graph_list[temp_node];
        while(temp!=NULL){
            if(!visited[temp->node]){
                enq(&Q_head,&Q_tail,temp->node);
                visited[temp->node] = true;
            }
            temp = temp->next;
        }
    }
}
void Graph_BFS(sll_node **Graph,int V){
//void Graph_BFS(int **Graph,int V){
    bool *visited = (bool *)malloc(sizeof(bool)*V);
    for(int i=0;i<V;i++){
        visited[i] = false;
    }
   for(int i=0;i<V;i++){
        if(!visited[i]){
            BFS(Graph,V,visited,0);
        }
    }
}
void DFS(sll_node **Graph_list,int V,bool *visited,int start_node){
//void DFS(int **Graph_mat,int V,bool *visited,int start_node){
    sll_node *S_head=NULL;
    push(&S_head,start_node);
    //visited[start_node] = true;
    int temp_node;
    while(S_head!=NULL){
        temp_node = pop(&S_head);
        if(!visited[temp_node]){
            cout << temp_node << " ";
            visited[temp_node] = true;
        }
        //For mat
        /*for(int i=0;i<V;i++){
            if(Graph_mat[temp_node][i] && !visited[i]){
                push(&S_head,i);
            }
        }*/
        //For list
        sll_node *temp = Graph_list[temp_node];
        while(temp!=NULL){
            if(!visited[temp->node]){
                push(&S_head,temp->node);
                //cout << "pushed "<< temp->node << " ";
            }
            temp = temp->next;
        }

    }
}
void Graph_DFS(sll_node **Graph,int V){
//void Graph_DFS(int **Graph,int V){
    bool *visited = (bool *)malloc(sizeof(bool)*V);
    for(int i=0;i<V;i++){
        visited[i] = false;
    }
   for(int i=0;i<V;i++){
        if(!visited[i]){
            DFS(Graph,V,visited,0);
        }
    }
}
//Traversal algorithm ends
//Topological sorting
int *Graph_topological_sort(sll_node **G,int V){
    int *temp = (int *)malloc(sizeof(int)*V);
    int k=0;
    int *indegree = (int *)malloc(sizeof(int)*V);
    for(int i=0;i<V;i++){
        indegree[i]=0;
    }
    sll_node *temp_node;
    for(int i=0;i<V;i++){
        temp_node = G[i];
        while(temp_node!=NULL){
            indegree[temp_node->node]++;
            temp_node = temp_node->next;
        }
    }
    sll_node *S_head=NULL;
    for(int i=0;i<V;i++){
        if(indegree[i]==0){
            push(&S_head,i);
        }
    }
    int node_zero_degree;
    while(S_head!=NULL){
        node_zero_degree = pop(&S_head);
        temp[k] = node_zero_degree;
        k++;
        temp_node = G[node_zero_degree];
        while(temp_node!=NULL){
            indegree[temp_node->node]--;
            if(indegree[temp_node->node]==0){
                push(&S_head,temp_node->node);
            }
            temp_node = temp_node->next;
        }
    }
    return temp;
}
//Topological Sorting end++++++++++++++++++++++++++++++++++++++++++++++++
//Single source shortest path algorithms
void Shortest_path_dijktra(sll_node **Graph_list,int source,int *p,int *d,int V){
    //Initialization
    for(int i=0;i<V;i++){
        p[i] = i;
        d[i] = 1000000000+7;
    }
    d[source] = 0;
    heap_data *heap = (heap_data *)malloc(sizeof(heap_data)*V);
    heap_data mini;
    sll_node *temp;
    int current_size = 0;
    heap_insert(heap,0,source,&current_size);
    while(current_size>0){
        mini = extract_min(heap,&current_size);
        temp = Graph_list[mini.value];
        while(temp!=NULL){
            if(d[temp->node]>d[mini.value]+temp->weight){
                d[temp->node] = d[mini.value] + temp->weight;
                p[temp->node] = mini.value;
                heap_insert(heap,d[temp->node],temp->node,&current_size);
            }
            temp = temp->next;
        }
    }
}

bool Shortest_path_bellman(sll_node **Graph_list,int source,int *p,int *d,int V){
    //Initialization
    for(int i=0;i<V;i++){
        p[i] = i;
        d[i] = 1000000000+7;
    }
    d[source] = 0;
    sll_node *temp;
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            temp = Graph_list[j];
            while(temp!=NULL){
                if(d[j] + temp->weight < d[temp->node]){
                    d[temp->node] = d[j] + temp->weight;
                    p[temp->node] = j;
                }
                temp = temp->next;
            }
        }
    }
    for(int i=0;i<V;i++){
        temp = Graph_list[i];
        while(temp!=NULL){
            if(d[temp->node]+temp ->weight <d[i]){
                return false;
            }
            temp=temp->next;
        }
    }
    return true;
}
//Single source shortest path ends
//All pair shortest path algorithm(only calculates distance)
void Shortest_distance_floyed(sll_node **Graph_list,int **d,int V){
    //Initialization
    sll_node *temp;
    for(int i=0;i<V;i++){
        temp = Graph_list[i];
        while(temp!=NULL){
            d[i][temp->node] = temp->weight;
            temp=temp->next;
        }
    }
    for(int k=0;k<V;k++){
        for(int i=0;i<V;i++){
            for(int j=0;j<V;j++){
                if(d[i][j]>d[i][k] + d[k][j]){
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
}
//All pair shortest path ends

//MST generation out of undirected connected graph
int ** MST_kruskal(sll_node **Graph_list,int V){
    //Initialization
    int **G=(int **)malloc(sizeof(int *)*V);
    for(int i=0;i<V;i++){
        G[i] = (int *)malloc(sizeof(int)*V);
        for(int j=0;j<V;j++){
            G[i][j] = 0;
        }
    }
    int E=0;
    sll_node *temp;
    for(int i=0;i<V;i++){
        temp = Graph_list[i];
        while(temp!=NULL){
            E++;
            temp = temp->next;
        }
    }
    data *edge_array = (data*)malloc(sizeof(data)*E);
    int k=0;
    for(int i=0;i<V;i++){
        temp = Graph_list[i];
        while(temp!=NULL){
            edge_array[k].data1 = temp->weight;
            edge_array[k].data2 = i;
            edge_array[k].data3 = temp->node;
            k++;
            temp = temp->next;
        }
    }
    merge_sort(edge_array,0,E-1);
    int *set_array = (int *)malloc(sizeof(int)*V);
    int *set_rank = (int *)malloc(sizeof(int)*V);
    for(int i=0;i<V;i++){
        set_array[i] = i;
        set_rank[i] = 1;
    }
    for(int i=0;i<E;i++){
        if(uf_union(set_array,set_rank,edge_array[i].data2,edge_array[i].data3)){
            G[edge_array[i].data2][edge_array[i].data3] = edge_array[i].data1;
        }
    }
    return G;
}
//MST end++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Maximum flow algorithm================================================
int minimum(int a,int b){
    return (a<b?a:b);
}
int *BFS_find_path(int **Graph_mat,int V,int s,int d){
    //If no path, sends NULL pointer
    int *parent_path = (int *)malloc(sizeof(int)*V);
    bool *visited = (bool *)malloc(sizeof(bool)*V);
    for(int i=0;i<V;i++){
        parent_path[i] = i;
        visited[i] = false;
    }
    sll_node *Q_head=NULL;
    sll_node *Q_tail = NULL;
    enq(&Q_head,&Q_tail,s);
    visited[s] = true;
    int temp_node;
    while(Q_tail!=NULL){
        temp_node = deq(&Q_tail);
        for(int i=0;i<V;i++){
            if(Graph_mat[temp_node][i]!=0 && (!visited[i])){
                enq(&Q_head,&Q_tail,i);
                visited[i] = true;
                parent_path[i] = temp_node;
            }
        }
    }
    if(visited[d]){
        return parent_path;
    }
    else{
        return NULL;
    }
}

int **Max_flow_ford_fulkerson(int **Graph_mat,int V,int s,int d){
    int **G = (int **)malloc(sizeof(int *)*V);
    for(int i=0;i<V;i++){
        G[i] = (int *)malloc(sizeof(int)*V);
        for(int j=0;j<V;j++){
            G[i][j] = 0;
        }
    }
    int *parent_path=BFS_find_path(Graph_mat,V,s,d);
    int traverse_node;
    int minimum_flow;
    while(parent_path!=NULL){
        traverse_node = d;
        minimum_flow = Graph_mat[parent_path[traverse_node]][traverse_node];
        while(traverse_node!=s){
            minimum_flow = minimum(minimum_flow,Graph_mat[parent_path[traverse_node]][traverse_node]);
            traverse_node = parent_path[traverse_node];
        }
        traverse_node = d;
        while(traverse_node!=s){
            Graph_mat[parent_path[traverse_node]][traverse_node] = Graph_mat[parent_path[traverse_node]][traverse_node]-minimum_flow;
            Graph_mat[traverse_node][parent_path[traverse_node]] = Graph_mat[traverse_node][parent_path[traverse_node]]+minimum_flow;
            G[parent_path[traverse_node]][traverse_node] = G[parent_path[traverse_node]][traverse_node]+minimum_flow;
            traverse_node = parent_path[traverse_node];
        }
        parent_path = BFS_find_path(Graph_mat,V,s,d);
    }
    return G;
}
//Maximum flow algorithm end++++++++++++++++++++++++++++++++++++++++++++++
int main(){
/*
//Merge sort check====================================================
    int sz = 20;
    data *mydata = new data[sz];
    for(int i=0;i<sz;i++){
        mydata[i].data1 = rand()%100;
        cout << mydata[i].data1 << " ";
    }
    cout << endl;
    merge_sort(mydata,0,sz-1);
    for(int i=0;i<sz;i++){
        cout << mydata[i].data1 << " ";
    }
//Merge sort check end++++++++++++++++++++++++++++++++++++++++++++++++++
*/
/*
//Counting sort check===================================================
    int sz = 20;
    data *mydata = new data[sz];
    for(int i=0;i<sz;i++){
        mydata[i].data1 = rand()%50;
        cout << mydata[i].data1 << " ";
    }
    cout << endl;
    count_sort(mydata,0,sz-1);
    for(int i=0;i<sz;i++){
        cout << mydata[i].data1 << " ";
    }
//Counting sort check end+++++++++++++++++++++++++++++++++++++++++++++++++
*/
/*
//Pattern matching check==================================================
    char *str_main = "A quick brown fox jumped somewhere!";
    char *str = "fox";
    int pos = pattern_match(str_main,str);
    cout << pos << endl;
//Pattern matching end++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

//Graph check==========================================================
    int V=6;
    int **Graph_mat;
    sll_node **Graph_list;
    //Generate random graph
    Graph_mat = (int **)malloc(sizeof(int *)*V);
    for(int i=0;i<V;i++){
        Graph_mat[i] = (int *)malloc(sizeof(int)*V);
        for(int j=0;j<V;j++){
            Graph_mat[i][j] = rand()%2;
            //cout << Graph_mat[i][j] << " ";
        }
        Graph_mat[i][i]=0;
        //cout << endl;
    }
    Graph_list = Graph_mat_to_list(Graph_mat,V);

    sll_node *temp;
    for(int i=0;i<V;i++){
        cout << i << " is connected to ";
        temp = Graph_list[i];
        while(temp!=NULL){
            cout << temp->node << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    //Graph_BFS(Graph_mat,V);
    //Graph_BFS(Graph_list,V);
    //Graph_DFS(Graph_mat,V);
    //Graph_DFS(Graph_list,V);
    /*if(Graph_directed_to_dag(Graph_mat,V)){
        cout << "DAG creation completed"<< endl;
    }
    else{
        cout << "DAG cannot be created" << endl;
    }
    Graph_mat[0][4]  =1;
    Graph_mat[1][5]  =1;
    Graph_mat[2][5]  =1;
    Graph_list = Graph_mat_to_list(Graph_mat,V);
    int *topo_sort = Graph_topological_sort(Graph_list,V);
    for(int i=0;i<V;i++){
        cout << topo_sort[i] << " ";
    }*/
    //Creating a weighted graph out of unweighted graph
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(Graph_mat[i][j]==1){
                Graph_mat[i][j] = (rand()%10) +1;
            }
        }
    }
    cout << endl;
    /*Graph_list = Graph_mat_to_list(Graph_mat,V);
    for(int i=0;i<V;i++){
        cout << i << " is connected to ";
        temp = Graph_list[i];
        while(temp!=NULL){
            cout << temp->node << " (" << temp->weight << ")";
            temp = temp->next;
        }
        cout << endl;
    }*/
    /*
    int *parent_relation = (int *)malloc(sizeof(int)*V);
    int *distance = (int *)malloc(sizeof(int)*V);
    int source = 0;
    Shortest_path_dijktra(Graph_list,source,parent_relation,distance,V);
    if(Shortest_path_bellman(Graph_list,source,parent_relation,distance,V)){
        cout << "No negative cycle" << endl;
    }
    else{
        cout << "Negative cycle detected" << endl;
    }
    for(int i=0;i<V;i++){
        cout << parent_relation[i] << " " << distance[i] << endl;
    }
    */
    /*int **distance_matrix= (int **)malloc(sizeof(int *)*V);
    for(int i=0;i<V;i++){
        distance_matrix[i] = (int *)malloc(sizeof(int)*V);
        for(int j=0;j<V;j++){
            distance_matrix[i][j] = 100000000+7;
        }
        distance_matrix[i][i] = 0;
    }
    Shortest_distance_floyed(Graph_list,distance_matrix,V);
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            cout << distance_matrix[i][j] << " ";
        }
        cout << endl;
    }*/
    //Graph_directed_to_undirected(Graph_mat,V);
    //Graph_list = Graph_mat_to_list(Graph_mat,V);
    /*for(int i=0;i<V;i++){
        cout << i << " is connected to ";
        temp = Graph_list[i];
        while(temp!=NULL){
            cout << temp->node << " (" << temp->weight << ")";
            temp = temp->next;
        }
        cout << endl;
    }
    cout << endl;
    int **Graph_mat_mst = MST_kruskal(Graph_list,V);
    sll_node **Graph_list_mst = Graph_mat_to_list(Graph_mat_mst,V);
        for(int i=0;i<V;i++){
        cout << i << " is connected to ";
        temp = Graph_list_mst[i];
        while(temp!=NULL){
            cout << temp->node << " (" << temp->weight << ")";
            temp = temp->next;
        }
        cout << endl;
    }*/
    int source = 0;
    int destination = 5;
    //Checking utility functions
    /*int *parent_path=BFS_find_path(Graph_mat,V,source,destination);
    int traverse_node = destination;
    while(traverse_node!=source){
        //minimum_flow = minimum(minimum_flow,Graph_mat[parent_path[traverse_node]][traverse_node]);
        cout << parent_path[traverse_node] << " " <<traverse_node << " " << Graph_mat[parent_path[traverse_node]][traverse_node] << endl;
        traverse_node = parent_path[traverse_node];
    }*/
    int **G = Max_flow_ford_fulkerson(Graph_mat,V,source,destination);
    sll_node **Graph_list_max_flow = Graph_mat_to_list(G,V);
    for(int i=0;i<V;i++){
        cout << i << " is connected to ";
        temp = Graph_list_max_flow[i];
        while(temp!=NULL){
            cout << temp->node << " (" << temp->weight << ")";
            temp = temp->next;
        }
        cout << endl;
    }
    cout << endl;
//Graph check end+++++++++++++++++++++++++++++++++++++++++++++++++++++++

    return 0;
}

