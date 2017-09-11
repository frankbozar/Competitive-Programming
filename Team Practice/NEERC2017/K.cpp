#include<cstdio>
int md[13]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int f()
{
    int y, m, d;
    scanf("%d%d%d", &d, &m, &y);
    return y*365+md[m-1]+d;
}

int main()
{
    freopen("king.in", "rb", stdin);
    freopen("king.out", "wb", stdout);
    
    for(int i=1; i<=12; i++)
        md[i]+=md[i-1];
    
    int t=f(), ans=-1, d=-1, n;
    scanf("%d", &n);
    
    for(int i=1; i<=n; i++)
    {
        int s=f();
        
        if( d<s && t-s>=365*18 )
            d=s, ans=i;
    }
    
    printf("%d\n", ans);
}
