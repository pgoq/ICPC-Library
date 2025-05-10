// Bridge Tree
//

using ii = pair<int,int>;
struct BridgeTree{
    int n, timer=0, qtd_cmp=0;
    vector<vector<ii>> g;
    vector<vector<int>> tree;
    vector<int> tin, low, is_bridge, cmp;
  
    BridgeTree(int n, int m, vector<vector<ii>> &g) 
      : n(n), g(g), tree(n), tin(n, -1), low(n), is_bridge(m), cmp(n, -1){
      build();
    }
  
    void build(){
      for(int i=0; i<n; i++){
        if(tin[i] == -1){
          dfs_ini(i, -1);
        }
      }
      for(int i=0; i<n; i++){
        if(cmp[i] == -1){
          dfs_comp(i, qtd_cmp++);
        }
      }
  
      for(int u=0; u<n; u++){
        for(auto [v, _] : g[u]){
          if(cmp[v] != cmp[u]){
            tree[cmp[u]].push_back(cmp[v]);
          }
        }
      }
    }
  
    void dfs_ini(int u, int ep){
      tin[u] = low[u] = timer++;
      for(auto [v, idx] : g[u]){
        if(idx == ep) continue;
        if(tin[v] != -1){
          low[u] = min(low[u], tin[v]);
        }
        else{
          dfs_ini(v, idx);
          low[u] = min(low[u], low[v]);
          if(low[v] > tin[u]){
            is_bridge[idx] = 1;
          }
        }
      }
    }
  
    void dfs_comp(int u, int c){
      cmp[u] = c;
      for(auto [v, idx] : g[u]){
        if(is_bridge[idx] || cmp[v] != -1) continue;
        dfs_comp(v, c);
      }
    }
  };
  