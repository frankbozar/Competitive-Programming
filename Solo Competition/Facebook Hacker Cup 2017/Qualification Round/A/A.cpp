#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
const double pi=atan(1)*4;

bool check(double p, double x, double y)
{
    x-=50;
    y-=50;
    double l=sqrt(x*x+y*y);
    
    if( p==0 || l>50 )
        return false;
    else if( l==0 )
        return true;
    
    double a=acos(min(1.0, max(-1.0, y/l)));
    
    if( x<0 )
        a=pi*2-a;
    
    return a<=pi*2*p/100 ;
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        double p, x, y;
        scanf("%lf%lf%lf", &p, &x, &y);
        printf("Case #%d: %s\n", cases, check(p, x, y) ? "black" : "white");
    }
}
