// Poly Inverse
// pega inverso de um polinomio
// nlog^2

vector<int> get_inverse(vector<int>& a) {
    if (a.empty()) return {};
    int Y = a.size() - 1, n = 32 - __builtin_clz(Y);
    n = (1 << n);
    a.resize(n);
    vector<int> inv = { fexp(a[0], mod - 2) }, f, c;
    for (int sz = 2; sz <= n; sz *= 2) {
        while (f.size() < sz) f.push_back(a[f.size()]);
        c = conv(f, inv);
        for (int i = 0; i < sz; i++) c[i] = (c[i] == 0 ? 0 : mod - c[i]);
        c[0] += (c[0] + 2 >= mod ? 2 - mod : 2);
        inv = conv(inv, c);
        inv.resize(sz);
    }
    return inv;
}