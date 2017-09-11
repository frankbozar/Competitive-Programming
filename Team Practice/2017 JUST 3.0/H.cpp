#include<cmath>
#include<cstdio>

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        double a, b, c, d;
        scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
        printf(log(a)*b>log(c)*d ? ">\n" : "<\n");
    }
}
