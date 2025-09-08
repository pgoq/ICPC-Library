// Phi

int phi[ms];

void calculatePhi() {
    for (int i = 0; i < ms; i++) phi[i] = (i & 1 ? i : i / 2);
    for (int i = 3; i < ms; i += 2) {
        if (phi[i] == i) {
            for (int j = i; j < ms; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
}