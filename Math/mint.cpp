const int MOD = 7;
struct mint {
    ll x;
    mint(ll xx=0) : x((xx%MOD) + (xx < 0 ? MOD : 0)) {}
    mint operator+(mint b) { return mint(x + b.x); }
    mint operator-(mint b) { return mint(x - b.x); }
    mint operator*(mint b) { return mint(x * b.x); }
    mint operator/(mint b) { return mint(*this * b.inv()); }
    mint inv() { return fexp<mint>(*this, MOD-2); }
};
