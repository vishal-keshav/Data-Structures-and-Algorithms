/* The motivation of creating this file is to construct every possible data structure and its use cases,
     with minimal functionality and code lines, so that it can be easily implemented and used in case
     of no availability of stl libraries provided by C++. Each data structure implemented is easy to
     understand and implement on the go with minimum effort and time.*/

/* Author-Vishal Keshav
    email-bulletcross@gmail.com
    www.github.com/bulletcross
/*

/* Data structure implemented are as follow:
    1. Singly linked list
    2. Doubly linked list
    3. Stack
    4. Queue
    5. Heap
    6. Binary Tree
    7. Binary Search Tree
    8. Balanced Binary Search Tree
    9. Graph
    10. Hash
    11. Union-find
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//A generic data structure
struct data{
    int data1;
    char data2;
    int data3;
};

//Singly Linked List start************************************************************
struct sll_node{
    data mydata;
    sll_node * next;
};
//singly Linked List end~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Doubly Linked List start***********************************************************
struct dll_node{
    data mydata;
    dll_node *next;
    dll_node *prev;
};
//Doubly Linked List end~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Stack start*************************************************************************
//Uses already created singly linked list structure
void push(sll_node **head,data mydata){
    sll_node *newnode = (sll_node *)malloc(sizeof(sll_node));
    newnode->mydata=mydata;
    newnode->next=(*head);
    (*head)=newnode;
}
data pop(sll_node **head){
    sll_node * newnode=(*head);
    (*head)=newnode->next;
    data mydata=newnode->mydata;
    free(newnode);
    return mydata;
}
//Stack end~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Queue start**************************************************************************
//Uses already created singly linked list structure
void enq(sll_node **head,sll_node **tail,data mydata){
    sll_node * newnode = (sll_node *)malloc(sizeof(sll_node));
    newnode->mydata = mydata;
    newnode->next=NULL;
    if((*head)==NULL){
        (*head)=newnode;
        (*tail)=newnode;
    }
    else{
        (*head)->next = newnode;
        (*head)=newnode;
    }
}
data deq(sll_node **tail){
    sll_node *newnode = (*tail);
    data mydata = newnode->mydata;
    (*tail)=newnode->next;
    free(newnode);
    return mydata;
}
//Queue end~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Heap Start*****************************************************************************
    //Fixed size heap should be declared
    //Defining functions for min heap
    //This heapify is a non recursive efficient version and does not use unnecessary swap and child functions
    void heapify(int *heap,int index,int current_size){
        int left;
        int right;
        int min_index=index;
        int temp;
        do{
            index=min_index;
            left = 2*index +1;
            right=2*index+2;
            if(left<current_size && heap[min_index]>heap[left]){
                min_index = left;
            }
            if(right<current_size && heap[min_index]>heap[right]){
                min_index = right;
            }
            temp=heap[min_index];
            heap[min_index]=heap[index];
            heap[index]=temp;
        }while(min_index!=index && min_index<current_size);
    }
    //current size will increase by one assuming all the checks have been done in main code
    void heap_insert(int *heap,int key,int *current_size){
        int index=(*current_size);
        int parent=(index-1)/2;
        int temp;
        heap[index]=key;
        (*current_size)=(*current_size)+1;
        while(index>0 && heap[parent]>heap[index]){
            temp=heap[parent];
            heap[parent]=heap[index];
            heap[index]=temp;
            index=parent;
            parent=(index-1)/2;
        }
    }
    //Extracting minimum is based on assumptions that proper checks have been made for empty heap
    int extract_min(int *heap,int *current_size){
        int minimum=heap[0];
        int index = (*current_size)-1;
        (*current_size)=(*current_size)-1;
        heap[0]=heap[index];
        heapify(heap,0,index);
        return minimum;
    }
//Heap end~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Binary Tree Start************************************************************************
    //Structure is very simple
    struct tree_node{
        data mydata;
        int height;
        tree_node *left;
        tree_node *right;
    };
    //Tree traversal (preorder)
    void preorder(tree_node *root){
        if(root!=NULL){
            printf("%d ",root->mydata.data1);
            preorder(root->left);
            preorder(root->right);
        }
    }
    //Tree traversal (inorder)
    void inorder(tree_node *root){
        if(root!=NULL){
            inorder(root->left);
            printf("%d ",root->mydata.data1);
            inorder(root->right);
        }
    }
    //Tree traversal (post order)
    void postorder(tree_node *root){
        if(root!=NULL){
            postorder(root->left);
            postorder(root->right);
            printf("%d ",root->mydata.data1);
        }
    }
    //For random insertion in a tree
    void tree_insert(tree_node **root,data mydata){
        if((*root)==NULL){
            (*root) = (tree_node *)malloc(sizeof(tree_node));
            (*root)->mydata = mydata;
            (*root)->left=NULL;
            (*root)->right=NULL;
        }
        else{
            int side = rand()%2;
            if(side==0){
                tree_insert(&((*root)->left),mydata);
            }
            else{
                tree_insert(&((*root)->right),mydata);
            }
        }
    }
//Binary Tree end~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Binary Search Tree**********************************************************************
    //Structure used for binary tree is reused
    void search_tree_insert(tree_node **root,data mydata){
        if((*root)==NULL){
            (*root)=(tree_node *)malloc(sizeof(tree_node));
            (*root)->mydata = mydata;
            (*root)->left=NULL;
            (*root)->right=NULL;
        }
        else{
            if((*root)->mydata.data1>mydata.data1){
                search_tree_insert(&((*root)->left),mydata);
            }
            else{
                search_tree_insert(&((*root)->right),mydata);
            }
        }
    }
    //Binary search returns node pointer
    tree_node *search_tree_search(tree_node *root,data mydata){
        tree_node *search_element=root;
        if(search_element->mydata.data1==mydata.data1){
            return search_element;
        }
        else{
            if(mydata.data1<search_element->mydata.data1){
                return search_tree_search(search_element->left,mydata);
            }
            else{
                return search_tree_search(search_element->right,mydata);
            }
        }
    }
//Binary Search Tree end~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Balanced Binary search tree*************************************************************
    //For your knd information, we are implementing AVL tree, not redblack tree which use extra color information
    //We need to implemet rotaion utility function seperately so that code looks clear
    tree_node *right_rotate(tree_node *parent){
        tree_node *left_child = parent->left;
        tree_node *transfer_node = left_child->right;
        parent->left=transfer_node;
        left_child->right=parent;
        int left_height = parent->left!=NULL ? parent->left->height:0;
        int right_height = parent->right!=NULL ? parent->right->height:0;
        parent->height = (left_height > right_height) ? left_height+1 : right_height+1;
        int child_left_height = left_child->left!=NULL ? left_child->left->height:0;
        int child_right_height = left_child->right!=NULL ? left_child->right->height:0;
        left_child->height = (child_left_height > child_right_height) ? child_left_height+1 : child_right_height+1;
        return left_child;
    }
    tree_node *left_rotate(tree_node *parent){
        tree_node *right_child = parent->right;
        tree_node *transfer_node = right_child->left;
        parent->left = transfer_node;
        right_child->left=parent;
        int left_height = parent->left!=NULL ? parent->left->height:0;
        int right_height = parent->right!=NULL ? parent->right->height:0;
        parent->height = (left_height > right_height) ? left_height+1 : right_height+1;
        int child_left_height = right_child->left!=NULL ? right_child->left->height:0;
        int child_right_height = right_child->right!=NULL ? right_child->right->height:0;
        right_child->height = (child_left_height > child_right_height) ? child_left_height+1 : child_right_height+1;
        return right_child;
    }
    //Insert in AVL tree
    tree_node *balanced_tree_insert(tree_node *root,data mydata){
        if(root==NULL){
            tree_node *new_node = (tree_node *)malloc(sizeof(tree_node));
            new_node->left=NULL;
            new_node->right=NULL;
            new_node->height=0;
            new_node->mydata = mydata;
            return new_node;
        }
        else{
            if(mydata.data1 < root->mydata.data1){
                root->left = balanced_tree_insert(root->left,mydata);
            }
            else{
                root->right = balanced_tree_insert(root->right,mydata);
            }
        }
        int left_height = root->left!=NULL ? root->left->height:0;
        int right_height = root->right!=NULL ? root->right->height:0;
        root->height =(left_height > right_height) ? left_height+1 : right_height +1;
        if(left_height - right_height > 1 && mydata.data1<root->left->mydata.data1){
            return right_rotate(root);
        }
        else if(left_height - right_height > 1 && mydata.data1 > root->left->mydata.data1){
            root->left = left_rotate(root->left);
            return right_rotate(root);
        }
        else if(left_height - right_height <-1 && mydata.data1>root->right->mydata.data1){
            return left_rotate(root);
        }
        else if(left_height - right_height <-1 && mydata.data1<root->right->mydata.data1){
            root->right = right_rotate(root->right);
            return left_rotate(root);
        }
        else{
            return root;
        }
    }
//Balance Binary search tree end~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Graph************************************************************************************
    //Since most of the coding problems in challages are based on graph operation like going through neighbours
    //Instead of Adjancy matrix(good for lookup), we go for Adjecency list(good for graph operation)
    //We assume no edge is added twice and we consider undirected graph(as directed graph is more easy)
    void add_edge(sll_node ***graph,int V,int src,int des){
        sll_node **mygraph = (*graph);
        sll_node *destination = (sll_node *)malloc(sizeof(sll_node));
        sll_node *source = (sll_node *)malloc(sizeof(sll_node));
        destination->mydata.data1 = des;
        source->mydata.data1 = src;
        destination->next = mygraph[src];
        mygraph[src] = destination;
        source->next = mygraph[des];
        mygraph[des] = source;
    }
//Graph ends~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Hash*************************************************************************************
    //Hashing collision resolvs in two ways, chaining and open addressing.
    //We chose open addressing as most of the time is is unknown of the elemnets number
    //Defenition of hash function may change
    int hash_function(int data,int N){
        return data%N;
    }
    void hash_in(sll_node **myhash,int data,int *hash_key,int N){
        //If element is not in hash map initailly
        int block = hash_function(data,N);
        sll_node *temp = (sll_node *)malloc(sizeof(sll_node));
        temp->mydata.data3=(*hash_key);
        temp->mydata.data1=data;
        temp->next = myhash[block];
        myhash[block] = temp;
        (*hash_key)++;
    }
    int hash_out(sll_node **myhash,int data,int N){
        int block = hash_function(data,N);
        sll_node *temp = myhash[block];
        while(temp!=NULL){
            //Comarator corresponding to element is used here
            if(temp->mydata.data1==data){
                return temp->mydata.data3;
            }
            temp = temp->next;
        }
        return -1;
    }
//Hash end~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(){
/*
    //Linked list check======================================
    //If head is NULL, linked list is empty
    sll_node * head=NULL;
    //Entering elements in linked list
    for(int i=0;i<5;i++){
        sll_node * newnode = (sll_node *)malloc(sizeof(sll_node));
        newnode->mydata.data1=i;
        newnode->next = head;
        head = newnode;
    }
    //Traversing list and removing element
    sll_node *traverse=head;
    sll_node *removal=traverse;
    while(traverse!=NULL){
        printf("%d ",traverse->mydata.data1);
        traverse=traverse->next;
        free(removal);
        removal = traverse;
    }
    //Linked List check end++++++++++++++++++++++++++++++++++++
*/
/*
    //Doubly Linked list check==================================
    //If head is NULL, list is empty
    //if head and tail are equal, then only one element is there.
    dll_node *head=NULL;
    dll_node *tail=head;
    //Entering elements in linked list consecutively in head and tail.
    //For doubly linked list, make sure to initialize for element and pointers of head and tail.
    if(head==NULL && tail==NULL){
        dll_node *newnode = (dll_node *)malloc(sizeof(dll_node));
        newnode->next=NULL;
        newnode->prev=NULL;
        newnode->mydata.data1=0;
        head=newnode;
        tail=newnode;
    }
    for(int i=1;i<10;i++){
        if(i%2==0){
            dll_node *newnode = (dll_node *)malloc(sizeof(dll_node));
            newnode->mydata.data1=i;
            newnode->next=head;
            newnode->prev=NULL;
            head->prev=newnode;
            head=newnode;
        }
        else{
            dll_node *newnode = (dll_node *)malloc(sizeof(dll_node));
            newnode->mydata.data1=i;
            newnode->prev = tail;
            newnode->next=NULL;
            tail->next=newnode;
            tail=newnode;
        }
    }
    //Traversing list
    dll_node *traverse_forward=head;
    dll_node *traverse_backward=tail;

    //While traversing, head and tail meets and if the crisscross, then special care has to be taken
    while(!(traverse_forward->prev==traverse_backward || (traverse_forward->prev==traverse_backward->next && traverse_forward->prev!=NULL))){
        printf("(%d - %d) ",traverse_forward->mydata.data1,traverse_backward->mydata.data1);
        traverse_forward=traverse_forward->next;
        traverse_backward=traverse_backward->prev;
    }
    //Doubly Linked List end++++++++++++++++++++++++++++++++++++++++
*/

/*
    //Stack Check===============================================
    //We need to manually check if stack is empty by equating it with NULL
    sll_node *mystack=NULL;
    //Pushing elements
    for(int i=0;i<10;i++){
        data mydata;
        mydata.data1=i;
        push(&mystack,mydata);
    }
    //Pop all the elements
    while(mystack!=NULL){
        data mydata = pop(&mystack);
        printf("%d ", mydata.data1);
    }
    //Stack Check end+++++++++++++++++++++++++++++++++++++++++++++
*/
/*
    //Queue Check================================================
    //We need to manually handle head and tail of queue
    sll_node *queue_head=NULL;
    sll_node *queue_tail=NULL;
    //Enqueue elements
    //First eleme
    for(int i=0;i<10;i++){
        data mydata;
        mydata.data1=i;
        enq(&queue_head,&queue_tail,mydata);
    }
    //Dequeue all elements
    //Condition for
    while(queue_tail!=NULL){
        data mydata = deq(&queue_tail);
        printf("%d ",mydata.data1);
    }
    //Queue Check end+++++++++++++++++++++++++++++++++++++++++++++
*/
/*
    //Min-heap Check==============================================
    int *heap;
    int heap_size=20;
    int current_size=0;
    //Declaring heap memory
    heap = (int *)malloc(sizeof(int)*heap_size);
    //Inserting random data
    for(int i=0;i<20;i++){
        int key = rand()%50;
        heap_insert(heap,key,&current_size);
    }
    //Printing the elements and checking extract min and heapify function
    int mini;
    //Canont use current_size instead of 20 because its a dynamic variable
    for(int i=0;i<20;i++){
        for(int j=0;j<20-i;j++){
            printf("%d ",heap[j]);
        }
        mini=extract_min(heap,&current_size);
        printf("[%d]\n",mini);
        //printf("\n");
    }
    //Min-heap Check end+++++++++++++++++++++++++++++++++++++++++++
*/
/*
    //Binary tree check=============================================
    //Construction of a random binary tree
    tree_node *root=NULL;
    data mydata;
    for(int i=0;i<20;i++){
        mydata.data1=rand()%100;
        tree_insert(&root,mydata);
    }
    inorder(root);
    //Binary tree check end+++++++++++++++++++++++++++++++++++++++++++++
*/

/*
    //Binary search tree check===========================================
    //Construction of random elements binary search tree
    tree_node *root = NULL;
    data mydata;
    for(int i=0;i<20;i++){
        mydata.data1=rand()%100;
        search_tree_insert(&root,mydata);
    }
    //Inorder prints elements in sorted format
    inorder(root);
    //Binary search tree check end+++++++++++++++++++++++++++++++++++++++++
*/
/*
    //Balanced Binary search tree check======================================
    tree_node *root = NULL;
    data mydata;
    for(int i=0;i<15;i++){
        mydata.data1=rand()%100;
        root = balanced_tree_insert(root,mydata);
    }
    //Inorder prints elements in sorted format
    inorder(root);
    //Balanced Binary search tree check end+++++++++++++++++++++++++++++++++++
*/
/*
    //Graph check===================================================
    sll_node **graph=NULL;
    int V=4;
    graph = (sll_node **)malloc(sizeof(sll_node *)*V);
    for(int i=0;i<V;i++){
        graph[i]=NULL;
    }
    add_edge(&graph,V,0,1);
    add_edge(&graph,V,0,3);
    add_edge(&graph,V,1,2);
    add_edge(&graph,V,2,3);
    add_edge(&graph,V,3,1);
    //Printing neighbors of each vertex
    sll_node *temp;
    for(int i=0;i<V;i++){
        cout << "Neighbours of " << i << ":";
        temp = graph[i];
        while(temp){
            cout << temp->mydata.data1 << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    //Graph check end+++++++++++++++++++++++++++++++++++++++++++++++++
*/
/*
    //Hash check start=================================================
    sll_node **myhash;
    int hash_size = 10;
    myhash = (sll_node **)malloc(sizeof(sll_node *)*hash_size);
    for(int i=0;i<hash_size;i++){
        myhash[i]=NULL;
    }
    int hash_key;
    hash_key=0;
    int *data_arr = (int *)malloc(sizeof(int)*hash_size);
    for(int i=0;i<hash_size;i++){
        data_arr[i] = rand()%1000;
    }
    //Entering 10 random data to be hashed
    for(int i=0;i<hash_size;i++){
        hash_in(myhash,data_arr[i],&hash_key,hash_size);
    }
    for(int i=0;i<hash_size;i++){
         sll_node *temp = myhash[i];
         while(temp!=NULL){
            cout << temp->mydata.data3 << " ";
            temp = temp->next;
         }
         cout << endl;
        cout << data_arr[i] << " "<<hash_out(myhash,data_arr[i],hash_size) << endl;
    }
    //Hash check end++++++++++++++++++++++++++++++++++++++++++++++++++
*/
    return 0;
}
