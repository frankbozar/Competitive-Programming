#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef pair<ll,ll> pll;
const ll oo = 0x3f3f3f3f3f3f3f3f;
#define sz(c) ll((c).size())
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define xx first
#define yy second

double sum(double n) { return n*(n+1)/2; }
double sumsq(double n) { return n*(n+1)*(2*n+1)/6; }

struct entry {
	ll cnt;
	double half, full;
};

vector<map<ll,ll>> adj;

entry rec(ll k, ll p, ll lengthIn) {
	vector<entry> ch;
	for (const auto &e: adj[k]) if (e.xx != p) {
		ch.pb(rec(e.xx,k,e.yy));
	}
	ll n = sz(ch);
	ll cnt = lengthIn;
	FOR(i,0,n) cnt += ch[i].cnt;
	
	double halfIn = sum(lengthIn), fullIn = (sumsq(lengthIn-1) + sum(lengthIn-1))/2;

	double half = halfIn;
	FOR(i,0,n) half += double(ch[i].cnt)*lengthIn + ch[i].half;

	double full = fullIn;
	FOR(i,0,n) full += ch[i].full;
	FOR(i,0,n) FOR(j,i+1,n) full += ch[i].cnt*ch[j].half + ch[j].cnt*ch[i].half;
	FOR(i,0,n) full += lengthIn*ch[i].half + ch[i].cnt*(halfIn-lengthIn);
	
	return {cnt,half,full};
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ll n; cin >> n;

	adj.resize(n);
	vvl dist(n, vl(n));

	FOR(i,0,n) FOR(j,i+1,n) {
		cin >> dist[i][j];
		dist[j][i] = dist[i][j];
	}
	
	adj[0][1] = adj[1][0] = dist[0][1];
	
	auto off = [&](ll a, ll b, ll c) {
		return (dist[a][b] + dist[a][c] - dist[b][c])/2;
	};

	FOR(c,2,n) {
		pll bestEdge(-1,-1);
		ll bestDist = oo;
		ll cnt = 0;
		FOR(a,0,sz(adj)) for (const auto &e: adj[a]) {
			cnt++;
			ll b = e.xx;
			ll offset = off(a,b,c);
			ll curDist = dist[a][c] - offset;
			if (curDist < bestDist) bestEdge = {a,b}, bestDist = curDist;
		}
		
		ll a, b; tie(a,b) = bestEdge;
		ll offset = off(a,b,c);
		if (offset == dist[a][b]) swap(a,b), offset = 0;

		if (offset == 0) {
			adj[a][c] = adj[c][a] = dist[a][c];
		} else {
			ll d = sz(adj);
			adj.pb(map<ll,ll>());
			adj[a][d] = adj[d][a] = offset;
			adj[b][d] = adj[d][b] = dist[a][b] - offset;
			adj[c][d] = adj[d][c] = dist[a][c] - offset;
			adj[a].erase(b), adj[b].erase(a);
				
			dist.pb(vl(sz(adj)));
			FOR(i,0,d) {
				ll noffset = off(a,b,i);
				dist[i].pb(dist[d][i] = dist[a][i] - noffset + abs(offset - noffset));
			}
		}
    }

	n = sz(adj);
	auto res = rec(0,-1,1);

	cout << fixed << setprecision(15) << res.full/sum(res.cnt-1) << endl;
	
}

