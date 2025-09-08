// Xor Gauss

template<const int N> struct XorGauss {
    bitset<N> basis[N], mask[N]; // mask[i] tem quais vetores contribuiram para a formacao do vetor i
    XorGauss() {}
    bool small(bitset<N> a, bitset<N> b) { // retorna true se a < b
        for (int i = N - 1; i >= 0; i--) {
            if (a[i] != b[i]) return (a[i] == 0);
        }
        return false;
    }
    pair<bool, bitset<N>> belong(bitset<N> x) { // retorna true se x pertence ao set e quais vetores formam x
        bitset<N> ans;
        for (int i = N - 1; i >= 0; i--) {
            if (small(basis[i] ^ x, x)) {
                x ^= basis[i];
                ans ^= mask[i];
            }
        }
        return pair(x.count() == 0, ans);
    }
    void add(bitset<N> v, int idx) {
        bitset<N> cur_mask;
        cur_mask[idx] = 1;
        for (int i = N - 1; i >= 0; i--) {
            if (v[i] == 0) continue;
            if (basis[i][i] == 0) {
                basis[i] = v;
                mask[i] = cur_mask;
                break;
            }
            cur_mask ^= mask[i];
            v ^= basis[i];
        }
    }
};
