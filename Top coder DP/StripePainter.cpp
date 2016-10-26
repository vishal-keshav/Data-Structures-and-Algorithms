//https://community.topcoder.com/stat?c=problem_statement&pm=1215&rd=4555
#include <iostream>

using namespace std;

#define INF 1000000000

int minimum(int a, int b){
  return a<b?a:b;
}

//TO-DO: Implement strip function



int recurse(char *stripes, int start, int end, int color){
  //Base case
  if(start>end){
    return 0;
  }
  else if(start==end){
    if(color == stripes[start]-'A'){
      return 0;
    }
    else{
      return 1;
    }
  }
  //Main case
  else{
    int _start,_index,_end;
    //Loop 1: Select partition point
    for(int index = start;index<=end;index++){
      //TO-DO: Not all colors should be tried, only first ones

      //Loop 2: Select a color for first group
      for(int first_color=0;first_color<nr_color;first_color++){
        for(int second_color=0;second_color<nr_color;second_color++){
          strip(start,index,&_start,&_index);
          left = recurse(stripes,_start,_index,first_color);
          strip(index,end,&_index,&_end);
          right = recurse(stripes,_index+1,_end,second_color);
          mini = minimum(mini,(first_color==color?left?left+1) + (second_color==color?right?right+1))
        }
      }
    }
  }
}

int minStrokes(char *stripes, int len){
  int ans = INF, temp;
  for(int i=0;i<nr_color;i++){
    ans = minimum(ans,recurse(stripes,0,len-1,i));
  }
}

int main(){
  char stripes[] = "AABBCCDDCCBBAABBCCDD";
  int len = sizeof(stripes)/sizeof(stripes[0]);
  cout << minStrokes(stripes, len) << endl;
  return 0;
}
