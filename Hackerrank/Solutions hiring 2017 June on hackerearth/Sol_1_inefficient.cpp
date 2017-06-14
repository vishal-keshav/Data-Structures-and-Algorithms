#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

#define max_mod 1000000007

using namespace std;

int N, Q;

struct my_input{
    long int A;
    long int index;
};

bool sort_fn(struct my_input elem1, struct my_input elem2){
    if(elem1.A < elem2.A){
        return true;
    }
    else{
        return false;
    }
}

vector<struct my_input> arr;
vector<long int> fibo;

void pre_compute_fibo(void){
    //Calculate fibo in increasing order with memoization
    long int var_a = 1;
    long int var_b = 1;
    long int temp_var;
    long int running_index = 2;
    for(long int i=0;i<N;i++){
        while(arr[i].A>running_index){
            temp_var = (var_a%max_mod + var_b%max_mod)%max_mod;
            var_a = var_b;
            var_b = temp_var;
            running_index++;
        }
        fibo[arr[i].index] = var_b;
    }
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
        return fibo[L];
    }
    else{
        long int gcd_temp = fibo[L];
        for(long int i=L+1;i<=R;i++){
            if(gcd_temp > fibo[i]){
                gcd_temp = calc_gcd(gcd_temp,fibo[i]);
            }
            else{
                gcd_temp = calc_gcd(fibo[i],gcd_temp);
            }
        }
        return gcd_temp;
    }
}

int main()
{
    long int L,R;
    cin >> N >> Q;
    arr.resize(N);
    for(long int i=0;i<N;i++){
        cin >> arr[i].A;
        arr[i].index = i;
    }

    sort(arr.begin(),arr.end(),sort_fn);

    fibo.resize(N,-1);
    pre_compute_fibo();

    for(long int i=0;i<Q;i++){
        cin >> L >> R;
        cout << compute_gcd(L-1,R-1) << endl;
    }
    return 0;
}
