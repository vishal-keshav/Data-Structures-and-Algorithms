//Large test case
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

long long int T,D,N;
string prog;

int main(){
	long long int n,s;
	long long int nr_charge, nr_shoot;
	int nr_case=1;
	cin >> T;
	while(T--){
		cin >> D >> prog;
		s = 1;
		n = 0;
		nr_charge = 0;
		nr_shoot = 0;
		vector<int> c(prog.size(),0);
		int j=0;
		for(int i=0;i<prog.size();i++){
			if(prog[i]=='C'){//Multiple(possibly zero) charges
				nr_charge++;
				s = s*2;
				j++;
			}
			else{
				nr_shoot++;
				n = n+s;
				c[j]++;
			}
		}
		//Invalid cases
		if(nr_shoot > D){
			cout << "Case #" << nr_case << ": IMPOSSIBLE" << endl;
			nr_case++;
		}
		else if(nr_charge == prog.size()){
			cout << "Case #" << nr_case << ": 0" << endl;
			nr_case++;
		}
		else{
			//Start from last valid constant
			while(c[j]==0 && j>=0){
				j--;
			}
			int steps = 0;
			while(n > D){
				c[j]--;
				c[j-1]++;
				n = n - pow(2,j-1);
				steps++;
				if(c[j] == 0){
					j--;
				}
			}
			cout << "Case #" << nr_case << ": " << steps << endl;
			nr_case++;
		}
	}
	return 0;
}
