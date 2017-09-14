
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

typedef long long lld;
const lld P=1000000007;
int n;
vector<vector<int>> E;
vector<map<int, lld>> D;
vector<lld> sum;
vector<int> cnt;

lld inv(lld a)
{
	lld res=1;
	for(lld b=P-2; b>0; a=a*a%P, b/=2)
		if(b&1)
			res=res*a%P;
	return res;
}
lld sol(int u, int p)
{
	if(D[u].find(p)==D[u].end())
	{
		lld &res=D[u][p];
		res=1;
		for(int v: E[u])
			if(v!=p)
				res=(res*(sol(v, u)+1))%P;

	}
//	printf("@u=%d p=%d %lld\n", u, p, D[u][p]);
	return D[u][p];
}

void dfs(int u, int p)
{
	lld &res=D[u][p];
	res=1;
	
	for(int v: E[u])
		if(v!=p)
		{
			dfs(v, u);
			res=(res*(sol(v, u)+1))%P;
			cnt[u]+=(sol(v, u)+1)%P==0;
		}
	
}

void dfs2(int u, int p)
{
	sum[u]=sol(u, p);
	if(p!=0)
	{
		sum[u]=(sum[u]*(sol(p, u)+1))%P;
		cnt[u]+=(sol(p, u)+1)%P==0;
	}
	for(int v: E[u])
		if(v!=p)
		{
			if((D[v][u]+1)%P!=0)
			{
				D[u][v]=(sum[u]*inv(D[v][u]+1))%P;
			}
			else if(cnt[u]==1)
			{
				sol(u, v);
			}
			else
				D[u][v]=0;
			dfs2(v, u);
		}
//		printf("~!u=%d p=%d %lld\n", u, p, D[u][p]);
}

int main()
{
	int T;
	for(scanf("%d", &T); T>0; T--)
	{
		scanf("%d", &n);
		E.clear();
		E.resize(n+1);
		D.clear();
		D.resize(n+1);
		sum.clear();
		sum.resize(n+1);
		cnt.clear();
		cnt.resize(n+1);
		for(int i=2; i<=n; i++)
		{
			int v;
			scanf("%d", &v);
			E[v].push_back(i);
			E[i].push_back(v);
		}
		dfs(1, 0);
		dfs2(1, 0);
		lld ans=0;
		for(int i=1; i<=n; i++)
			ans=(ans+sol(i, 0))%P;
		printf("%lld\n", ans);
	}
}

/*

2
3
1 1
5
1 2 3 4

*/
