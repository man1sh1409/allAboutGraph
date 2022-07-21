/*qns: given chess board knight can move in minimum 
number of jump to reach at end from start 
i.e a1->h8
input:
test case
source destination
2
a1 h8 
a1 c2
h8 c3

output:
6
1
4
*/
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7; 
const int INF=1e9+7;
// vector<int>board[N];
int level[8][8];
int visited[8][8];

pair<int,int> getCordinate(string s){
    int x=s[0]-'a';
    int y=s[1]-'1';
    pair<int,int> cordinate={x,y};
    return cordinate;
}
bool isValid(int x,int y){
    return x>=0 && y>=0 && x<8 && y<8;
}

vector<pair<int,int>> movements={
    {2,1},{-2,1},{1,2},{-1,2},
    {2,-1},{-2,-1},{1,-2},{-1,-2}
};

int bfs(string source,string dest){
    pair<int,int>sourceCord=getCordinate(source);
    pair<int,int>destCord=getCordinate(dest);
    queue<pair<int,int>>q;
    q.push(sourceCord);
    visited[sourceCord.first][sourceCord.second]=1;
    level[sourceCord.first][sourceCord.second]=0;
    while(!q.empty()){
        pair<int,int>node=q.front();q.pop();
        int x=node.first;
        int y=node.second;
        for(auto movement:movements){
            int childX=movement.first+x;
            int childY=movement.second+y;
            if(!isValid(childX,childY))continue;
            if(!visited[childX][childY]){
                q.push({childX,childY});
                visited[childX][childY]=1;
                level[childX][childY]=level[x][y]+1;
            }

        }
        if(level[destCord.first][destCord.second]!=INF){
            break;
        }
    }
    return level[destCord.first][destCord.second];
}

void reset(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            visited[i][j]=0;
            level[i][j]=INF;
        }
    }
}

int main(){
    int t;
    cin>>t;
    while(t--){
        reset();
        string s1,s2;
        cin>>s1>>s2;
        cout<<bfs(s1,s2)<<endl;
    }
}