// Gauss

struct Gauss{
  const double eps = 1e-9;
  vector<vector<double>> eq;
  void addEquation(const vector<double> &e, double sol){
    eq.push_back(e); eq.back().push_back(sol);
  }
  pair<int, vector<double>> solve(){
    int n = (int) eq.size(), m = (int) eq[0].size() - 1;
    vector<int> where(m, -1);
    for(int col=0, row=0; col<m && row<n; col++){
      int sel = row;
      for(int i=row; i<n; i++){
        if(abs(eq[i][col]) > abs(eq[sel][col])) sel = i;
      }
      if(abs(eq[sel][col]) < eps) continue;
      for(int i=col; i<=m; i++) swap(eq[sel][i], eq[row][i]);
      where[col] = row;
      for(int i=0; i<n; i++){
        if(i != row){
          double c = eq[i][col] / eq[row][col];
          for(int j=col; j<=m; j++) eq[i][j] = eq[i][j] - eq[row][j] * c;
        }
      }
      ++row;
    }

    vector<double> ans(m, 0);
    for(int i=0; i<m; i++){
      if(where[i] != -1) ans[i] = eq[where[i]][m] / eq[where[i]][i];
    }
    for(int i=0; i<n; i++){
      double sum = 0;
      for(int j=0; j<m; j++){
        sum = sum + ans[j] * eq[i][j];
      }
      if(abs(sum - eq[i][m]) > eps) return pair(0, vector<double>());
    }
    // int freedom = 0
    for(int i=0; i<m; i++){
      if(where[i] == -1) return pair(INF, ans); // freedom++
    }
    // mod^freedom vai ser a quantidade de solucoes possiveis se o sistema tiver modulado
    return pair(1, ans);
  }
};

// gauss mod 2
// int gauss (vector <bitset<ms>> a, int m, bitset<ms> &ans) {
//     int n = (int) a.size();
//     vector<int> where (m, -1);
//     for (int col=0, row=0; col<m && row<n; ++col) {
//         for (int i=row; i<n; ++i){
//             if (a[i][col]) {
//                 swap (a[i], a[row]);
//                 break;
//             }
//         }
//         if (!a[row][col]) continue;
//         where[col] = row;
//         for (int i=0; i<n; ++i){
//             if (i != row && a[i][col])
//                 a[i] ^= a[row];
//         }
//         ++row;
//     }  
//     for(int i = 0; i < m; ++i)
//         if(where[i] != -1) {
//           ans[i] = a[where[i]][m];
//         }
 
//     for(int i = 0; i < n; ++i) {
//         int sum = 0;
//         for(int j = 0; j < m; ++j) {
//           sum ^= (ans[j] & a[i][j]);
//         }
//         if(sum != a[i][m]) {
//           return 0;
//         }
//     }

//     for(int i = 0; i < m; ++i)
//         if(where[i] == -1)
//           return 1e9;
//     return 1;
// }