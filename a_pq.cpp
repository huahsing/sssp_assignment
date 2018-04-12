#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;

// We set V, Q, and AdjList to be global variables so that they are directly accessible in all other methods/functions
// But if you want to refactor this template code to avoid any global variable, you can do so
int V; // number of vertices in the graph (number of junctions in Singapore map)
int Q; // number of queries
vector<vector<ii>> AdjList; // the weighted graph (the Singapore map), the length of each edge (road) is stored here too, as the weight of edge

void PreProcess() {
  // Write necessary code to preprocess the graph, if needed
  //
  // write your answer here
  //------------------------------------------------------------------------- 



  //------------------------------------------------------------------------- 
}

int Query(int s, int t, int k) {
  int ans = -1;

  // You have to report the shortest path from Steven and Grace's current position s
  // to reach their chosen hospital t, output -1 if t is not reachable from s
  // with one catch: this path cannot use more than k vertices
  //
  // write your answer here
  
  class lesserDistCompare
  {
  public:
    bool operator() (const ii& lhs, const ii& rhs) const
    {
      return lhs.second < rhs.second;
    }
  };
  
  priority_queue<ii, vector<ii>, lesserDistCompare> dist_pq; // for consistency with ii type in adjacency list, first=vertex, second=dist
  vector<int> dist(AdjList.size(), INT_MAX);
  vector<int> predecessors(AdjList.size(), -2);
  vector<bool> solved(AdjList.size(), false);
  
  dist[s] = 0;
  predecessors[s] = -1;
  dist_pq.emplace(s, dist[s]);
  
  while(!dist_pq.empty())
  {
    auto min_ii = dist_pq.top();
    int solvedVertexNum = min_ii.first;
    
    // remove solved vertex
    dist_pq.pop();
    
    // do the following only if the vertex was not yet solved (due to duplicate insertion)
    if(!solved[solvedVertexNum])
    {
      // mark it as solved
      solved[solvedVertexNum] = true;
      
      // relax adjacent vertices if applicable
      for(int i = 0; i < AdjList[solvedVertexNum].size(); ++i)
      {
        int adjVertex = AdjList[solvedVertexNum][i].first;
        int adjVertexWeight = AdjList[solvedVertexNum][i].second;
          
        // only relax:
        //   1. unsolved vertices
        //   2. vertices still with dist==INT_MAX
        //   3. when new dist is smaller
        if( !solved[adjVertex] &&
            (dist[adjVertex] == INT_MAX || dist[adjVertex] > dist[solvedVertexNum] + adjVertexWeight) )
        {          
          // update new dist
          dist[adjVertex] = dist[solvedVertexNum] + adjVertexWeight;
          // update predecessor
          predecessors[adjVertex] = solvedVertexNum;
          
          // insert vertex (back) into pq
          dist_pq.emplace(adjVertex, dist[adjVertex]);
        }
      }
    }
  }
  
  // if predecessor[t] == -2, dijkstra did not find a path from s to t
  if(predecessors[t] != -2)
  {
    int p = predecessors[t];
    int junctionCnt = 1; // init to 0 if start junction is not counted
    
    while(p != -1)
    {
      p = predecessors[p];
      ++junctionCnt;
    }
    
    if(junctionCnt <= k)
      ans = dist[t];
  }

  //------------------------------------------------------------------------- 

  return ans;
}

// You can add extra function(s) if needed
// --------------------------------------------



// --------------------------------------------

int main() {
  int TC;
  scanf("%d", &TC);

  while (TC--) {
    int j, k, w;
    scanf("%d", &V);
    // clear the graph and read in a new graph as Adjacency List
    AdjList.assign(V, vector<ii>());
    for (int i = 0; i < V; i++) {
      scanf("%d", &k);
      while (k--) {
        scanf("%d %d", &j, &w);
        AdjList[i].emplace_back(j, w); // edge (road) weight (in minutes) is stored here
      }
    }

    PreProcess(); // optional

    int source, destination, required_k;
    scanf("%d", &Q);
    while (Q--) {
      scanf("%d %d %d", &source, &destination, &required_k);
      printf("%d\n", Query(source, destination, required_k));
    }

    if (TC)
      printf("\n");
  }
  return 0;
}