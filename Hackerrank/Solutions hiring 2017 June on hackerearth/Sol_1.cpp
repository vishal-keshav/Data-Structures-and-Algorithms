#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

#define max_mod 1000000007

using namespace std;

long int N, Q;
long int max_N;

vector<long int> arr;

long int calc_gcd(long int a, long int b){
    if(b){
        return calc_gcd(b, a%b);
    }
    else{
        return a;
    }
}

/*Segment tree*/
vector<long int> segment_tree;

void init_seg(long int node, long int s_index, long int e_index);

void init_seg_tree(vector<long int> vec){
	long int nr_elem = vec.size();
	long int tree_size = (long int)(2 * pow(2.0, floor((log((double)nr_elem) / log(2.0)) + 1)));
	segment_tree.resize(tree_size,999);
	init_seg(1,0,nr_elem-1);
}
void init_seg(long int node, long int s_index, long int e_index){
	if(s_index==e_index){
		segment_tree[node] = arr[s_index];
	}
	else{
		long int left_child = 2*node;
		long int right_child = 2*node + 1;
		init_seg(left_child, s_index, (s_index+e_index)/2);
		init_seg(right_child, (s_index+e_index)/2 + 1, e_index);
		segment_tree[node] = calc_gcd(segment_tree[left_child], segment_tree[right_child]);
	}
}

long int seg_query(long int node, long int s_index, long int e_index, long int i, long int j){
	if(i>e_index || j<s_index){
		return -1;
	}
	if(s_index>=i && e_index<=j){
		return segment_tree[node];
	}
	long int left_ret = seg_query(2*node, s_index, (s_index+e_index)/2, i, j);
	long int right_ret = seg_query(2*node + 1, (s_index+e_index)/2 + 1, e_index, i, j);
	if(left_ret==-1){
		return right_ret;
	}
	if(right_ret==-1){
		return left_ret;
	}
	return calc_gcd(left_ret, right_ret);
}


long int calc_fibo(long int input){
    long int var_a = 1;
    long int var_b = 1;
    long int temp_var;
    long int running_index = 2;
    while(input>running_index){
        temp_var = (var_a + var_b)%max_mod;
        var_a = var_b;
        var_b = temp_var;
        running_index++;
    }
    return (var_b);
}

int main()
{
    long int L,R;
    cin >> N >> Q;
    max_N = 0;
    arr.resize(N);
    for(long int i=0;i<N;i++){
        cin >> arr[i];
        if(max_N<arr[i]){
            max_N = arr[i];
        }
    }
	init_seg_tree(arr);
    for(long int i=0;i<Q;i++){
        cin >> L >> R;
		cout << calc_fibo(seg_query(1,0,N-1,L-1,R-1)) << endl;
    }
    return 0;
}
