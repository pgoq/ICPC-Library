// Suffix Array

// lcp[i] = lcp entre s[sa[i],...,n-1] e s[sa[i+1],...,n-1]
// se for ter mais de um separador (mais de uma string), o separador mais a direita tem que ser o menor
struct SuffixArray {
    vector<int> sa, lcp;
    SuffixArray(string s, int sigma = 260) : sa(s.size() + 1), lcp(s.size()) {
        s += "$";
        int n = s.size(), M = max(n, sigma);
        vector<int> ra(n);
        for (int i = 0; i < n; i++) sa[i] = i, ra[i] = s[i];
        for (int k = 0; k < n; k = max(1, 2 * k)) {
            vector<int> nsa(sa), nra(n), cnt(M);

            for (int i = 0; i < n; i++) nsa[i] = (nsa[i] - k + n) % n, cnt[ra[i]]++;
            for (int i = 1; i < M; i++) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i + 1; i--) sa[--cnt[ra[nsa[i]]]] = nsa[i];
            for (int i = 1, r = 0; i < n; i++) {
                if (ra[sa[i]] != ra[sa[i - 1]] || ra[(sa[i] + k) % n] != ra[(sa[i - 1] + k) % n]) r++;
                nra[sa[i]] = r;
            }
            ra = nra;
            if (ra[sa[n - 1]] == n - 1) break;
        }
        sa = vector<int>(sa.begin() + 1, sa.end());

        n--;
        int k = 0;
        for (int i = 0; i < n; i++) ra[sa[i]] = i;
        for (int i = 0; i < n; i++, k -= !!k) {
            if (ra[i] == n - 1) { k = 0; continue; }
            int j = sa[ra[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            lcp[ra[i]] = k;
        }
    }
};