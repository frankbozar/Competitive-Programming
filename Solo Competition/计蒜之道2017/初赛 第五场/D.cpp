#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
#define data pair<lld,int>
#define v first
#define i second

int main()
{
    int n, m;
    scanf("%d", &n);
    vector<lld> a(n+1, 0), C(n+1);
    
    for(int i=1; i<=n; i++)
        C[i]=((lld)rand()<<32)|rand();
    
    for(int i=1; i<=n; i++)
    {
        scanf("%lld", &a[i]);
        a[i]=a[i-1]+C[ a[i] ];
    }
    
    scanf("%d", &m);
    vector<int> ans(m+1);
    vector<vector<data>> h(n+1);
    
    for(int i=1; i<=m; i++)
    {
        int k;
        scanf("%d", &k);
        h[k].push_back(data(0, i));
        
        for(int j=1; j<=k; j++)
        {
            int x;
            scanf("%d", &x);
            h[k].back().v+=C[x];
        }
    }
    
    for(int k=1; k<=n; k++)
    {
        if( h[k].empty() )
            continue;
        
        for(int i=k; i<=n; i++)
            h[k].push_back(data(a[i]-a[i-k], 0));
        
        sort(h[k].begin(), h[k].end());
        int s=h[k].size();
        
        for(int j, i=0; i<s; i++)
        {
            if( i==0 || h[k][i].v!=h[k][i-1].v )
                j=0;
            
            j+= h[k][i].i==0;
            ans[ h[k][i].i ]=j;
        }
    }
    
    for(int i=1; i<=m; i++)
        printf("%d\n", ans[i]);
}
