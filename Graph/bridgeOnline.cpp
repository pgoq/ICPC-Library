// Bridge Online
//

// ds[0][x] indica a componente que x pertence
// ds[1][x] é o nó comprimido que x pertence em sua árvore, o representante é o nó mais alto do conjunto
int bridges = 0;
int ds[2][ms], sz[2][ms];
int h[ms], pai[ms], old[ms];
vector<int> g[ms];

void init(){
  for(int i=0; i<ms; i++){
    g[i].clear();
    h[i] = 0;
    ds[0][i] = ds[1][i] = i;
    sz[0][i] = sz[1][i] = 1;
  }
}

int dsfind(int j, int i){
  return (j == ds[i][j] ? ds[i][j] : ds[i][j] = dsfind(ds[i][j], i));
}

void dfs(int u, int p, int l){
  h[u] = l;
  pai[u] = p;
  old[u] = dsfind(u, 1);
  for(int v : g[u]){
    if(v == p) continue;
    dfs(v, u, l+1);
  }
}

void updateNodes(int u, int p){
  if(old[u] == old[p]){
    ds[1][u] = ds[1][p];
  }
  else ds[1][u] = u;
  for(int v : g[u]){
    if(v == p) continue;
    updateNodes(v, u);
  }
}

void mergeTrees(int a, int b){
  bridges++;
  int iniA = a, iniB = b;
  a = dsfind(a, 0), b = dsfind(b, 0);
  if(sz[0][a] < sz[0][b]) swap(a, b), swap(iniA, iniB);
  dfs(iniB, iniA, h[iniA]+1);
  old[iniA] = -1;
  updateNodes(iniB, iniA);
  ds[0][b] = a;
  sz[0][a] += sz[0][b];
}

void removeBridges(int a, int b){
  a = dsfind(a, 1), b = dsfind(b, 1);
  while(a != b){
    bridges--;
    if(h[a] < h[b]) swap(a, b);
    // ponte entre (a, pai[a]) deixou de existir
    ds[1][a] = dsfind(pai[a], 1);
    a = ds[1][a];
  }
}

void addEdge(int a, int b){
  if(dsfind(a, 0) == dsfind(b, 0)){
    removeBridges(a, b);
  }
  else{
    // nova ponte entre (a, b)
    g[a].push_back(b);
    g[b].push_back(a);
    mergeTrees(a, b);
  }
}