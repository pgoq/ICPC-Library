// Mod Inverse
// m[i] = inverso modular de i no modulo mod
m[1] = 1;
for (int i = 2; i < ms; i++) {
    m[i] = (mod - mod / i) * m[mod % i] % mod;
}