#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long lld;
const int N=1<<20;
lld a[N]={0}, b[2][N]={{0}};

lld f(int l, int r)
{
    return (a[r]-a[l])*(a[r]-a[l]);
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    
    for(int i=1; i<=n; i++)
    {
        scanf("%lld", &a[i]);
        a[i]+=a[i-1];
    }
    
    for(int k=1; k<=m; k++)
    {
        for(int i=0; i<k*(k+1)>>1; i++)
            b[k&1][i]=0;
        
        for(int i=k*(k+1)>>1; i<=n; i++)
            b[k&1][i]=max(b[k&1][i-1], b[k&1^1][i-k]+f(i-k, i));
    }
    
    printf("%lld\n", b[m&1][n]);
}
