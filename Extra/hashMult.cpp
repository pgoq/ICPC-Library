// Hash Mult
//

ull hashify(ull sum) {
    sum += FIXED_RANDOM;
    sum += 0x9e3779b97f4a7c15;
    sum = (sum ^ (sum >> 30)) * 0xbf58476d1ce4e5b9;
    sum = (sum ^ (sum >> 27)) * 0x94d049bb133111eb;
    return sum ^ (sum >> 31);
}