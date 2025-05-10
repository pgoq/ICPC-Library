// Aho Corasick

int trie[ms][sigma], fail[ms], terminal[ms], superfail[ms];
bool present[ms];
int z=1;
 
int val(char c){ return c - 'a';}
 
void add(string &p){
  int cur =0;
  for(int i=0; i<(int)p.size(); i++){
    int &nxt = trie[cur][val(p[i])];
    if(nxt == 0) nxt = z++;
    cur = nxt;
  }
  present[cur] = true;
  terminal[cur]++;
}
 
void build(){
  queue<int> q;
  for(q.push(0); !q.empty(); q.pop()){
    int on = q.front();
    for(int i=0; i<sigma; i++){
      int &to = trie[on][i];
      int f = (on == 0 ? 0 : trie[fail[on]][i]);
      int sf = (present[f] ? f : superfail[f]);
      if(!to){
        to = f;
      }else{
        fail[to] = f;
        superfail[to] = sf;
        // dar merge nas infos (por ex: terminal[v] += terminal[f])
        q.push(to);
      }
    }
  }
}
 
void search(string &s){
  int cur = 0;
  for(char c : s){
    cur = trie[cur][val(c)];
    // processar infos no no atual (por ex: ocorrencias += terminal[node])
  }
}

// se tiver usando super fail, cuidado com o estado que voce ta, antes de subir pro sf, porque pode ser que o estado que ta nao seja no terminal
