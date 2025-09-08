// Hash

const int mod = 1.7e9 + 7, Q = 2; // 1e9 + 9, 1e9 + 7
using H = array<mint, Q>;
const H B = { 709, 5381 }; // random 

H pw[ms];
struct Hash {
    vector<H> h;
    Hash(string& s) : h(s.size()) {
        for (int j = 0; j < Q; j++) h[0][j] = s[0], pw[0][j] = 1;
        for (int i = 1; i < s.size(); i++) for (int j = 0; j < Q; j++) {
            h[i][j] = s[i] + h[i - 1][j] * B[j];
            pw[i][j] = pw[i - 1][j] * B[j];
        }
    }
    H operator()(int l, int r) {
        H ret = h[r];
        for (int j = 0; j < Q && l; j++) {
            ret[j] = ret[j] - h[l - 1][j] * pw[r - l + 1][j];
        }
        return ret;
    }
};
