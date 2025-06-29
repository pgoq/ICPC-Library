// NTT

const int mod = 998244353, root = 62;
void ntt(vector<int> &a) {
	int n = a.size(), L = 31 - __builtin_clz(n);
	static vector<int> rt(2, 1);
	for(static int k = 2, s = 2; k < n; k *= 2, s++){
		rt.resize(n);
		ll z[] = {1, fexp(root, mod >> s)};
		for(int i = k; i < (2*k); i++) rt[i] = (1ll * rt[i / 2] * z[i & 1]) % mod;
	}
	vector<int> rev(n);
	for(int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	for(int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for(int k = 1; k < n; k *= 2){
		for(int i = 0; i < n; i += 2 * k){
            for(int j = 0; j < k; j++){
			  ll z = (1ll * rt[j + k] * a[i + j + k]) % mod; int &ai = a[i + j];
			  a[i + j + k] = ai - z + (z > ai ? mod : 0);
			  ai += (ai + z >= mod ? z - mod : z);
		    }
        }
    }
}
vector<int> conv(const vector<int> &a, const vector<int> &b) {
	if (a.empty() || b.empty()) return {};
	int s = a.size() + b.size() - 1, B = 32 - __builtin_clz(s), n = 1 << B;
	int inv = fexp(n, mod - 2);
	vector<int> L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	for(int i = 0; i < n; i++) out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
	ntt(out);
	return {out.begin(), out.begin() + s};
}
