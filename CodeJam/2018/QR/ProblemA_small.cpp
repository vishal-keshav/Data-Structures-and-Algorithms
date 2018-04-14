//Small test case
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
	long long int l,n,s,d;
	int nr_case=1;
	cin >> T;
	while(T--){
		cin >> D >> prog;
		s = 1;
		n = 0;
		if(prog.size()-1>D){
            cout << "Case #" << nr_case << ": IMPOSSIBLE" << endl;
            nr_case++;
		}
		else{
            for(int i=0;i<prog.size();i++){
                if(prog[i]=='C'){//First and last charge
                    l = (prog.size() - i -1);
                    d = (D - i);
                    s = s*2;
                }
                else{
                    n = n+s;
                }
            }
            if(s==1){//There was no charging
                if(prog.size()>D){
                    cout << "Case #" << nr_case << ": IMPOSSIBLE" << endl;
                    nr_case++;
                }
                else{
                    cout << "Case #" << nr_case << ": 0" << endl;
                    nr_case++;
                }
            }
            else{
                cout << "Case #" << nr_case << ": " << (2*l - d) << endl;
                nr_case++;
            }
		}
	}
	return 0;
}
