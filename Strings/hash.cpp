// Hash

const int mod = 1.7e9 + 7, Q = 2; // 1e9 + 9, 1e9 + 7
using ll = long long;
using H = array<ll, Q>;
const H B = {709, 5381}; // 174440041, 9737333
struct Hash{
  vector<H> h, p;
  Hash(string &s) : h(s.size()), p(s.size()){
    for(int j=0; j<Q; j++) h[0][j] = s[0], p[0][j] = 1;
    for(int i=1; i<s.size(); i++){
      for(int j=0; j<Q; j++){
        h[i][j] = (s[i] + h[i-1][j]*B[j])%mod;
        p[i][j] = (p[i-1][j] * B[j])%mod;
      }
    }
  }
  H operator()(int l, int r){
    H ret = h[r];
    for(int j=0; j<Q && l; j++){
      ret[j] = (mod + ret[j] - h[l-1][j]*p[r-l+1][j]%mod)%mod;
    }
    return ret;
  }
};