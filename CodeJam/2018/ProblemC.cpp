#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int w;
int h;

vector<vector<bool> > grid;

int main(){
	int T,A;
	cin >> T;
	while(T--){
		cin >> A;
		if(A==20){
			h = 5;
			w = 4;
		}
		else{
			h = 20;
			w = 10;
		}
		grid.clear();
		grid.resize(h+1, vector<bool>(w+1, false));
		bool done = false;
		bool stop = false;
		while(!done){
			int I,J;
			//Complete internal area first
			 for(int i=2;i<=h-1;i++){
				 for(int j=2;j<=w-1;j++){
					 while(grid[i][j]==false){
						 cout << i << " " << j << endl;
						 cin >> I >> J;
						 if(I == 0 && J == 0){
							 done = true;
							 break;
						 }
						 if(I == -1 && J == -1){
							 done = true;
							 stop = true;
							 break;
						 }
						 grid[I][J] = true;
					 }
					 if(done){
						 break;
					 }
				 }
				 if(done){
					 break;
				 }
			 }
			 if(done){
				 break;
			 }
			 //Complete first and last rows
			 for(int j=2;j<=w-1;j++){
				 while(grid[1][j]==false){
					 cout << 2 << " " << j << endl;
					 cin >> I >> J;
					 if(I == 0 && J == 0){
						 done = true;
						 break;
					 }
					 if(I == -1 && J == -1){
						 done = true;
						 stop = true;
						 break;
					 }
					 grid[I][J] = true;
				 }
				 if(done){
					 break;
				 }
				 while(grid[h][j]==false){
					 cout << h-1 << " " << j << endl;
					 cin >> I >> J;
					 if(I == 0 && J == 0){
						 done = true;
						 break;
					 }
					 if(I == -1 && J == -1){
						 done = true;
						 stop = true;
						 break;
					 }
					 grid[I][J] = true;
				 }
				 if(done){
					 break;
				 }
			 }
			 //Complete first and last columns
			 for(int i = 2;i<=h-1;i++){
				 while(grid[i][1]==false){
					 cout << i << " " << 2 << endl;
					 cin >> I >> J;
					 if(I == 0 && J == 0){
						 done = true;
						 break;
					 }
					 if(I == -1 && J == -1){
						 done = true;
						 stop = true;
						 break;
					 }
					 grid[I][J] = true;
				 }
				 if(done){
					 break;
				 }
				 while(grid[i][w]==false){
					 cout << i << " " << w-1 << endl;
					 cin >> I >> J;
					 if(I == 0 && J == 0){
						 done = true;
						 break;
					 }
					 if(I == -1 && J == -1){
						 done = true;
						 stop = true;
						 break;
					 }
					 grid[I][J] = true;
				 }
				 if(done){
					 break;
				 }
			 }
			 //Compute corners
			 while(grid[1][1] == false){
				 cout << 2 << " " << 2 << endl;
				 cin >> I >> J;
				 if(I == 0 && J == 0){
					 done = true;
					 break;
				 }
				 if(I == -1 && J == -1){
					 done = true;
					 stop = true;
					 break;
				 }
				 grid[I][J] = true;
			 }
			 if(done){
				 break;
			 }
			 while(grid[1][w] == false){
				 cout << 2 << " " << w-1 << endl;
				 cin >> I >> J;
				 if(I == 0 && J == 0){
					 done = true;
					 break;
				 }
				 if(I == -1 && J == -1){
					 done = true;
					 stop = true;
					 break;
				 }
				 grid[I][J] = true;
			 }
			 if(done){
				 break;
			 }
			 while(grid[h][1] == false){
				 cout << h-1 << " " << 2 << endl;
				 cin >> I >> J;
				 if(I == 0 && J == 0){
					 done = true;
					 break;
				 }
				 if(I == -1 && J == -1){
					 done = true;
					 stop = true;
					 break;
				 }
				 grid[I][J] = true;
			 }
			 if(done){
				 break;
			 }
			 while(grid[h][w] == false){
				 cout << h-1 << " " << w-1 << endl;
				 cin >> I >> J;
				 if(I == 0 && J == 0){
					 done = true;
					 break;
				 }
				 if(I == -1 && J == -1){
					 done = true;
					 stop = true;
					 break;
				 }
				 grid[I][J] = true;
			 }
			 if(done){
				 break;
			 }
		}
		if(stop){
			break;
		}
	}
	return 0;
}
