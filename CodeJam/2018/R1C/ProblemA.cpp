#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <bits/stdc++.h>

using namespace std;

#define LEN 2009
#define MOD 1000000007

typedef long long ll;

int T;
int ar[LEN];

int main(){
  int nr_case = 1;
	/*ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);*/
	cin>>T;
	while(T--){
		int n,l;
		unordered_map<string,int> map_unordered;
		set<char> fc[10];
		string s[LEN];
		cin>>n>>l;
		for(int i=0;i<n;i++)
		{
			cin>>s[i];
			map_unordered[s[i]]=1;
			for(int j=0;j<l;j++)
				fc[j].insert(s[i][j]);
		}

		string ans="-";

		for(int i=0;i<l;i++){
			if(fc[i].size()==1)continue;
			for(auto it=fc[i].begin();it!=fc[i].end();it++){
				char ch= *it;
				for(int j=0;j<n;j++){
					if(s[j][i]==ch){
            continue;
          }
					s[j][i]=ch;
					if(map_unordered.find(s[j])==map_unordered.end()){
						ans=s[j];
						goto algo;
					}
				}
			}
		}
		algo:
		cout<<"Case #" << nr_case <<": " << ans << endl;
    nr_case++;
	}
	return 0;
}
