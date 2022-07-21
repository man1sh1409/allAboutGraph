/*
qns:grid of n*m.every one hour the max of adjacent is taken .
you have to return maximum hour to fill all in grid;
input: 
testcase
n m
grid
3
2 2
1 1
1 1
2 2
1 1
1 2
3 4
1 2 1 2 // see in first hour 2 flood 
1 1 1 2  // new grid will be
1 1 2 2 //  2 2 2 2
        //  2 2 2 2
output: //  1 2 2 2 
0
1
2

// intution:
find maximum in grid and make all maximum value as source node 
push it into queue.intialise level with zero.
//in its child level increse by 1 of its parent i.e parent's level+1
make ans =0;
take max of all level


*/

#include<bits/stdc++.h>
using namespace std;
const int INF=1e9+7;
const int N=1e3+7;
int val[N][N];
int lev[N][N];
int vis[N][N];
int n,m;

vector<pair<int,int>>movements={
    {0,1},{0,-1},
    {1,0},{-1,0},
    {1,1},{-1,-1},
    {-1,1},{1,-1}
};
bool isValid(int i,int j){
    return i>=0 && j>=0 && i<n && j<m;
}


int bfs(){
    int mx=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            mx=max(mx,val[i][j]);
        }
    }
    queue<pair<int,int>>q;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(val[i][j]==mx){
                q.push({i,j});
                vis[i][j]=1;
                lev[i][j]=0;
            }
        }
    }
    int ans=0;
    while(!q.empty()){
        pair<int,int> curr_n=q.front();q.pop();
        int x=curr_n.first;
        int y=curr_n.second;
        for(auto movement:movements){
            int child_x=movement.first+x;
            int child_y=movement.second+y;
            if(!isValid(child_x,child_y))continue;
            if(vis[child_x][child_y])continue;
            vis[child_x][child_y]=1;
            q.push({child_x,child_y});
            lev[child_x][child_y]=lev[x][y]+1;
            ans=max(ans,lev[child_x][child_y]);
        }
    }
    return ans;
}
void reset(){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            vis[i][j]=0;
            lev[i][j]=INF;
        }
    }
}


int main(){
    int t;
    cin>>t;
    while(t--){
        reset();
        cin>>n>>m;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cin>>val[i][j];
            }
        }
        cout<<bfs()<<endl;
    }
}