#include<bits/stdc++.h>
using namespace std;
const int N=1e3+7;
int parent[N];
int Size[N];
void make(int v){
    parent[v]=v;
    Size[v]=1;
}

int find(int v){
    if(v==parent[v])return v;

    return parent[v]=find(parent[v]);
}

void Union(int a,int b){
    a=find(a);
    b=find(b);
    if(a!=b){
        if(Size[a]<Size[b])
         swap(a,b);
        parent[b]=a;
        Size[a]+=Size[b];
    }
}


int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        make(i);
    }
    vector<pair<int,pair<int,int>>>edges;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        edges.push_back({w,{u,v}});
    }
    sort(edges.begin(),edges.end());
    int cost=0;
    for(auto &edge:edges){
        int u=edge.second.first;
        int v=edge.second.second;
        int wt=edge.first;
        if(find(u)!=find(v)){
            Union(u,v);
            cout<<u<<" "<<v<<" "<<wt<<endl;
            cost+=wt;
        }
    }
    cout<<cost<<endl;
}


