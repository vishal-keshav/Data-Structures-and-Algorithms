#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int T,S,K;
string pan;

int revert_pan(int index){
	int ret_index = -1;
	for(int i=0;i<K;i++){
		if(pan[i+index] == '-'){
			pan[i+index] = '+';
		}
		else{
			pan[i+index] = '-';
			if(ret_index == -1){
				ret_index = i+index;
			}
		}
	}
	if(ret_index==-1){
		return index+K;
	}
	else{
		return ret_index;
	}
}

int compute(void){
	int ret = 0;
	int index = 0;
	while(index <= S-K){
		if(pan[index] == '-'){
			index = revert_pan(index);
			ret++;
		}
		else{
			index++;
		}
	}
	for(int i=S-K+1;i<S;i++){
		if(pan[i]=='-'){
			return -1;
		}
	}
	return ret;
}

int compute_optimized(void){
	int ret = 0;
	int flip_counter = 0;
	vector<int> flip_minus(S+1,0);
	for(int i=0;i<=S-K;i++){
		flip_counter = (flip_counter - flip_minus[i]);
		if(pan[i]=='-' && flip_counter%2==0){
			ret++;
			flip_counter++;
			flip_minus[i+K] = flip_counter;
		}
		else if(pan[i]=='+' && flip_counter%2==1){
			ret++;
			flip_counter++;
			flip_minus[i+K] = flip_counter;
		}
		else{
			//do nothing
		}

	}
	for(int i = S-K+1;i<S;i++){
		flip_counter = flip_counter - flip_minus[i];
		if(pan[i]=='-' && flip_counter%2==0){
			return -1;
		}
		else if(pan[i]=='+' && flip_counter%2==1){
			return -1;
		}
		else{
			//do nothing
		}
	}
	return ret;
}

int main(){
	int nr_case = 1;
	int ans;
	cin >> T;
	while(T--){
		cin >> pan >> K;
		S = pan.size();
		//ans = compute();
		ans = compute_optimized();
		if(ans!=-1){
			cout << "Case #" << nr_case << ": " << ans << endl;
		}
		else{
			cout << "Case #" << nr_case << ": IMPOSSIBLE" << endl;
		}
		nr_case++;
	}
}
