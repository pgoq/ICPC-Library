// Euclides

// pega x, y tal que
// A*x + B*y = gcd(A, B)
// se gcd(A, B) = 1, 
// x eh o inverso modular de A no modulo B
// y eh o inverso modular de B no modulo A

tuple<ll, ll, ll> ext_gcd(ll a, ll b) {
    if (!a) return { b, 0, 1 };
    auto [g, x, y] = ext_gcd(b % a, a);
    return { g, y - b / a * x, x };
}
