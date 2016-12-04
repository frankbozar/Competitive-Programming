#include <bits/stdc++.h>
#define MAXN 200005
#define MAXP 400005

using namespace std;

struct node {
	int l, r, ls, rs;
	int cnt;
	long long single, val, xp;
};

map<string, int> names;
static int f[MAXN];
static int ford[MAXN];
static int costs[MAXN];
static int fstart[MAXN];

static int t[MAXP];
static int id[MAXP];

static struct node a[MAXN];
int r, w;
static int roots[MAXN];
static int ans[MAXN];

void initTree(int sz, int offset) {
	int root = w;
	a[w].l = 0;
	a[w].r = sz-1;
	a[w].ls = -1;
	a[w].rs = -1;
	a[w].cnt = 0;
	a[w].val = 0;
	w++;
	while (w > r) {
		if (a[r].r > a[r].l) {
			a[w].l = a[r].l;
			a[w].r = (a[r].l + a[r].r) / 2;
			a[w].ls = -1;
			a[w].rs = -1;
			a[w].cnt = 0;
			a[w].val = 0;
			a[r].ls = w;
			w++;
			a[w].l = a[w-1].r + 1;
			a[w].r = a[r].r;
			a[w].ls = -1;
			a[w].rs = -1;
			a[w].cnt = 0;
			a[w].val = 0;
			a[r].rs = w;
			w++;
		}
		r++;
	}
	for (int i = w-1; i >= root; i--) {
		if (a[i].l == a[i].r) {
			a[i].single = costs[offset + a[i].l];
		} else {
			a[i].single = a[a[i].ls].single + a[a[i].rs].single;
		}
	}
}

void add(int point, int where) {
	if (a[point].l == a[point].r) {
		a[point].cnt++;
		a[point].val = (long long)a[point].cnt * a[point].single;
		a[point].xp = (long long)a[point].cnt;
	} else {
		if (a[a[point].ls].r >= where) {
			add(a[point].ls, where);
		} else {
			add(a[point].rs, where);
		}
		a[point].cnt = a[a[point].ls].cnt + a[a[point].rs].cnt;
		a[point].val = a[a[point].ls].val + (long long)a[a[point].ls].cnt * a[a[point].rs].single + a[a[point].rs].val;
		a[point].xp = a[a[point].ls].xp + (long long)a[a[point].ls].cnt * (long long)(a[a[point].rs].r - a[a[point].rs].l + 1) + a[a[point].rs].xp;
	}
}

pair<long long, pair<int, long long> > get(int point, int L, int R, int carry) {
	if (R < L) {
		return make_pair(0, make_pair(0, 0));
	}
	if ((a[point].l >= L) && (a[point].r <= R)) {
		return make_pair(a[point].val + (long long)carry * a[point].single, make_pair(a[point].cnt, a[point].xp + (long long)carry * (long long)(a[point].r - a[point].l + 1)));
	} else {
		pair<long long, pair<int, long long> > left = make_pair(0, make_pair(0, 0));
		if (a[a[point].ls].r >= L) {
			left = get(a[point].ls, L, R, carry);
		}
		pair<long long, pair<int, long long> > right = make_pair(0, make_pair(0, 0));
		if (a[a[point].rs].l <= R) {
			right = get(a[point].rs, L, R, carry + left.second.first);
		}
		return make_pair(left.first + right.first, make_pair(left.second.first + right.second.first, left.second.second + right.second.second));
	}
}

int recalc(int family, int forder) {
	add(roots[family], forder);

	long long candies = 4 * a[roots[family]].cnt - 1;
	int L = 0; int R = fstart[family+1] - fstart[family] - 1;
	int C;
	pair<long long, pair<int, long long> > val;
	while (R > L) {
		C = (L+R+1)/2;
		val = get(roots[family], 0, C-1, 0);
		if (val.first <= candies) L = C;
		else R = C-1;
	}
	val = get(roots[family], 0, L-1, 0);

	//cout << "Can evolve " << val.second.first << " Pokemon up to level " << L << " for " << val.first << " resulting in " << val.second.second << " evolutions" << endl;

	candies -= val.first;
	long long xp = val.second.second;
	int cost = costs[fstart[family] + L];

	if (cost) {
		//Not final level.
		xp += (candies / cost);
	}

	//	cout << "Performed a total of " << xp << " evolutions" << endl; 

	return (int)xp * 1000;
}

int main () {
	ios::sync_with_stdio(false);
	r = 0; w = 0;
	int F;
	int N = 0;
	cin >> F;
	for (int iF = 0; iF < F; iF++) {
		fstart[iF] = N;
		int FC;
		cin >> FC;
		string nm;
		cin >> nm;
		names[nm] = N;
		f[N] = iF;
		ford[N] = 0;
		costs[N] = 0;
		N++;
		for (int i = 1; i < FC; i++) {
			int c;
			cin >> c >> nm;
			costs[N-1] = c;
			names[nm] = N;
			f[N] = iF;
			ford[N] = i;
			costs[N] = 0;
			N++;
		}
		roots[iF] = w;
		initTree(FC, fstart[iF]);
		ans[iF] = 0;
	}
	fstart[F] = N;
	int P;
	cin >> P;
	for (int i = 0; i < P; i++) {
		string nm;
		cin >> t[i] >> nm;
		id[i] = names.find(nm)->second;
	}
	int res = 0;
	int cur = 0;

	int prev = 0;
	for (int i = 0; i < P; i++)
	{
		while (t[prev] + 1800 <= t[i]) {
			prev++;
		}

		int family = f[id[i]];
		int forder = ford[id[i]];
		cur -= ans[family];
		ans[family] = recalc(family, forder);
		cur += ans[family];

		res = max(res, cur + (i - prev + 1) * 100);
	}

	cout << res + P * 100 << endl;
	return 0;
}
