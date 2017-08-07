#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
const double EPS=1e-6;

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
    
    point operator+(const point& P) const
    {
        return point(x+P.x, y+P.y);
    }
    
    point operator*(const double s) const
    {
        return point(x*s, y*s);
    }
    
    point operator/(const double s) const
    {
        return point(x/s, y/s);
    }
    
    void show() const
    {
        printf("%.10f %.10f\n", x, y);
    }
};

double same(double x, double y)
{
    return fabs(x-y)<EPS;
}

double mcos(double x)
{
    return acos(max(min(x, 1.0), -1.0));
}

double angle(double a, double b, double c)
{
    return mcos((b*b+c*c-a*a)/(2*b*c));
}

int main()
{
    for(point A, B, C; A.read() && B.read() && C.read(); )
    {
        double a=B-C;
        double b=C-A;
        double c=A-B;
        
        if( same(a+b, c) || same(b+c, a) || same(c+a, b) )
            printf("Impossible\n");
        else
        {
            double p=sin(angle(a, b, c)*2);
            double q=sin(angle(b, c, a)*2);
            double r=sin(angle(c, a, b)*2);
            double s=p+q+r;
            point P=(A*p+B*q+C*r)/s;
            P.show();
        }
    }
}

/*

-4 0
0 4
4 0
1 2
2 4
4 8

*/
