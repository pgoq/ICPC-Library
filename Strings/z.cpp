// Z

// z[i] = tamanho do maior prefixo comecando de i que tambem é prefixo de s
vector<int> ZFunc(const string &s) {
    vector<int> z(s.size(), 0);
    int n = (int) s.size(), a = 0, b = 0;
    if(!z.empty()) z[0] = 0;
    for(int i = 1; i < n; i++) {
        int end = i; 
        if (i < b) end = min(i + z[i - a], b);
        while(end < n && s[end] == s[end - i]) ++end;
        z[i] = end - i; if(end > b) a = i, b = end;
    }
    return z;
}
