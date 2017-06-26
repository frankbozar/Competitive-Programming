#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
typedef long long lld;
const double EPS=1e-6;
#define point pair<lld,lld>
#define x first
#define y second

lld cross(const point& A, const point& B)
{
    return A.x*B.y-A.y*B.x;
}

lld area(const point& A, const point& B, const point& C)
{
    return abs(cross(A, B)+cross(B, C)+cross(C, A));
}

bool in(const point& P, const point& A, const point& B, const point& C)
{
    return area(P, A, B)+area(P, B, C)+area(P, C, A)==area(A, B, C);
}

double dist(const point& P, const point& Q)
{
    lld dx=P.x-Q.x;
    lld dy=P.y-Q.y;
    return sqrt(dx*dx+dy*dy);
}

bool in(const point& P, const point& X, const point& Y)
{
    return fabs(dist(P, X)+dist(P, Y)-dist(X, Y))<EPS;
}

int main()
{
    int n, x=0, y=0, z=0;
    scanf("%d", &n);
    point A(0, 0), B(0, 0), C(0, 0);
    
    for(int i=1; i<=n; i++)
    {
        point P;
        scanf("%lld%lld", &P.x, &P.y);
        
        if( x==0 )
            x=i, A=P;
        else if( y==0 )
            y=i, B=P;
        else if( z==0 )
            z=i, C=P;
        else if( in(A, B, C) && (area(P, B, C)>0 || (!in(B, P, A) && !in(C, P, A))) )
            y=i, B=P;
        else if( in(B, C, A) && (area(P, C, A)>0 || (!in(C, P, B) && !in(A, P, B))) )
            z=i, C=P;
        else if( in(C, A, B) && (area(P, A, B)>0 || (!in(A, P, C) && !in(B, P, C))) )
            x=i, A=P;
        else if( in(P, B, C) )
            y=i, B=P;
        else if( in(P, C, A) )
            z=i, C=P;
        else if( in(P, A, B) )
            x=i, A=P;
        else if( in(P, A, B, C) && area(A, B, C)>0 )
            x=i, A=P;
    }
    
    printf("%d %d %d\n", x, y, z);
}
