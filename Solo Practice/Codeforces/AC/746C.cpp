#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
const double EPS=1E-6;

double solve(double s, double x, double y, double u, double v, double p, double d)
{
    double dir=fabs(y-x)/u, tra=0;
    
    if( u>=v )
        return dir;
    
    if( p>x )
    {
        if( d>0 )
        {
            tra=(s-p+s-x)/(u+v);
            p=x+tra*u;
            d=-1;
        }
        else
        {
            tra=(p-x)/(u+v);
            p=x+tra*u;
        }
    }
    else if( p<x )
    {
        if( d>0 )
        {
            tra=(x-p)/(u+v);
            p=x-tra*u;
        }
        else
        {
            tra=(p+x)/(u+v);
            p=x-tra*u;
            d=1;
        }
    }
    
    if( p>y )
    {
        if( d>0 )
            tra+=(s-p+s-y)/v;
        else
            tra+=(p-y)/v;
    }
    else
    {
        if( d>0 )
            tra+=(y-p)/v;
        else
            tra+=(p+y)/v;
    }
    
    return min(dir, tra);
}

int main()
{
    double s, x, y, u, v, p, d;
    scanf("%lf%lf%lf%lf%lf%lf%lf", &s, &x, &y, &u, &v, &p, &d);
    printf("%.0f\n", solve(s, x, y, 1/v, 1/u, p, d));
}