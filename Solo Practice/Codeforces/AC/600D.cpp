#include<cmath>
#include<cstdio>
using namespace std;
typedef long double lld;
const lld PI=acos((lld)-1);

struct circle
{
    lld x, y, r;
    
    void read()
    {
        scanf("%Lf%Lf%Lf", &x, &y, &r);
    }
    
    lld operator+(const circle& C) const
    {
        const circle& D=*this;
        lld d=C-D;
        
        if( D.r>C.r )
            return C+D;
        else if( d>=C.r+D.r )
            return 0;
        else if( d<=C.r-D.r )
            return D();
        
        lld t=(C.r*C.r-D.r*D.r+d*d)/(2*d);
        
        if( t<=d )
            return C(t)+D(d-t);
        else
            return C(t)+D()-D(t-d);
    }
    
    lld operator-(const circle& C) const
    {
        lld dx=x-C.x;
        lld dy=y-C.y;
        return sqrt(dx*dx+dy*dy);
    }
    
    lld operator()() const
    {
        return PI*r*r;
    }
    
    lld operator()(lld t) const
    {
        lld a=acos(t/r);
        return r*r*a-r*t*sin(a);
    }
};

int main()
{
    circle C, D;
    C.read();
    D.read();
    printf("%.20Lf\n", C+D);
}
