// FWHT
// O(N log N)
// a.size() tem que ser uma potencia de dois

void FST(vector<ll>& a, bool inv) {
	for (int n = (int) a.size(), step = 1; step < n; step *= 2) {
		for (int i = 0; i < n; i += 2 * step) {
			for(int j=i; j <i+step; j++) {
				ll &u = a[j], &v = a[j + step]; 
				// tie(u, v) = inv ? ii(v - u, u) : ii(v, u + v); // AND
				// tie(u, v) = inv ? ii(v, u - v) : ii(u + v, u); // OR 
				// tie(u, v) = ii(u + v, u - v);   // XOR 
			}
		}
	}
	// if(inv){ // XOR only
	// 	for(ll& x : a){
	// 		x /= a.size(); 
	// 	}
	// }
}
vector<ll> conv(vector<ll> a, vector<ll> b) {
	FST(a, 0); 
	FST(b, 0);
	for(int i=0; i<a.size(); i++){
		a[i] = a[i] * b[i];
	} 
	FST(a, 1); 
	return a;
}