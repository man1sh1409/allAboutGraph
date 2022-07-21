/*
input:
6 9
1 2 1
1 3 5
2 4 2
2 3 2
2 5 1
3 5 2
4 5 3 
4 6 1
5 6 2
output:
4

intution:
dijsktra works on greedy approach .it works for multiple dest 
make source node dis=0;
intialise distance all other node with infinity
use visited array

use set/priority_queue to find minimum distance of all child node
algo says if you make distance smaller than curr distance then do it and push it into set/pq
take out the minimum distance node;

do while set/pq not empty
if(vis[curr_v])continue
vis[curr_v]=1;
go to all its child of curr_v
those node whose distance become smaller than curr goes into set/pq
so inside comparing distance not mark visited as true;

*/

#include<bits/stdc++.h>
using namespace std;
const int INF=1e9+7;
const int  N=1e3+7;
vector<pair<int,int> >graph[N];
vector<int>dis(N,INF);
int n,m;

void dijkstra(int source){
    vector<int>vis(N,0);
    set<pair<int,int>>st;//wt->node
    st.insert({0,source});
    dis[source]=0;
    while(!st.empty()){
        auto curr_n=*st.begin();
        st.erase(st.begin());
        int v=curr_n.second;
       
        if(vis[v])continue;
        vis[v]=1;
        for(auto child:graph[v]){
            int child_wt=child.second;
            int child_v=child.first;
            if(dis[v]+child_wt < dis[child_v]){
                dis[child_v]= dis[v]+ child_wt;
                st.insert({dis[child_v],child_v});
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
        graph[x].push_back({y,w});
    }
    dijkstra(1);
    for(int i=1;i<=n;i++){
    	cout<<dis[i]<<" ";
    }
}