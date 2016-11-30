#include<cstdio>

int main()
{
    double x, y;
    scanf("%lf%lf", &x, &y);
    int n;
    
    for(scanf("%d", &n); n>0; n--)
    {
        double l, r, v;
        scanf("%lf%lf%lf", &l, &r, &v);
        y+=(r-l)*(v-1);
    }
    
    printf("%f\n", x/y);
}

/*

100 140
1
40 90 0.2000000000

100 100
3
0 20 2.0000000000
50 100 0.1000000000
20 50 0.2000000000

*/