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

    return 0;
}

