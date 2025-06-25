const int MOD = 7;
struct Mod {
	int x;
	Mod(ll xx=0) : x((xx%MOD) + (xx < 0 ? MOD : 0)) {}
	Mod operator+(Mod b) { return Mod(x + b.x); }
	Mod operator-(Mod b) { return Mod(x - b.x); }
	Mod operator*(Mod b) { return Mod(1ll * x * b.x); }
	Mod operator/(Mod b) { return Mod(*this * b.inv()); }
    Mod inv() { return fexp(MOD-2); }
	Mod fexp(ll e) {
        Mod ret(1), a(x);
        while(e){
            if(e&1) ret = ret * a;
            a = a * a;
            e/=2;
        }
        return ret;
	}
};