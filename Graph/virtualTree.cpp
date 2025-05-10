// Virtual Tree
// constroi arvore comprimida apenas com os vertices presentes 
// no array dado como parametro

// O(nlgn), sendo n o numero de vertices

vector<pair<int,int>> virt[ms]; // par (vertice, distancia)

void build_virt(vector<int> &v){
	auto cmp = [&](int i, int j) { return tin[i] < tin[j]; };
  sort(v.begin(), v.end(), cmp);
  for(int i=0, n = v.size();i+1 <n; i++) v.push_back(lca(v[i], v[i+1]));
  sort(v.begin(), v.end(), cmp);
  v.erase(unique(v.begin(), v.end()), v.end());
  vector<int> st;
  for(auto u : v){
    if(st.empty()){
      st.push_back(u);
    }
    else{
      // inSubtree responde se u ta na subarvore de st.back()
      while(!st.empty() && !inSubtree(st.back(), u)) st.pop_back();
			assert(!st.empty());
			virt[st.back()].emplace_back(u, abs(lvl[u] - lvl[st.back()])); // distancia de u para st.back()
			virt[u].emplace_back(st.back(),abs(lvl[u] - lvl[st.back()]));
			st.push_back(u);
    }
  }
}