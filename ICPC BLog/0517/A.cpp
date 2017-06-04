#include<cstdio>
typedef long long lld;

int main()
{
    int n, ans=0;
    scanf("%d", &n);
    
    for(lld p=1LL<<40; n>0; n--)
    {
        int x;
        scanf("%d", &x);
        ans+=p!=x;
        p=x;
    }
    
    printf("%d\n", ans);
}
