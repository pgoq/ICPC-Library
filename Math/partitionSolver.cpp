// Partition Solver
//

template<const int N>
class PartitionSolver {
public:
	PartitionSolver() {
		vector<int> a;
		partitions.push_back(a);
		gen(1, N, a);
		sort(partitions.begin(), partitions.end());
		to.assign(partitions.size(), vector<int>(N+1, -1));
    	from = to;
		for(int i = 0; i < (int) partitions.size(); i++) {
			int sum = 0;
			auto arr = partitions[i];
			for(auto x : arr) {
				sum += x;
			}
			to[i][0] = i;
			from[i][0] = i;
			for(int j = 1; j + sum <= N; j++) {
				arr = partitions[i];
				arr.push_back(j);
				sort(arr.begin(), arr.end());
				to[i][j] = getIndex(arr);
        		from[to[i][j]][j] = i;
			}
		}
	}

	int size() const { return (int) partitions.size(); }
	int getIndex(const vector<int> &arr) const { return lower_bound(partitions.begin(), partitions.end(), arr) - partitions.begin(); }
	int add(int id, int num) const { return to[id][num]; }
  	int remove(int id, int num) const { return from[id][num]; }
	vector<int> getPartition(int id) const { return partitions[id]; }
private:
	vector<vector<int>> partitions, to, from;
	void gen(int i, int sum, vector<int> &a) {
		if(i > sum) { return; }
		a.push_back(i);
		partitions.push_back(a);
		gen(i, sum - i, a);
		a.pop_back();
		gen(i+1, sum, a);
	}
};

// calcula o numero de partições p todos os numeros <= n
vector<ll> partitionNumber(int n) {
	vector<ll> ans(n+1, 0);
	ans[0] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j * (3 * j + 1) / 2 <= i; j++) {
			ll here =  ans[i - j * (3 * j + 1) / 2];
			ans[i] = (ans[i] + (j&1 ? here : -here));
		}
		for(int j = 1; j * (3 * j - 1) / 2 <= i; j++) {
			ll here = ans[i - j * (3 * j - 1) / 2];
			ans[i] = (ans[i] + (j&1 ? here : -here));
		}
	}
	return ans;
}