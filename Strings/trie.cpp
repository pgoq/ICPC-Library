// Trie

int trie[ms][sigma], terminal[ms];
int z = 1;

int val(char c) { return c - 'a'; }

void add(const string& p) {
    int cur = 0;
    for (int i = 0; i < p.size(); i++) {
        int& nxt = trie[cur][val(p[i])];
        if (nxt == 0) nxt = z++;
        cur = nxt;
    }
    terminal[cur]++;
}

bool query(const string& s) {
    int cur = 0;
    for (int i = 0; i < s.size(); i++) {
        int nxt = trie[cur][val(s[i])];
        if (nxt == 0) return false;
        cur = nxt;
    }
    return (terminal[cur] > 0);
}
