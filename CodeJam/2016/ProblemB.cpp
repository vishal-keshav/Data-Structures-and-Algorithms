#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int T;
string input;

int main(){
	int nr_case= 1;
	int ans;
	cin >> T;
	while(T--){
		cin >> input;
		ans = 0;
		char prev = input[0];
		for(int i=1;i<input.size();i++){
			if(prev!=input[i]){
				ans++;
				prev = input[i];
			}
		}
		ans = (prev=='-')?(ans+1):ans;
		cout << "Case #" << nr_case << ": " << ans << endl;
		nr_case++;
	}
	return 0;
}
