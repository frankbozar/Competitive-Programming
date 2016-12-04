#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)       

int n, mk[3], dists[100005][3], a, b, best = 100005;
vector<int> adj[100005][2];
queue<pair<int,int>> q[3];

void bfs(int qIdx, int gIdx) {
	while (!q[qIdx].empty()) {
		pair<int,int> node = q[qIdx].front();
		q[qIdx].pop();
		for (int next : adj[node.first][gIdx]) if (dists[next][qIdx] > 1 + node.second) {
			q[qIdx].push({next, dists[next][qIdx] = 1 + node.second});
		}
	}
}

int main() {
	cin >> n >> mk[1] >> mk[2];
	FOR(i, 0, n) FOR(j, 0, 3) dists[i][j] = 2*n;
	FOR(j, 1, 3) FOR(i, 0, mk[j]) {
		cin >> a;
		q[j].push({a-1, dists[a-1][j] = 0});
	}
	FOR(i, 0, n) {
		cin >> a;
		FOR(j, 0, a) {
			cin >> b;
			adj[i][0].push_back(b-1);
			adj[b-1][1].push_back(i);
		}
	}
	q[0].push({0, dists[0][0] = 0});
	FOR(i, 0, 3) bfs(i, i!=0);
	FOR(i, 0, n) best = min(best, dists[i][0] + dists[i][1] + dists[i][2]);
	if (best <= n) cout << best << endl;
	else cout << "impossible" << endl;
}
