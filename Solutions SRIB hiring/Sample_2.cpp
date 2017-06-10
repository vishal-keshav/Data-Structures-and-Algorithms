#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

#define max_mod 1000000007

using namespace std;

long int N, Q;
long int max_N;

vector<long int> arr;

long int calc_fibo(long int input){
    long int var_a = 1;
    long int var_b = 1;
    long int temp_var;
    long int running_index = 2;
    while(input>running_index){
        temp_var = (var_a + var_b)%max_mod;
        var_a = var_b;
        var_b = temp_var;
        running_index++;
    }
    return (var_b);
}


long int calc_gcd(long int a, long int b){
    if(b){
        return calc_gcd(b, a%b);
    }
    else{
        return a;
    }
}

long int compute_gcd(long int L, long int R){
    if(L==R){
        return arr[L];
    }
    else{
        long int mid = L + (R-L)/2;
        long int left = compute_gcd(L,mid);
        long int right = compute_gcd(mid+1,R);
        if(left>right){
            return calc_gcd(left,right);
        }
        else{
            return calc_gcd(right,left);
        }
    }
}

int main()
{
    long int L,R;
    cin >> N >> Q;
    max_N = 0;
    arr.resize(N);
    for(long int i=0;i<N;i++){
        cin >> arr[i];
        if(max_N<arr[i]){
            max_N = arr[i];
        }
    }
    for(long int i=0;i<Q;i++){
        cin >> L >> R;
        cout << calc_fibo(compute_gcd(L-1,R-1)) << endl;
    }
    return 0;
}
