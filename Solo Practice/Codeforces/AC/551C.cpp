#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<60;
lld a[1<<20]={0};

bool check(int n, int m, lld x)
{
    lld cnt=0, pre=0;
    
    for(int i=n; i>0; i--)
    {
        lld y=a[i];
        lld tmp=min(y, pre);
        y-=tmp;
        pre-=tmp;
        
        if( y==0 )
            continue;
        else if( x<=i )
            return false;
        
        tmp=x-i;
        cnt+=(y+tmp-1)/tmp;
        
        if( cnt>m )
            return false;
        
        y%=tmp;
        
        if( y>0 )
            pre=tmp-y;
    }
    
    return true;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    
    for(int i=1; i<=n; i++)
        scanf("%lld", &a[i]);
    
    lld ans=-1;
    
    for(lld l=0, r=INF; l<r; )
    {
        lld x=(l+r)>>1;
        
        if( check(n, m, x) )
            r=ans=x;
        else
            l=x+1;
    }
    
    printf("%lld\n", ans);
}
