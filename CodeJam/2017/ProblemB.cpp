#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int T;
long long int N;
long long int ans;

int main(){
	cin >> T;
	vector<int> input_digit;
    vector<int> output_digit;
	while(T--){
		input_digit.clear();
		cin >> N;
		while(N!=0){
			input_digit.push_back(N%10);
			N = N/10;
		}
		output_digit.push_back(input_digit[0]);
		for(int i=1;i<input_digit.size()-1;i++){
            if(input_digit[i]<input_digit[i+1]){
                input_digit[i] = input_digit[i-1];
            }
            output_digit.push_back(input_digit[i]);
		}
		output_digit.push_back(input_digit[input_digit.size()]);
	}
	return 0;
}
