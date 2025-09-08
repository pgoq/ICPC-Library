// Hash Ull

using ll = long long;
using ull = uint64_t;
struct H {
    ull x; H(ull x = 0) : x(x) {}
    H operator+(H o) { return x + o.x + (x + o.x < x); }
    H operator-(H o) { return *this + ~o.x; }
    H operator*(H o) {
        auto m = (__uint128_t)x * o.x;
        return H((ull)m) + (ull)(m >> 64);
    }
    ull get() const { return x + !~x; }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11 + 3; // (order ~ 3e9; random also ok)
struct Hash {
    vector<H> h, pw;
    Hash(string& str) : h(str.size()), pw(str.size()) {
        pw[0] = 1, h[0] = str[0];
        for (int i = 1; i < str.size(); i++) {
            h[i] = h[i - 1] * C + str[i];
            pw[i] = pw[i - 1] * C;
        }
    }
    H operator()(int l, int r) { // [l, r]
        return h[r] - (l ? h[l - 1] * pw[r - l + 1] : 0);
    }
};
