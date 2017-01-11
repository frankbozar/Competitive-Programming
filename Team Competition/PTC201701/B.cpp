#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int n;
int a[128][128];
bool vis[128][128];
int dx[5] = {0,-1,0,1,0};
int dy[5] = {0,0,1,0,-1};

int dfs(int x, int y, int dir)
{
    if( x < 0 || x >= n || y < 0 || y >= n || vis[x][y] )
        return 0;
    if( a[x][y] != 0 )
    {
        dir = a[x][y];
        vis[x][y] = true;
    }
    return (a[x][y]!=0)+dfs(x+dx[dir],y+dy[dir],dir);
}

int main()
{
    int T;
    scanf("%d",&T);

    for(int t = 0; t < T; t++)
    {
        scanf("%d",&n);

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                scanf("%d",&a[i][j]);

        int ans = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if( a[i][j] != 0 )
                {
                    memset(vis,false,sizeof(vis));
                    ans = max(ans,dfs(i,j,a[i][j]));
                }

        printf("%d\n",ans);
    }
	return 0;
}

/*
1
5
3 0 0 0 0
2 3 0 0 0
0 2 3 0 0
0 0 2 3 0
0 0 0 2 3
*/
