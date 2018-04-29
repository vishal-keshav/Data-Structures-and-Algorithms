#include<iostream>
#include <algorithm>
using namespace std;
long long int N,L,T;
long long int findITR(long long int start,long long int remg,long long int init){
	if(remg ==1||remg ==0)
	return remg;
	long long int itr=0;
	long long int itr1 = start;
	for(long long int i=start;i<=remg;i=i*2){
		long long int no=(init+i*100)%N;
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
		long long int no=(init+remg*100)%N;
		if(no*2>=N){
			return itr1 + findITR(1,remg-itr1,(init+itr1*100)%N);
		}
		else return remg;
	}
	return 0;
}
int main(){

	cin>>T;
	for(long long int i=1;i<=T;i++){
		cin>>N>>L;
		long long int sumValue=0;
		long long int a[L];
		for(long long int i=0;i<L;i++){
			cin>>a[i];
			sumValue+=a[i];
		}
		long long int b[L];
		for(long long int i=0;i<L;i++){
			b[i]=(a[i]*100)%N;
		}
		sort(b,b+L);
		long long int remg = N-sumValue;
		long long int ans = 0;
		for(long long int i=0;i<L;i++){
			long long int no =(a[i]*100)%N;
			//cout<<"no "<<no <<" ";
			if(no*2>=N){
				ans+=((a[i]*100)/N)+1;
			}
			else{
				long long int value = findITR(1,remg,no);
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
			long long int value = findITR(1,remg,0);
			//cout<<" value ="<<value<<endl;
			if(value!=remg){
				long long int counter = remg/value;
				long long int no= (value*100)%N;
				if(no*2>=N){
					ans+=counter*((value*100)%N+1);
				}
				else{
					ans+=counter*((value*100)%N);
				}
				ans+=((remg-value)*100)%N;
			}
			else{
				long long int no= (value*100)%N;
				if(no*2>=N){
					ans+=((value*100)/N+1);
					//long long int var =(value*100)%N;
					//cout<<" value = "<<value<<"N = "<<N<<endl;
				}
				else{
					ans+=((value*100)/N);
					//long long int var =(value*100)%N;
					//cout<<" value = "<<value<<"var = "<<var<<endl;
				}
			}
		}

		cout<<"Case #"<<i<<": "<<ans<<endl;
	}
}
