// SCC
//
// componentes ja sao ordenados em ordem topologica
// !A = ~A
// A -> B == !A v B

struct SCC{
	int n, ncomp;
	vector<vector<int>> g, inv; // troca p basic_string se precisar otimizar
	vector<int> comp, vis, stk, value;
	SCC(int n) : n(n), ncomp(0), g(2*n), inv(2*n), comp(2*n, -1), vis(2*n), value(n){}
	
	void dfs(int u){
		vis[u] = 1;
		for(int v : g[u]){
			if(!vis[v]) dfs(v);
		}
		stk.push_back(u);
	}

	void dfs_inv(int u){
		comp[u] = ncomp;
		for(int v : inv[u]){
			if(comp[v] == -1) dfs_inv(v);
		}
	}

	bool solve(){
		for(int i=0; i<2*n; i++){
			if(!vis[i]) dfs(i);
		}
		reverse(stk.begin(), stk.end());
		for(int u : stk){
			if(comp[u] != -1) continue;
			dfs_inv(u);
			ncomp++; 
		}
		for(int i=0; i<2*n; i++){
			if(comp[i] == comp[i^1]) return false;
		}
		for(int i=0; i<n; i++){
			value[i] = comp[trad(i)] > comp[trad(~i)]; 
		}
		return true;
	}

	void add_edge(int a, int b){
		g[a].push_back(b);
		inv[b].push_back(a);
	}

	int trad(int v) { return v < 0 ?(~v)*2^1 : v * 2; }
	void add(int a, int b) { add_edge(trad(a), trad(b)); }
	void addOr(int a, int b) { add(~a, b); add(~b, a); }
	void addImp(int a, int b) { addOr(~a, b); }
	void addEqual(int a, int b) { addOr(a, ~b); addOr(~a, b); }
	void addDiff(int a, int b) { addEqual(a, ~b); }
	void isFalse(int a) { addImp(a, ~a); }
	void isTrue(int a) { isFalse(~a); }
};