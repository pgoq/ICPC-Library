// Bit
//

struct Bit {
    vector<int> bit;
    Bit(int n) : bit(n + 1) {}
    void add(int idx, int v) {
        for (idx++; idx < (int)bit.size(); idx += idx & -idx) {
            bit[idx] += v;
        }
    }
    int query(int idx) {
        int ret = 0;
        for (idx++; idx > 0; idx -= idx & -idx) {
            ret += bit[idx];
        }
        return ret;
    }
};
