#include<cstdio>
#include<vector>
using namespace std;
typedef long long lld;
char s[1<<20]={0};

int main()
{
    int n, m;
    scanf("%d%d%s", &n, &m, s+1);
    vector<bool> a(n+1, false);
    vector<lld> c(n+1, 0), d(n+1, 0);
    
    for(int i=1; i<=n; i++)
        a[i]=s[i]=='0';
    
    for(; m>0; m--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        c[x]+=a[y];
        d[x]++;
        c[y]+=a[x];
        d[y]++;
    }
    
    lld ans=0;
    
    for(int i=1; i<=n; i++)
    {
        if( a[i] )
            ans+=d[i]*(d[i]-1);
        else
            ans+=c[i]*(d[i]-1);
    }
    
    printf("%lld\n", ans);
}
