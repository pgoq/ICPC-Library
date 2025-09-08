// KMP Automaton

int go[ms][sigma];

int val(char c) { return c - 'a'; }

void automaton(string& s) {
    for (int i = 0; i < sigma; i++) go[0][i] = (i == val(s[0]));
    int border = 0;
    for (int i = 1; i <= (int)s.size(); i++) {
        for (int j = 0; j < sigma; j++) {
            go[i][j] = go[border][j];
        }
        if (i < (int)s.size()) {
            go[i][val(s[i])] = i + 1;
            border = go[border][val(s[i])];
        }
    }
}