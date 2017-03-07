//Description

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

class seg_tree{
	#define INT_MAX_OPS 0
	#define INT_MIN_OPS 1
	#define INT_SUM_OPS 2
	public:
		seg_tree(vector<long int> vec, int operation){
			nr_elem = vec.size();
			ops = operation;
			tree_size = (long int)(2 * pow(2.0, floor((log((double)nr_elem) / log(2.0)) + 1)));
			segment_tree.resize(tree_size,0);
			init_segment_tree(0,0,nr_elem-1);
			input_vec = vec;
		}
		long int query(long int s_index, long int e_index){
			return query_util(1,0,nr_elem-1,s_index,e_index);
		}

	private:
		long int nr_elem, ops,tree_size;
		vector<long int> segment_tree;
		vector<long int> input_vec;

		void init_segment_tree(long int node, long int start_index, long int end_index){
			if(start_index == end_index){
				if(ops==INT_MIN_OPS || ops==INT_MAX_OPS){
					segment_tree[node] = start_index;
				}
				else{
					segment_tree[node] = input_vec[start_index];
				}
			}
			else{
				long int left_child = 2*node;
				long int right_child = 2*node + 1;
				init_segment_tree(left_child, start_index, (start_index+end_index)/2);
				init_segment_tree(right_child, (start_index+end_index)/2 + 1, end_index);
				long int left_result = segment_tree[left_child];
				long int right_result = segment_tree[right_child];

				if(ops==INT_SUM_OPS){
					segment_tree[node] = left_result + right_result;
				}
				else{
					long int left_value = input_vec[left_result];
					long int right_value = input_vec[right_result];
					if(ops==INT_MAX_OPS){
						segment_tree[node] = (left_value>=right_value)? left_result:right_result;
					}
					else{
						segment_tree[node] = (left_value<=right_value)? left_result:right_result;
					}
				}
			}
		}
		long int query_util(long int node, long int interval_start, long interval_end, long int i, long int j){
			if(i>interval_end || j<interval_start){
				return -1;
			}
			if(interval_start>=i && interval_end <=j){
				return segment_tree[node];
			}

			long int pos1 = query_util(2*node,interval_start, (interval_start+interval_end)/2, i, j);
			long int pos2 = query_util(2*node+1, (interval_start+interval_end)/2 + 1, interval_end, i, j);
			if(pos1==-1){
				return pos2;
			}
			if(pos2==-1){
				return pos1;
			}

			switch(ops){
				case INT_MAX_OPS:
					return input_vec[pos1]>=input_vec[pos2]? pos1:pos2;
				case INT_MIN_OPS:
					return input_vec[pos1]<=input_vec[pos2]? pos1:pos2;
				case INT_SUM_OPS:
					return pos1+pos2;
			}
		}
};

int main(){
	vector<long int> vec = {10,2,47,3,9,1,98,21,37};
	seg_tree sg(vec,1);
	//cout << sg.query(1,7) << " " << sg.query(3,8) << endl;

	return 0;
}
