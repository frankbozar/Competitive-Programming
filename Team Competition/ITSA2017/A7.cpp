#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1000;
vector<vector<int>> e;
int a[64][2][2][3][2][3];

int solve(int u, int ustat, int p, int pstat, int pneed, int pexac, int bstat)
{
    bstat=min(bstat, 2);
    int& ans=a[u][ustat][pstat][pneed][pexac][bstat];
    
    if( ans<0 )
    {
        ans=INF;
        vector<int> c;
        
        for(int v : e[u])
            if( v!=p )
                c.push_back(v);
        
        int n=c.size();
        
        for(int cstat=pneed; cstat<=(pexac ? pneed : n); cstat++)
        {
			int uneed= pstat==1 || ustat==1 || cstat>0 ? 0 : 2-bstat ;
			vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(n+3, vector<int>(uneed+1, INF)));
			dp[0][0][0]=0;
			
            for(int i=1; i<=n; i++)
                for(int j=0; j<=cstat; j++)
					for(int k=0; k<=uneed; k++)
						for(int l=0; l<=k; l++)
						{
							dp[i][j][k]=min(dp[i][j][k], dp[i-1][j][l]+solve(c[i-1], 0, u, ustat, k-l, k!=uneed, pstat+cstat));
							
							if( j>0 )
								dp[i][j][k]=min(dp[i][j][k], dp[i-1][j-1][l]+solve(c[i-1], 1, u, ustat, k-l, k!=uneed, pstat+cstat-1));
						}
            
            ans=min(ans, dp[n][cstat][uneed]+ustat);
        }
    }
    
    return ans;
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n;
        scanf("%d", &n);
        e.clear();
        e.resize(n+1);
        
        for(int i=1; i<n; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            e[u].push_back(v);
            e[v].push_back(u);
        }
        
		memset(a, 0xFF, sizeof(a));
		int ans=min(solve(1, 0, 0, 0, 0, 0, 0), solve(1, 1, 0, 0, 0, 0, 0));
		printf("%d\n", ans);
    }
}

/*

3

7
1 2
2 3
3 4
4 5
5 6
6 7

9
1 2
2 3
2 4
4 5
4 6
4 7
7 8
7 9

7
1 2
1 3
2 4
2 5
3 6
3 7

*/
