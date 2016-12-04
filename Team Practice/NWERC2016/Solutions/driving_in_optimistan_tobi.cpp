#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define FOR(i,a,b) for (ll i=(a); i<(b); i++)
#define OFFSET(A,B,C) ((dist[A][B] + dist[A][C] - dist[B][C]) / 2)
#define EDGE(A,B,c) dist[A][B] = dist[B][A] = adj[A][B] = adj[B][A] = c
ll n, dist[1000][1000], A, B, C, nodes;
priority_queue<pair<ll,ll>> pq;
bool intree[1000];
map<ll,ll> adj[1000];

bool walk(ll from, ll to, ll par, vector<ll> &path) {
	if (from == to) return true;
	for (auto next : adj[from]) if (next.first != par) {
		if (walk(next.first, to, from, path)) {
			path.push_back(from);
			return true;
		}
	}
	return false;
}

void computeDist(int from, int cur, int curDist, int p) {
	dist[from][cur] = curDist;
	for (auto next : adj[cur]) if (next.first != p) computeDist(from, next.first, curDist + next.second, cur);
}

int main() {
	cin >> n;
	FOR(i, 0, n-1) FOR(j, i+1, n) {
		cin >> dist[i][j];
		dist[j][i] = dist[i][j];
	}
	FOR(i, 1, n) pq.push(make_pair(-dist[0][i], i)); // MST init

	auto next = pq.top(); pq.pop();
	intree[0] = intree[next.second] = true;
	EDGE(0, next.second, -next.first);
	FOR(i, 0, n) if (!intree[i]) pq.push(make_pair(-dist[next.second][i], i));
	nodes = n; // will include artificial nodes, but not the implicit nodes

	while (!pq.empty()) {
		next = pq.top(); pq.pop();
		A = next.second;
		if (intree[A]) continue; // already part of tree
		FOR(i, 0, n) if (i != A && !intree[i]) pq.push(make_pair(-dist[i][A], i));  	// B-X-------A   Example:
		pair<ll,pair<ll,ll>> minConn = make_pair(LLONG_MAX, make_pair(-1, -1));     	//  _|           - A is merged into tree of B, C and D
		FOR(B, 0, n) if (intree[B]) FOR(C, B + 1, n) if (intree[C]) {               	// / |           - B and C are close intree nodes to A
			minConn = min(minConn, make_pair(OFFSET(A,B,C), make_pair(B, C)));  	// | C           - X has to be created such that
		}                                                                           	// |               AB + AC - BC = 2*AX
		intree[A] = true;                                                           	// D
		B = minConn.second.first, C = minConn.second.second;
		ll AX = minConn.first, XC = dist[A][C] - AX, curDist = 0;
		vector<ll> path {C};
		walk(B, C, -1, path); // get path from C to B
		FOR(i, 0, path.size()) {
			if (curDist == XC) { // there is already a node, connect it
				EDGE(A, path[i], AX);
				break;
			} else if (curDist > XC) { // create a new node between path[i-1] and path[i]
				adj[path[i]].erase(path[i-1]);
				adj[path[i-1]].erase(path[i]);
				EDGE(path[i-1], nodes, XC - (curDist - dist[path[i]][path[i-1]]));
				EDGE(path[i], nodes, curDist - XC);
				EDGE(nodes, A, AX);
				nodes++;
				break;
			}
			curDist += dist[path[i+1]][path[i]];
		}
	}

	FOR(i, 0, nodes) computeDist(i, i, 0, -1);
	double sum = 0;
	ll totNodes = nodes;
	FOR(i, 0, nodes) FOR(j, i+1, nodes) {
		int legs[2] = {-1, -1}, vars[2] = {j, i}; // i -- legs[0] -- (middle) -- legs[1] -- j
		FOR(k, 0, 2) for (auto next : adj[vars[1-k]]) if (legs[k] == -1 || dist[next.first][vars[k]] < dist[legs[k]][vars[k]]) legs[k] = next.first;
		ll left = dist[i][j] - dist[legs[0]][j], right = dist[i][j] - dist[legs[1]][i];
		ll middle = dist[i][j] - left - right;
		if (legs[0] == j) { // there is only one leg
			totNodes += left - 1;
			sum += (left*(left+1)*(left+2))/6.0;
		} else sum += left*right*(2 + left + right + 2*middle)/2;
	}
	cout << setprecision(20) << sum / (totNodes*(totNodes-1)/2) << endl;

	return 0;
}
