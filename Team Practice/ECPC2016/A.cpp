#include<cstdio>

int main()
{
    freopen("powers.in", "rb", stdin);
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, ans=0;
        
        for(scanf("%d", &n); n>0; n--)
        {
            int b, x;
            scanf("%d%d", &b, &x);
            
            if( b&1 )
                ans^=x&1;
            else if( x%(b+1)==b )
                ans^=2;
            else
                ans^=x%(b+1)&1;
        }
        
        printf("%d\n", ans==0 ? 2 : 1);
    }
}
