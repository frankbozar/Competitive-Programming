#include<cstdio>
#include<algorithm>
using namespace std;
const int INF=1<<24;
typedef long long lld;
int a[INF]={0}, c[INF];

bool check(int n, int m, int k)
{
    lld cnt=0;
    c[k]=1;
    
    for(int i=k; i<=n; i++)
    {
        if( i>>1>=k )
            c[i]=c[(i+1)>>1]+c[i>>1];
        else if( (i+1)>>1>=k )
            c[i]=c[(i+1)>>1];
        else
            c[i]=1;
        
        cnt+=a[i]*(lld)c[i];
    }
    
    return cnt>=m;
}

int main()
{
    int n, m, k=0, ans=-1;
    scanf("%d%d", &n, &m);
    
    for(int i=0; i<n; i++)
    {
        int x;
        scanf("%d", &x);
        k=max(k, x);
        a[x]++;
    }
    
    for(lld l=1, r=k+1; l<r; )
    {
        int x=(l+r)>>1;
        
        if( !check(k, m, x) )
            r=x;
        else
        {
            l=x+1;
            ans=x;
        }
    }
    
    printf("%d\n", ans);
}
