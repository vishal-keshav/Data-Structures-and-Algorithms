#include <bits/stdc++.h>
using namespace std;
#define MX 207
int main()
{
	int t;
	cin>>t;
	for(int tc=1;tc<=t;tc++)
	{
		int n;
		int sold[MX]={},cnt[MX]={};
		cin>>n;
		for(int i=0;i<n;i++)
		{
			int num,pref[MX],j;
			cin>>num;
			for(j=0;j<num;j++)
				cin>>pref[j],cnt[pref[j]]++;
			int ans=-1;
			for(j=0;j<num;j++)
			{
				// cout<<"for "<<pref[j]<<", "<<sold[pref[j]]<<endl;
				if(!sold[pref[j]])
				{
					if(ans==-1)ans=pref[j];
					else if(cnt[pref[j]]<cnt[ans])
						ans=pref[j];
				}
			}
			if(ans!=-1)sold[ans]=1;
			cout<<ans<<endl;
			fflush(stdout);
		}
	}
	return 0;
}
