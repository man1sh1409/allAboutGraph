/*
qns: find the minimum egdes we have to 
reverse so that there is a path between 1 to n

intution:
we have to find path by revesring mimimum edges
so we can think of bfs.
we add reverse edge with penalty of 1 
if level/weight of neighbour is zero 
we push it into front of queue
otherwise push back into queue
we know that in queue at a time two 
level of node reside in it.


*/

#include<bits/stdc++.h>
using namespace std;
const int INF=1e9+7;
const int N=1e5+7;
vector<pair<int,int>>adj[N];
vector<int>level(N,INF);
int n,m;


int bfs(){
   // use deque instead of queue 
   // because we have to front and back
   deque<int>q;
   q.push_back(1);
   level[1]=0;
   while(!q.empty()){
    int curr_v=q.front();q.pop_front();
    for(auto child:adj[curr_v]){
        int child_v=child.first;
        int wt=child.second;
        /*
          suppose we have two node at same level and two have same child but weight are different
                        4   2
                        1\ /0
                          3       
            suppose 4 and two have level 5
            node 3 have level inf at start if node 4 come from deque.(i.e curr_v==4)
            it check 5+1<inf true it push_back into queue;
            and level of 3 is 6;
            deque structre will be 2...3
            now curr_v is 2;
            it check 5+0<6 it push_front in deque
            3..3
            level of 3 is 5;
            this show that every node in queue push two time;
            level will be unique

        */
        if(level[curr_v]+wt<level[child_v]){
            level[child_v]=level[curr_v]+wt;
            if(wt==1){
                q.push_back(child_v);
            }
            else{
                q.push_front(child_v);
            }
        }

    }
  }
  return level[n]==INF ? -1 : level[n];
}



int main(){
    int t;
    cin>>t;
    while(t--){
        
        cin>>n>>m;
        for(int i=0;i<m;i++){
            int x,y;
            cin>>x>>y;
            if(x==y)continue;
            adj[x].push_back({y,0});
            // we are adding reverse egde with penality of 1
            adj[y].push_back({x,1});
        }
        cout<<bfs()<<endl;
    }
}