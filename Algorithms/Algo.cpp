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
    char data2;
    int data3;
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
            temp[running_index].data1 = mydata[left_index].data1;
            left_index++;
        }
        else{
            temp[running_index].data1 = mydata[right_index].data1;
            right_index++;
        }
        running_index++;
    }
        while(left_index<=middle_index){
            temp[running_index].data1 = mydata[left_index].data1;
            running_index++;
            left_index++;
        }
        while(right_index<=end_index){
            temp[running_index].data1= mydata[right_index].data1;
            running_index++;
            right_index++;
        }
    running_index=0;
    left_index = start_index;
    while(left_index<=end_index){
        mydata[left_index].data1 = temp[running_index].data1;
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

//Graph Algorithms
// 1. BFS
// 2. DFS
// 3. Single source shortest path (Digstras and Bellman fords)
// 4. Minimum Spanning tree (Kruskals and Prims)
// 5. All pair shortest path (Floyed Warshall)
// 6. Topological sorting (indegree and stack method)
// 7. Maximum Flow algorithm(Ford fulkersons algorithm)

//We will include both adjency matrix and adjency list implementation
//in all algorithms disabling one while checking
//Graph utilities of no use^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
sll_node **Graph_mat_to_list(int **Graph_mat,int V){
    sll_node **G = (sll_node **)malloc(sizeof(sll_node *)*V);
    for(int i=0;i<V;i++){
        G[i] = NULL;
    }
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(Graph_mat[i][j]==1){
                sll_node *temp = (sll_node *)malloc(sizeof(sll_node));
                temp->node = j;
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

//Graph check end+++++++++++++++++++++++++++++++++++++++++++++++++++++++

    return 0;
}

