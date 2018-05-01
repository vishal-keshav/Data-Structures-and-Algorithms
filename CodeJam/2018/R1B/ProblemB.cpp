#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int T;
long long int S;
long long int D_temp, A_temp, B_temp;

long long int M[100005];
long long int N[100005];
long long int ANS_M[100005];
long long int ANS_N[100005];

int main(){
  long long int nr_case = 1;
  long long int nr_count;
  long long int current_max;
  cin >> T;
  while(T--){
    cin >> S;
    //We re-use the buffer
    for(long long int i=0;i<S;i++){
      cin >> D_temp >> A_temp >> B_temp;
      M[i] = D_temp + A_temp;
      N[i] = D_temp - B_temp;
    }
    //Process ans
    ANS_M[S] = 0;
    ANS_N[S] = 0;
    M[S] = M[S-1]+1;
    N[S] = N[S-1]+1;
    for(long long int i=S-1;i>=0;i--){
      if(M[i] == M[i+1]){
        ANS_M[i] = ANS_M[i+1] + 1;
      }
      else{
        ANS_M[i] = 1;
      }
      if(N[i] == N[i+1]){
        ANS_N[i] = ANS_N[i+1] + 1;
      }
      else{
        ANS_N[i] = 1;
      }
    }
    //After processing, fill the max
    current_max = LLONG_MIN;
    nr_count = 1;
    /*for(int i=0;i<=S;i++){
      cout << ANS_M[i] << " : " << ANS_N[i] << endl;
      cout << M[i] << " : " << N[i] << endl;
    }*/
    long long int ANS_MAX;
    for(long long int i=0;i<S;i++){
      ANS_MAX = max(ANS_M[i] + ANS_N[i+ANS_M[i]], ANS_N[i] + ANS_M[i+ANS_N[i]]);
      if(ANS_MAX>current_max){
        current_max = ANS_MAX;
        nr_count = 1;
      }
      else if(ANS_MAX == current_max){
        nr_count++;
      }
      else{
        //do nothing
      }
    }
    /*for(int i=0;i<S;i++){
      cout << ANS_MAX[i] << " ";
    }*/
    cout << "Case #" << nr_case << ": "<< current_max << " " << nr_count << endl;
    nr_case++;

  }
  return 0;
}
