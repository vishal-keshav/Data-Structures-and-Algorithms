#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

struct cell{
    int x, y;
};

int N,M;
vector<vector<int> > grid;
vector<int> primality;
vector<vector<int> > DP;
int main()
{
    cin >> N >> M;
    int max_number = 0;
    grid.resize(N,vector<int>(M,0));
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin >> grid[i][j];
            if(max_number < grid[i][j]){
                max_number = grid[i][j];
            }
        }
    }
    //Primality
    primality.resize(max_number+1,0);
    for(int i=2;i<=max_number;i++){
        if(primality[i]){
            continue;
        }
        else{
            for(int j=2;i*j<=max_number;j++){
                primality[i*j] = 1;
            }
        }
    }
    //Transform grid to obstacle grid
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(primality[grid[i][j]]){
                grid[i][j] = 0;
            }
            else{
                grid[i][j] = 1;
            }
        }
    }
    /*for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }*/
    DP.resize(N,vector<int>(M,0));
    DP[0][0] = 1;
    for(int i=1;i<M;i++){
        if(grid[0][i]){
            DP[0][i] = 1;
        }
        else{
            break;
        }
    }
    for(int i=1;i<N;i++){
        if(grid[i][0]){
            DP[i][0] = 1;
        }
        else{
            break;
        }
    }
    //Fill whole DP
    for(int i=1;i<N;i++){
        for(int j=1;j<M;j++){
            if(grid[i][j]){
                DP[i][j] = DP[i-1][j] + DP[i][j-1] + DP[i-1][j-1];
            }
        }
    }
    cout << DP[N-1][M-1] << endl;
    stack<struct cell> my_stack;
    //Trace the back path
    int start_x = N-1;
    int start_y = M-1;
    struct cell elem;
    while(start_x+start_y>=0){
        elem.x = start_x;
        elem.y = start_y;
        my_stack.push(elem);
        //Now we have three choices
        if(start_x > 0 && start_y > 0 && DP[start_x-1][start_y-1]){
            start_x--;
            start_y--;
        }
        else if(start_x > 0 && DP[start_x-1][start_y]){
            start_x--;
        }
        else{
            start_y--;
        }
    }

    while(!my_stack.empty()){
        elem = my_stack.top();
        cout << elem.y+1 << " " << elem.x+1 << endl;
        my_stack.pop();
    }

    return 0;
}
