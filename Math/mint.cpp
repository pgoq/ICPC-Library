// Mint

template<const uint32_t MOD>
struct Mod {
  uint32_t x;
  template<typename T>
  Mod(T x=0) : x(uint32_t(((int64_t(x) % MOD) + MOD) % MOD)) {}
  Mod& operator+=(Mod rhs) {
    x += rhs.x;
    if(x >= MOD) x -= MOD;
    return *this;
  }
  Mod& operator-=(Mod rhs) {
    x += MOD - rhs.x;
    if(x >= MOD) x -= MOD;
    return *this;
  }
  Mod& operator*=(Mod rhs) {
    auto y = 1ull * x * rhs.x;
    if(y >= MOD) y %= MOD;
    x = uint32_t(y);
    return *this;
  }
  Mod& operator/=(Mod rhs) { return *this *= fexp(rhs, MOD - 2); }
  friend Mod operator+(Mod lhs, Mod rhs) { return lhs += rhs; }
  friend Mod operator-(Mod lhs, Mod rhs) { return lhs -= rhs; }
  friend Mod operator*(Mod lhs, Mod rhs) { return lhs *= rhs; }
  friend Mod operator/(Mod lhs, Mod rhs) { return lhs /= rhs; }
  bool operator==(Mod rhs) const { return x == rhs.x; }
};
