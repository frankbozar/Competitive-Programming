#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
const double EPS=1e-6;
const double PI=acos(-1);

struct point
{
    double x, y;
    point(double _x=0, double _y=0) : x(_x), y(_y){}
    
    bool read()
    {
        return scanf("%lf%lf", &x, &y)==2;
    }
    
    double operator-(const point& P) const
    {
        double dx=x-P.x;
        double dy=y-P.y;
        return sqrt(dx*dx+dy*dy);
    }
};

double angle(double a, double b, double c)
{
    double C=(b*b+c*c-a*a)/(2*b*c);
    return acos(max(min(C, 1.0), -1.0))*2;
}

bool f(double a, double d)
{
    return fabs(round(a/d)-a/d)<EPS;
}

int sol(const point& A, const point& B, const point& C)
{
    double a=B-C;
    double b=C-A;
    double c=A-B;
    double x=angle(a, b, c);
    double y=angle(b, c, a);
    double z=angle(c, a, b);
    
    for(int i=3; i<=1000; i++)
    {
        double d=PI*2/i;
        
        if( f(x, d) && f(y, d) && f(z, d) )
            return i;
    }
    
    return -1;
}

int main()
{
    for(point A, B, C; A.read() && B.read() && C.read(); )
        printf("%d\n", sol(A, B, C));
}

/*

-1385.736326 -146.954822
430.000292 -2041.361203
1162.736034 478.316025

0.000000 4147.000000
-4147.000000 0.000000
0.000000 -4147.000000

END

*/
