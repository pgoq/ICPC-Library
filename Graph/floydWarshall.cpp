// Floud Warshall

int g[ms][ms];
void init(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g[i][j] = inf;
        }
        g[i][i] = 0;
    }
}
// distancia de U -> V é -infinito se existe um vertice X 
// tal que g[x][x] < 0 e g[u][x] != INF e g[x][v] != INF

void run(int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
}
