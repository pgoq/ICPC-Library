// Bit 2D

int bit[ms][ms];
void update(int x, int y, int v) {
    for (x++, y++; x < ms; x += x & -x) {
        for (int y1 = y; y1 < ms; y1 += y1 & -y1) {
            bit[x][y1] += v;
        }
    }
}

int query(int x, int y) {
    int r = 0;
    for (x++, y++; x > 0; x -= x & -x) {
        for (int y1 = y; y1 > 0; y1 -= y1 & -y1) {
            r += bit[x][y1];
        }
    }
    return r;
}

int query(int x1, int y1, int x2, int y2){
    return query(x2, y2) - query(x2, y1-1) - query(x1-1, y2) + query(x1-1, y1-1);
}