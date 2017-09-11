#include<cmath>
#include<cstdio>

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, k=0;
        double m;
        scanf("%d%lf", &n, &m);
        
        for(int i=0; i<n; i++)
        {
            int x;
            scanf("%d", &x);
            k+=x>=50;
        }
        
        printf(k>=ceil(n*m) ? "YES\n" : "NO\n");
    }
}
