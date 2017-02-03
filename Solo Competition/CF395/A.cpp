#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
vector<vector<int>> e;
vector<int> c, d;

int color(int u, int p)
{
    int& ans=d[u];
    
    if( ans<0 )
    {
        ans=c[u];
        
        for(int v : e[u])
            if( v!=p && color(v, u)!=ans )
                ans=-1;
    }
    
    return ans;
}

int solve(int u=1, int p=0, int pc=-1)
{
    int cc=pc>0 && pc!=c[u] ? -1 : c[u] ;
    int bad=-1;
    
    for(int v : e[u])
    {
        if( v==p )
            continue;
        
        if( color(v, u)<0 )
        {
            if( bad<0 )
                bad=v;
            else
                return -1;
        }
        else if( color(v, u)!=cc )
            cc=-1;
    }
    
    if( bad<0 )
        return u;
    else if( cc<0 )
        return -1;
    else
        return solve(bad, u, cc);
}

int main()
{
    int n;
    scanf("%d", &n);
    e.resize(n+1);
    c.assign(n+1, -1);
    d.assign(n+1, -1);
    
    for(int i=1; i<n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    
    for(int i=1; i<=n; i++)
        scanf("%d", &c[i]);
    
    int ans=solve();
    
    if( ans<0 )
        printf("NO\n");
    else
        printf("YES\n%d\n", ans);
}
