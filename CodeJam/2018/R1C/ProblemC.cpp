/*Ant Stack*/
#include<iostream>
using namespace std;

long long int wt[100000][500];
long long int min(long long int x1,long long int x2){
	if(x1<x2){
		return x1;
	}
	return x2;
}
int main(){
	int T;
	cin>>T;
	for(int t=1;t<=T;t++){
		int N;
		cin>>N;
		int W[N];
		for(int i=0;i<N;i++){
			cin>>W[i];
		}

		for(int i=0;i<N;i++){
			for(int j=0;j<500;j++){
				wt[i][j]=0;
			}
		}
		int length =1;
		for(int i=0;i<N;i++){
			for(int j=0;j<500;j++){
				if(j>i){
					break;
				}
				if(i==0){
					wt[0][0]=W[i];
					break;
				}
				else{
					int flag=0;
					if(j==0){
						wt[i][j]=min(wt[i-1][j],W[i]);
						flag = 1;
					}
					else{
						if(wt[i-1][j]==0){
							if(wt[i-1][j-1]<=6*W[i]){
								wt[i][j]=wt[i-1][j-1]+W[i];
								flag = 1;
							}
							break;
						}
						else{

							if(wt[i-1][j-1]+W[i]<wt[i-1][j]&& wt[i-1][j-1]<=6*W[i]){
								wt[i][j]=wt[i-1][j-1]+W[i];
								flag = 1;
							}
							else{
								wt[i][j]=wt[i-1][j];
								flag = 1;
							}
						}
					}
					if(flag==0){
						break;
					}
				}
			}
		}
		int ans=1;
		for(int j=0;j<500;j++){
			if(wt[N-1][j]!=0){
				ans=j+1;
			}
		}

		cout<<"Case #"<<t<<": "<<ans<<endl;
	}
	return 0;
}
