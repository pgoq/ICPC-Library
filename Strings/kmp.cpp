// KMP

// pi[i] = j -> s[0..j] eh o maior prefixo que eh sufixo de s[0..i]
vector<int> get_pi(const string &s){
    int n = s.size();
    vector<int> pi(n, -1);
    for(int i=1, j=-1; i<n; i++){
        while(j >= 0 && s[i] != s[j+1]) j = pi[j];
        if(s[i] == s[j+1]) j++;
        pi[i] = j; 
    }
    return pi;
} 