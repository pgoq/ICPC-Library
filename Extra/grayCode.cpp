// Gray Code
// g(n) xor g(n+1), tem apenas 1 bit ativado

// pega o cara que ta na posição N
int g(int n) {
    return n ^ (n >> 1);
}

// dado g(n), retorne n
int rev_g(int g) {
    int n = 0;
    for (; g; g >>= 1) {
        n ^= g;
    }
    return n;
}
