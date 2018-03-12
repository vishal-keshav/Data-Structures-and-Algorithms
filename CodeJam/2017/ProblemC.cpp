#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int T;
unsigned long long int N,K;
unsigned long long int y,z;

void compute(void){
	for(int i=0;i<K-1;i++){
		N = N/2;
	}
	y = N/2;
	if(N%2 == 0){
        if(y>0){
            z = y - 1;
        }
        else{
            z = 0;
        }
	}
	else{
        z = y;
	}
	//z = y - (N%2==0)?1:0;
	return;
}

int main(){
	int nr_case = 1;
	cin >> T;
	while(T--){
		cin >> N >> K;
		compute();
		cout << "Case #" << nr_case << ": " << y << " " << z << endl;
		nr_case++;
	}

	return 0;
}
