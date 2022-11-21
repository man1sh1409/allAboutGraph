#include<bits/stdc++.h>
using namespace std;
const int INF=1e9+7;
const int  N=1e3+7;
vector<pair<int,int> >graph[N];
vector<vector<int>>dis(N,vector<int>(N,INF));
int n,m;

void floydWarshal(){
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i==j)dis[i][j]=0;
                else{
                    int newdis=dis[i][k]+dis[k][j];
                    dis[i][j]=min(dis[i][j],newdis);
                }
            }
        }
    }
}


int main(){
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int x,y,w;
        cin>>x>>y>>w;
        // node-> wt
        dis[x][y]=w;
        graph[x].push_back({y,w});
    }
    floydWarshal();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(dis[i][j]==INF){
                cout<<-1<<" ";
            }
            else{
                cout<<dis[i][j]<<" ";
            }
        }cout<<endl;
    	  
    }
}
