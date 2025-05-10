// FFT
//

typedef complex<double> C;

void fft(vector<C> &a){
  int n = a.size(), L = 31 - __builtin_clz(n);
  static vector<complex<long double>> R(2, 1); // 10% faster if double
  static vector<C> rt(2, 1);
  for(static int k=2; k<n; k*=2){
    R.resize(n);
    rt.resize(n);
    auto x = polar(1.0L, acos(-1.0L)/k);
    for(int i=k; i<2*k; i++){
      rt[i] = R[i] = (i&1 ? R[i/2] * x: R[i/2]);
    }
  }
  vector<ll> rev(n);
  for(int i=0; i<n; i++) rev[i] = (rev[i/2] | (i&1) << L)/2;
  for(int i=0; i<n; i++) if(i < rev[i]) swap(a[i], a[rev[i]]);
 
  for(int k=1; k<n; k*=2){
    for(int i=0; i<n; i+= 2*k){
      for(int j=0; j<k; j++){
       	auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k]; 
	      C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);  
        a[i + j + k] = a[i + j] - z;
        a[i + j] += z;
      }
    }
  }
}
 
vector<ll> conv(const vector<ll> &a, const vector<ll> &b){
  if(a.empty() || b.empty()) return {};
  vector<ll> res(a.size() + b.size() - 1);
  int L = 32 - __builtin_clz((int)res.size()), n = 1 << L;
  vector<C> in(n), out(n);
  copy(a.begin(), a.end(), in.begin());
  for(int i=0; i<b.size(); i++){
    in[i].imag(b[i]);
  }
  fft(in);
  for(C &x : in) x*=x;
  for(int i=0; i<n; i++) out[i] = in[-i & (n-1)] - conj(in[i]);
  fft(out);
  vector<ll> ans(res.size());
  for(int i=0; i<res.size(); i++) ans[i] = round(imag(out[i])/(4*n)) ;
  return ans;
}
