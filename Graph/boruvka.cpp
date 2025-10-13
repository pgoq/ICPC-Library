// Boruvka

ll boruvka(int n) {
  vector<int> vis(n, -1), reps;
  vector<vector<int>> comp(n);
  int CNT = 1, n_cmp = n;
  ll ans = 0;
  while (n_cmp > 1) {
    for (int i = 0; i < n; i++) {
      int x = dsfind(i);
      comp[x].push_back(i);
      if (vis[x] != CNT) {
        vis[x] = CNT;
        reps.push_back(x);
      }
    }
    vector<iii> e;
    for (int y : reps) {
      // pega menor aresta saindo da componente y para alguma outra componente x
      // os vertices da componente y tao em comp[y]
      iii cheap = { w, y, x };
      e.push_back(cheap);
    }

    for (auto [w, a, b] : e) {
      if (dsfind(a) != dsfind(b)) {
        ans += w;
        merge(a, b);
        n_cmp--;
      }
    }
    for (int x : reps) comp[x].clear();
    reps.clear();
    CNT++;
  }
  return ans;
}