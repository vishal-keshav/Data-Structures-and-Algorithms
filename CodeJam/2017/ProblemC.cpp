#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int T,N,M,C,R;
vector<vector<char> > grid(100, vector<char>(100));
vector<int> used_row(100);
vector<int> used_col(100);
vector<int> used_diag1(200);
vector<int> used_diag2(100);
vector<int> used_diag2_negative(100);

void init(void){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			grid[i][j] = '.';
		}
	}
	fill(used_row.begin(), used_row.end(), 0);
	fill(used_col.begin(), used_col.end(), 0);
	fill(used_diag1.begin(), used_diag1.end(), 0);
	fill(used_diag2.begin(), used_diag2.end(), 0);
	fill(used_diag2_negative.begin(), used_diag2_negative.end(), 0);
	return;
}

int main(){
	char sym;
	int ans;
	int elem;
	int nr_case = 1;
	cin >> T;
	while(T--){
		cin >> N >> M;
		ans = 0;
		elem = 0;
		init();
		for(int i=0;i<M;i++){
			cin >> sym >> R >> C;
			R--;
			C--;
			grid[R][C] = sym;
			if(sym == 'x'){
				used_row[R] = 1;
				used_col[C] = 1;
				ans++;
				elem++;
			}
			else{
				used_diag1[R+C] = 1;
				if(R-C>=0){
					used_diag2[R-C] = 1;
				}
				else{
					used_diag2_negative[C-R] = 1;
				}
				ans++;
				elem++;
			}
			
		}
		//processing for x and +
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if(grid[i][j] == '.'){
					int unique_elem = 0;
					if(used_row[i]==0 && used_col[j]==0){
						ans++;
						used_row[i] = 1;
						used_col[i] = 1;
						unique_elem = min(1, unique_elem+1);
					}
					if(used_diag1[i+j]==0){
						if(i-j>=0 && used_diag2[i-j]==0){
							used_diag1[i+j] = 1;
							used_diag2[i-j] = 1;
							ans++;
							unique_elem = min(1, unique_elem+1);
						}
						else if(i-j<0 && used_diag2_negative[j-i]==0){
							used_diag1[i+j] = 1;
							used_diag2_negative[j-i] = 1;
							ans++;
							unique_elem = min(1, unique_elem+1);
						}
						else{
							//do nothing
						}
					}
					elem+=unique_elem;
				}
			}
		}
		cout << "Case #" << nr_case << ": " << ans << elem << endl;
		nr_case++;
	}
	return 0;
}