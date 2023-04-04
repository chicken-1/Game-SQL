#include <iostream>
#include <vector>

using namespace std;

vector<int> adj[10000];
int edge, vertex;
vector<int> path;
int in[1000], out[1000];
 
bool graphHasEulerianPath() {
    if (edge == 0) return false;
    int startNodes = 0, endNodes = 0;
    for (int i = 0; i < vertex; i++) {
        if (out[i] - in[i] > 1 || in[i] - out[i] > 1) return false;
        else if (out[i] - in[i] == 1) startNodes++;
        else if (in[i] - out[i] == 1) endNodes++;
    }
    if(endNodes == 0 && startNodes == 0 || endNodes == 1 && startNodes == 1)
        return true;
    else return false;
}
int findStartNode() {
    int start = 0;
    for (int i = 0; i < vertex; i++) {
      // Unique starting node.
      if (out[i] - in[i] == 1) return i;
      // Start at a node with an outgoing edge.
      if (out[i] > 0) start = i;
    }
    return start;
  }
void setup(){
    for(int i=0;i<vertex;i++){
        in[i] = 0;
        out[i] = 0;
    }
    // Compute in and out node degrees.
    for (int i=0;i<vertex;i++) {
      for (int j : adj[i]) {
        out[i]++;
        in[j]++;
        
      }
    }
}
void dfs(int at){
    while(out[at] != 0){
        int next = adj[at][out[at]-1];
        --out[at];
        // recheck 2 lines above(can reverse position)
        dfs(next);
    }
    path.push_back(at);
}
int* getEulerianPath(){
    
    if(edge == 0) return NULL;
    if(!graphHasEulerianPath()) return NULL;
    dfs(findStartNode());
    // Make sure all edges of the graph were traversed. It could be the
    // case that the graph is disconnected in which case return null.
    if(path.size() != edge + 1) return NULL;
    int *sol = new int[edge+1];
    for(int i = 0;i <= edge ;i++){
        sol[i] = path[i];
    }
    return sol;
}
int main()
{
    cin >> vertex >> edge;
    for(int i=0;i<edge;i++){
       int x,y;
       cin >> x >> y;
       adj[x].push_back(y);
    }
    
    setup();
   
    int *sol = new int[edge+1]; 
    sol = getEulerianPath();
    if(sol == NULL) cout << "Graph don't have an Eulerian path.";
    else {
        cout << "Eulerian path: ";
        for(int i = edge;i >= 0 ;i--){
            cout << sol[i] << ' ';
        }
    }
}
