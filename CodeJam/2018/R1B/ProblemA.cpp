#include<iostream>
#include <algorithm>
using namespace std;
int N,L,T;
int findITR(int start,int remg,int init){
	if(remg ==1||remg ==0)
	return remg;
	int itr=0;
	int itr1 = start;
	for(int i=start;i<=remg;i=i*2){
		int no=(init+i*100)%N;
		if(no*2>=N){
			itr=i;
			break;
		}
		itr1=i;
	}
	if(itr == start)
	return itr;
	if(itr!=0){
		return itr1 + findITR(1,itr1,(init+itr1*100)%N);
	}
	else {
		int no=(init+remg*100)%N;
		if(no*2>=N){
			return itr1 + findITR(1,remg-itr1,(init+itr1*100)%N);
		}
		else return remg;
	}
	return 0;
}
int main(){

	cin>>T;
	for(int i=1;i<=T;i++){
		cin>>N>>L;
		int sumValue=0;
		int a[L];
		for(int i=0;i<L;i++){
			cin>>a[i];
			sumValue+=a[i];
		}
		int b[L];
		for(int i=0;i<L;i++){
			b[i]=(a[i]*100)%N;
		}
		sort(b,b+L);
		int remg = N-sumValue;
		int ans = 0;
		for(int i=0;i<L;i++){
			int no =(a[i]*100)%N;
			//cout<<"no "<<no <<" ";
			if(no*2>=N){
				ans+=((a[i]*100)/N)+1;
			}
			else{
				int value = findITR(1,remg,no);
				//cout<<"i= "<<i<<" value ="<<value<<endl;
				ans+=((a[i]+value)*100)/N;
				no = ((a[i]+value)*100)%N;
				if(no*2>=N){
					ans+=1;
				}
				remg = remg-value;
			}
			//cout<<"ans = "<<ans<<endl;
		}
		//cout<<"remg = "<<remg<<endl;
		if(remg!=0){
			int value = findITR(1,remg,0);
			//cout<<" value ="<<value<<endl;
			if(value!=remg){
				int counter = remg/value;
				int no= (value*100)%N;
				if(no*2>=N){

					ans+=counter*((value*100)/N+1);
				}
				else{
					ans+=counter*((value*100)/N);
				}
				ans+=((remg-value)*100)%N;
			}
			else{
				int no= (value*100)%N;
				if(no*2>=N){
					ans+=((value*100)/N+1);
					//int var =(value*100)%N;
					//cout<<" value = "<<value<<"N = "<<N<<endl;
				}
				else{
					ans+=((value*100)/N);
					//int var =(value*100)%N;
					//cout<<" value = "<<value<<"var = "<<var<<endl;
				}
			}
		}

		cout<<"Case #"<<i<<": "<<ans<<endl;
	}
}
