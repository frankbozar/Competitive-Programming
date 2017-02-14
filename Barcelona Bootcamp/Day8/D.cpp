#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

void solve(vector<int>& f, int n)
{
    map<int, int> M;
    
    for(int i=1; i<=n; i++)
        M[ f[i] ]=0;
    
    int m=0;
    
    for(auto& it : M)
        it.second=++m;
    
    vector<int> g(n+1, 0), h(m+1, 0);
    
    for(int i=1; i<=n; i++)
    {
        g[i]=M[ f[i] ];
        h[ M[ f[i] ] ]=f[i];
    }
    
    for(int i=1; i<=m; i++)
        if( g[ h[i] ]!=i )
        {
            printf("-1\n");
            return ;
        }
    
    for(int i=1; i<=n; i++)
        if( h[ g[i] ]!=f[i] )
        {
            printf("-1\n");
            return ;
        }
    
    printf("%d\n", m);
    
    for(int i=1; i<=n; i++)
        printf(i==n ? "%d\n" : "%d ", g[i]);
    
    for(int i=1; i<=m; i++)
        printf(i==m ? "%d\n" : "%d ", h[i]);
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> a(n+1, 0);
    
    for(int i=1; i<=n; i++)
        scanf("%d", &a[i]);
    
    solve(a, n);
}

/*

3
1 2 3

3
2 2 2

2
2 1


*/
