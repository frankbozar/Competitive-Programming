#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
const double PI=acos(1);
const double EPS=1e-3;

struct point
{
    double x, y;
    point(double _x=0, double _y=0) : x(_x), y(_y){}
    
    void read()
    {
        scanf("%lf%lf", &x, &y);
    }
    
    double operator^(const point& P) const
    {
        return x*P.y-y*P.x;
    }
    
    double operator&(const point& P) const
    {
        return x*P.x+y*P.y;
    }
    
    point operator-(const point& P) const
    {
        return point(x-P.x, y-P.y);
    }
    
    bool operator==(const point& P) const
    {
        return fabs(x-P.x)<EPS && fabs(y-P.y)<EPS ;
    }
    
    double len() const
    {
        return sqrt(x*x+y*y);
    }
    
    point trans(double t, double a, double dx, double dy) const
    {
        return point(a*(x*cos(t)-y*sin(t))+dx, a*(x*sin(t)+y*cos(t))+dy);
    }
};

bool solve(double& t, double& a, double& x, double& y, int n, const vector<point>& p, const vector<point>& q)
{
    int i=rand()%n, j=rand()%n, c=0;
    point u=p[i]-p[j];
    point v=q[i]-q[j];
    t=acos((u&v)/(u.len()*v.len()))*((u^v)<0 ? -1 : 1);
    a=v.len()/u.len();
    x=(q[i]-p[i].trans(t, a, 0, 0)).x;
    y=(q[j]-p[j].trans(t, a, 0, 0)).y;
    
    for(int k=0; k<n; k++)
        c+=p[k].trans(t, a, x, y)==q[k];
    
    return a<10 && c<<1>=n;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<point> p(n), q(n);
    
    for(int i=0; i<n; i++)
    {
        p[i].read();
        q[i].read();
    }
    
    if( n<=2 )
        printf("0\n1\n%.10f %.10f\n", (q[0]-p[0]).x, (q[0]-p[0]).y);
    else
    {
        double t, a, x, y;
        while( !solve(t, a, x, y, n, p, q) );
        printf("%.10f\n%.10f\n%.10f %.10f\n", t, a, x, y);
    }
}
