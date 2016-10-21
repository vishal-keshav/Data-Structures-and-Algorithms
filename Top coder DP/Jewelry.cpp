#include <iostream>
using namespace std;

void sort_values(int *values, int len){
  int temp;
  for(int i=len-2;i>=0;i--){
    for(int j=0;j<=i;j++){
      if(values[j]>values[j+1]){
        temp = values[j];
        values[j] = values[j+1];
        values[j+1] = temp;
      }
    }
  }
  //Debug
  for(int i=0;i<len;i++){
    cout << values[i] << " ";
  }
  cout << endl;
  //Debug
}

void fill_duplicates(int *d_p, int *d_v, int *values, int len){
  int index=1,counter=1;
  while(index<=len){
    if(index<len && values[index]==values[index-1]){
      index++;
      counter++;
    }
    else{
      for(int i=1;i<=counter;i++){
        d_p[index-i] = counter-i+1;
        d_v[index-i] = counter;
      }
      index++;
      counter=1;
    }
  }
  //Debug
  for(int i=0;i<len;i++){
    cout << d_p[i] << ":" << d_v[i] << " ";
  }
  cout << endl;
  //Debug
}

int sum(int *values, int len){
  int ret_sum = 0;
  for(int i=0;i<len;i++){
    ret_sum+=values[i];
  }
  //Debug
  cout << ret_sum << endl;
  //Debug
  return ret_sum;
}

void fill_bob(int **arr, int len, int max_sum, int start_index, int end_index, int *values){
  for(int i=start_index;i<=end_index;i++){
    for(int s=max_sum;s>=values[i];s--){
      arr[end_index][s]+=arr[end_index][s-values[i]];
      /*if(arr[end_index][s] > 0){
        cout << "Positive found" << endl;
      }*/
    }
  }
}

void fill_frank(int **arr, int len, int max_sum, int start_index, int end_index, int *values){
  for(int i=start_index;i<=end_index;i++){
    for(int s=max_sum;s>=values[i];s--){
      arr[start_index][s]+=arr[start_index][s-values[i]];
      /*if(arr[start_index][s] > 0){
        cout << "Positive" << endl;
      }*/
    }
  }
}

//TO-DO: Memoize
long long int choose(int b, int a){
  if(b==a){
    return 1;
  }
  else if(a==1){
    return b;
  }
  else{
    return choose(b-1,a)+choose(b-1,a-1);
  }
}

long long int howMany(int *values,int len){

  sort_values(values,len);
  cout << "Sorting done" << endl;

  int *d_p = new int[len];
  int *d_v = new int[len];
  fill_duplicates(d_p,d_v,values,len);
  cout << "Duplicates generated" << endl;

  int max_sum = sum(values,len);
  cout << "Summation done" << endl;

  int **B = new int*[len];
  int **F = new int*[len];
  for(int i=0;i<len;i++){
    B[i] = new int[max_sum+1];
    F[i] = new int[max_sum+1];
    B[i][0] = F[i][0] = 1;
    for(int j=1;j<=max_sum;j++){
      B[i][j] = 0;
      F[i][j] = 0;
    }
  }
  for(int i=0;i<len;i++){
    fill_bob(B,len,max_sum,0,i,values);
    fill_frank(F,len,max_sum,i,len-1,values);
  }
  //Debug
  /*for(int i=0;i<=max_sum;i++){
    cout << B[len-1][i] << " ";
  }
  cout << endl;
  for(int i=0;i<=max_sum;i++){
    cout << F[1][i] << " ";
  }
  cout << endl;*/
  //Debug
  cout << "Memoization complete" << endl;

  long long int ret = 0;
  for(int i=0;i<len-1;i++){
    for(int s=values[i];s<=max_sum;s++){
      if(i-d_p[i] < 0){
        ret+=0;
      }
      else{
        ret+=B[i-d_p[i]][s-values[i]]*F[i+1][s]*choose(d_v[i],d_p[i]);
        //ret+=B[i-d_p[i]][s-values[i]]*F[i+1][s];
      }
      /*if(ret>0){
        cout << ret << endl;
      }*/
    }
  }
  return ret;
}

int main(){
  int values[] = {7,7,8,9,10,11,1,2,2,3,4,5,6};
  int len = sizeof(values)/sizeof(values[0]);
  cout << howMany(values,len) << endl;
  return 0;
}
