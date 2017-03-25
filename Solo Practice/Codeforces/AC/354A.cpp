#include<cstdio>
#include<algorithm>
using namespace std;
const int INF=2000000000;
int a[1<<20]={0};

int main()
{
    int n, l, r, p, q, ans=INF;
    scanf("%d%d%d%d%d", &n, &l, &r, &p, &q);
    
    for(int i=1; i<=n; i++)
    {
        scanf("%d", &a[i]);
        a[i]+=a[i-1];
    }
    
    for(int i=0; i<=n; i++)
    {
        int tmp=a[i]*l+(a[n]-a[i])*r;
        
        if( i>n-i )
            tmp+=p*(i-n+i-1);
        else if( i<n-i )
            tmp+=q*(n-i-i-1);
        
        ans=min(ans, tmp);
    }
    
    printf("%d\n", ans);
}
