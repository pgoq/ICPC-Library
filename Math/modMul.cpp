// Mod Mul
// a*b % M
ull modmul(ull a, ull b, ull M){
	long long ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (long long)M);
}