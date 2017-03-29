#include<cstdio>
typedef long long lld;
const int N=1<<11;
int a[N], b[N];

int main()
{
    for(int c=1, n; scanf("%d", &n)!=EOF; c++)
    {
        for(int i=0; i<n; i++)
            scanf("%d", &a[i]);
        
        for(int i=0; i<n; i++)
            scanf("%d", &b[i]);
        
        lld ans=0;
        
        for(int i=0; i<n; i++)
            if( a[i]==b[i] )
                ans+=a[i]*b[i];
        
        printf("Case %d: %lld\n", c, ans);
    }
}
