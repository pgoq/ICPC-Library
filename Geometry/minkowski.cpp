// Minkowski

// Assume que p e q sao poligonos convexos ordenados ccw
vector<pt> minkowski(vector<pt> p, vector<pt> q) {
    auto fix = [](vector<pt>& P) {
        int pos = 0;
        for (int i = 1; i < P.size(); i++) {
            if (P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x)) pos = i;
        }
        rotate(P.begin(), P.begin() + pos, P.end());
        P.push_back(P[0]), P.push_back(P[1]);
    };
    fix(p), fix(q);
    vector<pt> result;
    int i = 0, j = 0;
    while (i < p.size() - 2 || j < q.size() - 2) {
        result.push_back(p[i] + q[j]);
        auto cross = ((p[i + 1] - p[i]) ^ (q[j + 1] - q[j]));
        if (cross >= 0 && i < p.size() - 2) i++;
        if (cross <= 0 && j < q.size() - 2) j++;
    }
    return result;
}
