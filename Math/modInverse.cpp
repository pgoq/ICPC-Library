// Mod Inverse
// m[i] = inverso modular de i no modulo mod
m[1] = 1;
for(int i=2; i<ms; i++){
  m[i] = (mod - mod/i) * m[mod % i] % mod;
}
// pegando inverso modular de fat[i]
fat[0] = 1;
inv[0] = 1;
for(int i=1; i<ms; i++){
  fat[i] = (fat[i-1] * i)%mod;
  inv[i] = (inv[i-1] * m[i])%mod;
}