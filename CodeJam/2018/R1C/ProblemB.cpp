#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
  int T,N,D,pref_flavour;
  cin >> T;
  while(T--){
    cin >> N;
    //Maintain a map of flavour sold
    vector<bool> sold(false, N);
    //Read preference for each customer
    for(int i=0;i<N;i++){
      cin >> D;
      vector<int> pref;
      for(int j=0;j<D;j++){
        cin >> pref_flavour;
        pref.push_back(pref_flavour);
      }
      //Algo1: Sell the very first preference
      bool disappointed = true;
      for(int i=0;i<D;i++){
        if(!sold[pref[i]]){
          sold[pref[i]] = true;
          cout << pref[i] << endl;
          fflush(stdout);
          disappointed = false;
          break;
        }
      }
      if(disappointed){
        cout << -1 << endl;
        fflush(stdout);
      }
    }
  }
  return 0;
}
