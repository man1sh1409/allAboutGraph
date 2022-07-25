/*written by manish malhotra
all function are genric,to make specific remove T wherever are present
for int type of graph you can use vector<bool>vis(V,false) instead of unordered_map
for local creation of adjacency list ,of int type of node is very simple

  //make array of vector<int>;
  vector<int>adj[V];
  //m is numbers of edges
  for(int i=0;i<m;i++){
      int u,int v;
      u=edges[i][0];
      v=edges[i][1];
      if directed then 
      adj[u].push_back(v);
      else
      adj[u].push_back(v);
      adj[v].push_back(u);
  }

*/
#include<bits/stdc++.h>
using namespace std;
template <class T>
class Graph{
     private:
     unordered_map<T,list<pair<T,int> > >adj;
	 void topologicalSortUtil(T node,unordered_map<T,bool>&vis,vector<T>&ans);
	 unordered_map<T,int> getIndegree(int v);
    public:
    void addEdge(T u,T v,bool dirn=false,int wt=0){
         if(!dirn){
            adj[u].push_back({v,wt});
            adj[v].push_back({u,wt});
         }
         else{
            adj[u].push_back({v,wt});
         }
    }
    void printGraph();
    void dfsTraversal(T node,unordered_map<T,bool>&vis);	
    void bfsTraversal(T node,unordered_map<T,bool>&vis);
    bool cycleIndirectedGraphUsingDfs(T node,unordered_map<T,bool>&vis,unordered_map<T,bool>&dfsVis);
    bool cycleInUndirectedGraphUsingDfs(T node,unordered_map<T,bool>&vis,T parent);
    vector<T> topologicalSort(int v);
    vector<T> topologicalSortUsingBfs(int v);
    vector<T> shortestPathUsingBfs(T src,T dest);
	
};

template <class T> void  Graph<T>::topologicalSortUtil(T node,unordered_map<T,bool>&vis,vector<T>&ans){
	vis[node]=true;
	for(auto neighbour:adj[node]){
		if(!vis[neighbour.first]){
			topologicalSortUtil(neighbour.first,vis,ans);
		}
	}
	ans.push_back(node);
}

template <class T> void Graph<T>::bfsTraversal(T node,unordered_map<T,bool>&vis){
	queue<T>q;
	q.push(node);
	vis[node]=true;
	while(!q.empty()){
		T temp=q.front();q.pop();
		cout<<temp<<" ";
		for(auto neighbour:adj[temp]){
			if(!vis[neighbour.first]){
				q.push(neighbour.first);
				vis[neighbour.first]=true;
			}
		}
	}
}

template <class T> void Graph<T>:: dfsTraversal(T node,unordered_map<T,bool>&vis/*vector<T>&ans want to store answer uncomment it*/){
	vis[node]=true;
	// store node in ans
	//ans.push_back(node);
	cout<<node<<" ";
	for(auto neighbour:adj[node]){
		//return pair node ,weight
		if(!vis[neighbour.first]){
			dfsTraversal(neighbour.first,vis);
		}
	}
}

template <class T> bool Graph<T>::cycleIndirectedGraphUsingDfs(T node,unordered_map<T,bool>&vis,unordered_map<T,bool>&dfsVis){
          vis[node]=true;
		  dfsVis[node]=true;
		  for(auto neighbour:adj[node]){
			  if(!vis[neighbour.first]){
				  bool check=cycleIndirectedGraphUsingDfs(neighbour.first,vis,dfsVis);
				  if(check) return true;
			  }
			  else if(dfsVis[neighbour.first]){
				  return true;
			  }
		  }	
		  dfsVis[node]=false;
		  return false;
}

template <class T> bool Graph<T>::cycleInUndirectedGraphUsingDfs(T node,unordered_map<T,bool>&vis,T parent){
          vis[node]=true;
		  for(auto neighbour:adj[node]){
			  if(!vis[neighbour.first]){
				  bool check=cycleInUndirectedGraphUsingDfs(neighbour.first,vis,node);
				  if(check) return true;
			  }
			  else if(parent!=neighbour.first){
				  return true;
			  }
		  }	
		  return false;
}

template <class T> unordered_map<T,int> Graph<T>:: getIndegree(int v){
	  //int n=adj.size();
	  unordered_map<T,int>ans;
	  for(int i=0;i<v;i++){
		  ans[i]=0;
	  }
	  for(auto i:adj){
		  for(auto j:i.second){
			  ans[j.first]+=1;
		  }
	  }
	  return ans;
}

template <class T>  vector<T> Graph<T>::topologicalSort(int v){
	vector<T>ans;
	unordered_map<T,bool>vis;
	for(int i=0;i<v;i++){
		if(!vis[i]){
			topologicalSortUtil(i,vis,ans);
		}
	}
	reverse(ans.begin(),ans.end());
	return ans;
}

template <class T> vector<T> Graph<T>::topologicalSortUsingBfs(int v){
	unordered_map<T,int>indegree=getIndegree(v);
	// for(auto pb:indegree)cout<<pb.first<<" " <<pb.second<<" \n";
	queue<T>q;
	for(auto i:indegree){
		if(i.second==0){
			q.push(i.first);
		}
	}
	vector<T>ans;
	while(!q.empty()){
		int node=q.front();q.pop();
		ans.push_back(node);
		for(auto neighbour:adj[node]){
			indegree[neighbour.first]--;
			if(indegree[neighbour.first]==0)
			q.push(neighbour.first);
		}
	}
	return ans;
}

template <class T> vector<T> Graph<T>:: shortestPathUsingBfs(T src,T dest){
	unordered_map<T,bool>vis;
	queue<T>q;
	vector<T> ans;
	unordered_map<T,T>parent;
	q.push(src);
	vis[src]=true;
	while(!q.empty()){
		int node=q.front();q.pop();
		for(auto neighbour:adj[node]){
			if(!vis[neighbour.first]){
				parent[neighbour.first]=node;
				q.push(neighbour.first);
				vis[neighbour.first]=true;
			}
		}
	}
	T temp=parent[dest];
	while(temp!=src){
		ans.push_back(temp);
		temp=parent[temp];
	}
	reverse(ans.begin(),ans.end());
	return ans;
}

template <class T> void Graph<T>:: printGraph(){
	for(auto i:adj){
			cout<<i.first<<"-> ";
			for(auto j:i.second){
				if(j.second!=0)
				 cout<<"("<<j.first<<" ,"<<j.second<<")";
				else{
					cout<<j.first<<" ";
				}
			}cout<<endl;
    }
}


int main(){
    //Graph<string> g;
    // g.addEdge("patna","kolk");
	Graph<int> g;
	int n=5;//number of nodes starts with zero
	//undirected graph
    // addEdge() take four argument u,v,dirn,weight but dirn and weight are optional
	g.addEdge(0,1);
	g.addEdge(0,2);
	//g.addEdge(0,3); 
	g.addEdge(1,3);
	g.addEdge(2,3);
	g.addEdge(3,4);
	//directed graph
	// g.addEdge(0,1,1);
	// g.addEdge(1,3,1);
	// g.addEdge(2,0,1);
	// g.addEdge(2,3,1);
	// g.addEdge(3,4,1);
	//print graph
    //g.printGraph();
	unordered_map<int,bool> vis;
	//dfsVis used in to check cycle in directed graph using dfs 
	unordered_map<int,bool> dfsVis;
	// for all component in graph
	for(int i=0;i<n;i++){
		if(!vis[i]){
			// dfs call
			//g.dfsTraversal(i,vis);
			// bfs call
			//g.bfsTraversal(i,vis);
		}
	}
	//cout<<g.cycleIndirectedGraphUsingDfs(0,vis,dfsVis)<<endl;
	//cout<<g.cycleInUndirectedGraphUsingDfs(0,vis,-1)<<endl;
	// topo sort using dfs
	 vector<int>ans;
	 //ans=g.topologicalSort(n);
	 //ans=g.topologicalSortUsingBfs(n);
	 //check cycle using topologicalSortUsingBfs is  if ans!=n cycle present
	 // shortest path 
	 ans=g.shortestPathUsingBfs(0,4);
	for(auto i:ans)cout<<i<<" ";
    return 0;
}
