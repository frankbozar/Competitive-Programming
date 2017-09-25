#include<cstdio>
const double INF=1e100;

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, ans=0;
        scanf("%d", &n);
        double v=-INF;
        
        for(int i=1; i<=n; i++)
        {
            double a, b, c;
            scanf("%lf%lf%lf", &a, &b, &c);
            double t=c+(b*b)/(a*4);
            
            if( v<t )
                v=t, ans=i;
        }
        
        printf("%d\n", ans);
    }
}

/*

3

1
1 4 2

2
3 126 1400
2 152 208

2
3 127 1400
2 154 208

*/
