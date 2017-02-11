#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
const double INF=1e30;
const double EPS=1e-2;
const int MIT=20;

double length(double x, double y, double v)
{
    return sqrt(x*x+y*y)/v;
}

double solve(double a, double b, double x, double y, double h)
{
    double ans=INF;
    int cnt=0;
    
    for(double l=0, r=h; r-l>EPS*2 && cnt<MIT; cnt++)
    {
        double m=(l+r)*.5;
        double p=length(a, m+EPS, x)+length(b, h-(m+EPS), y);
        double q=length(a, m-EPS, x)+length(b, h-(m-EPS), y);
        
        if( p<q )
        {
            l=m;
            ans=min(ans, p);
        }
        else
        {
            r=m;
            ans=min(ans, q);
        }
    }
    
    return ans;
}

double solve(double a, double b, double c, double x, double y, double z, double h)
{
    double ans=INF;
    int cnt=0;
    
    for(double l=0, r=h; r-l>EPS*2 && cnt<MIT; cnt++)
    {
        double m=(l+r)*.5;
        double p=length(a, m+EPS, x)+solve(b, c, y, z, h-(m+EPS));
        double q=length(a, m-EPS, x)+solve(b, c, y, z, h-(m-EPS));
        
        if( p<q )
        {
            l=m;
            ans=min(ans, p);
        }
        else
        {
            r=m;
            ans=min(ans, q);
        }
    }
    
    return ans;
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        double h, a, b, c, x, y, z;
        scanf("%lf%lf%lf%lf%lf%lf%lf", &h, &a, &b, &c, &x, &y, &z);
        printf("%f\n", solve(a, b, c, x, y, z, h));
    }
}

/*

2
10 3 4 3 1 1 1
21 5 12 4 4 3 4

*/
