#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

struct ds
{
    vector<int> p, w;
    ds(int n) : p(n+1, -1){}
    
    int find(int x)
    {
        return p[x]<0 ? x : p[x]=find(p[x]);
    }
    
    void join(int x, int y)
    {
        x=find(x);
        y=find(y);
        
        if( x!=y )
            p[x]=y;
    }
};

void update(const vector<int>& op, vector<int>& dp, int k, int w, int b)
{
    for(int i=k; i>=w; i--)
        dp[i]=max(dp[i], op[i-w]+b);
}

int main()
{
    int n, m, k, ans=0;
    scanf("%d%d%d", &n, &m, &k);
    vector<int> w(n+1, 0), b(n+1, 0), sw(n+1, 0), sb(n+1, 0), dp(k+1, 0);
    vector<vector<int>> e(n+1);
    ds D(n);
    
    for(int i=1; i<=n; i++)
        scanf("%d", &w[i]);
    
    for(int i=1; i<=n; i++)
        scanf("%d", &b[i]);
    
    for(int i=0; i<m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        D.join(u, v);
    }
    
    for(int i=1; i<=n; i++)
    {
        int p=D.find(i);
        e[p].push_back(i);
        sw[p]+=w[i];
        sb[p]+=b[i];
    }
    
    for(int i=1; i<=n; i++)
    {
        vector<int> tmp=dp;
        update(tmp, dp, k, sw[i], sb[i]);
        
        for(int x : e[i])
            update(tmp, dp, k, w[x], b[x]);
    }
    
    for(int i=0; i<=k; i++)
        ans=max(ans, dp[i]);
    
    printf("%d\n", ans);
}