// Sack

void dfs(int u, int p = -1, bool keep = 0) {
  int big = -1;
  for(int v : g[u]){
    if(v == p) continue;
    if(big == -1 || sz[v] > sz[big]){
        big = v;
    }
  }
  for(int v : g[u]){
    if(v == p || v == big) continue;
    dfs(v, u, 0);
  }
  if(big != -1){
    dfs(big, u, 1);
  }
  add(u);
  for(int v : g[u]){
    if(v == p || v == big) continue;
    put(v, u); 
  }
  ans[u] = ;
  if(!keep){ // limpa
        
  }
}