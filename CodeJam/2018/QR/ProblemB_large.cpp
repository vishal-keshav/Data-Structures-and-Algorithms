#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int T,N;
vector<vector<long long int> > list(2);

int main(){
	int nr_case = 1;
	cin >> T;
	while(T--){
		cin >> N;
		list[0].clear();
		list[0].resize(N/2 + N%2);
		list[1].clear();
		list[1].resize(N/2);
		for(int i=0;i<N;i++){
			cin >> list[i%2][i/2];
		}
		sort(list[0].begin(), list[0].end());
		sort(list[1].begin(), list[1].end());
		int index = -1;
		int j;
		for(int i=0;i<N-1;i++){
			j = i+1;
			if(list[i%2][i/2] > list[j%2][j/2]){
				index = i;
				break;
			}
		}
		if(index == -1){
			cout << "Case #" << nr_case << ": OK" << endl;
		}
		else{
			cout << "Case #" << nr_case << ": " << index << endl;
		}
		nr_case++;
	}
}