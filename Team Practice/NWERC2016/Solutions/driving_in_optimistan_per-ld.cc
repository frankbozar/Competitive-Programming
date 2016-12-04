#include <cassert>
#include <cstdio>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

int n, d[1200][1200];
vi adj[1200];
int par[2000], joins;

int root(int x) {
	if (par[x] != x) par[x] = root(par[x]);
	return par[x];
}

void join(int a, int b) {
	adj[a].push_back(b); adj[b].push_back(a);
	par[root(a)] = b;
	++joins;
}

bool same(int a, int b) { return root(a) == root(b); }

void findjoin(int u) {
	for (int v = 0; v < u; ++v) {
		if (same(u, v)) continue;
		int x = -1, ok = true;
		for (int k = 0; ok && k < n; ++k) {
			if (u == k || v == k) continue;
			int y = (d[u][v]+d[u][k]-d[v][k])/2;
			if (same(u, k)) ok = y == 0;
			else if (same(v, k)) ok = y == d[u][v];
			else if (x == -1) x = y;
			else ok = x == y;
		}
		if (ok) {
			for (int k = 0; k < n; ++k)  {
				d[k][n] = d[n][k] = d[u][k] + (same(u, k) ? x : -x);
			}
			join(u, n);
			join(v, n);
			++n;
		}
	}
}


map<pii,int> size;
int Size(int u, int p) {
	int &r = size[pii(u,p)];
	if (!r && (r = 1))
		for (auto v: adj[u])
			if (v != p) r += Size(v, u) + d[u][v]-1;
	return r;
}

map<pii,long double> distb;
long double DistB(int u, int p) {
	long double &r = distb[pii(u,p)];
	if (r == 0 && (r = 1))
		for (auto v: adj[u]) 
			if (v != p)
				r += d[u][v]*((d[u][v]-1)/2.0 + Size(v, u)) + DistB(v, u);
	return r-1;
}

int main(void) {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		d[i][i] = 0;
		for (int j = i+1; j < n; ++j)
			scanf("%d", d[i]+j), d[j][i] = d[i][j];
	}
	for (int i = 0; i < 2*n; ++i) par[i] = i;
	while (joins < n-1)
		for (int u = 0; u < n; ++u) findjoin(u);

	long double totd = 0, tots = Size(0, -1);
	for (int u = 0; u < n; ++u) {
		totd += DistB(u, -1);
		for (int v: adj[u]) {
			if (u < v) continue;
			totd += ((DistB(u,v) + DistB(v,u))*(d[u][v]-1) + 
					 1.0L*(Size(u,v) + Size(v,u))*d[u][v]*(d[u][v]-1)/2 +
					 1.0L*d[u][v]*(d[u][v]-1)*(d[u][v]-2)/3);
		}
	}
	printf("%.10Lf\n", totd/(tots*(tots-1)));
	return 0;
}
