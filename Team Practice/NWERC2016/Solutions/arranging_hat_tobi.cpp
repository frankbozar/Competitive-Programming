#include <iostream>
#include <cstring>
#include <string>

using namespace std;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define FORD(i,a,b) for (int i=int(b)-1; i>=(a); i--)

int n, m, dp[401][41][41][10], moves[401][41][41][10];
string nums[40], output[40];

int rec(int index, int from, int to, int max) {
	if (to <= from || index >= m) return 0;
	if (max < 0) return 111; // at most n*l_10(n)
	if (dp[index][from][to][max] != -1) return dp[index][from][to][max];
	int cur = rec(index, from, to, max-1), local = 0;
	moves[index][from][to][max] = 0;
	FORD(i, from, to) {
		if (nums[i][index] != max + '0') local++;
		int next = rec(index, from, i, max-1) + rec(index+1, i, to, 9) + local;
		if (next < cur) {
			moves[index][from][to][max] = to-i;
			cur = next;
		}
	}
	return dp[index][from][to][max] = cur;
}

void fix(int index, int from, int to, int max) {
	if (to <= from || index >= m || max < 0) return;
	int same = moves[index][from][to][max];
	FOR(i, 0, same) output[to-1-i][index] = max + '0';
	fix(index, from, to-same, max-1);
	fix(index+1, to-same, to, 9);
}

int main() {
	cin >> n >> m;
	FOR(i, 0, n) cin >> nums[i];
	FOR(i, 0, n) output[i] = nums[i];
	memset(dp, -1, sizeof dp);
	rec(0, 0, n, 9);
	fix(0, 0, n, 9);
	FOR(i, 0, n) cout << output[i] << " ";
	cout << endl;
	return 0;
}
