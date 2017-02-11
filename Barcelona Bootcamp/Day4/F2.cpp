#include<cmath>
#include<cstdio>
#include<vector>
using namespace std;
const double INF=1e10;
const double EPS=1e-8;

struct point
{
    double x, y;
    point(double _x=0, double _y=0) : x(_x), y(_y){}
    
    void read()
    {
        scanf("%lf%lf", &x, &y);
    }
    
    void show()
    {
        printf("%f %f\n", x, y);
    }
    
    double operator-(const point& P) const
    {
        double dx=x-P.x;
        double dy=y-P.y;
        return sqrt(dx*dx+dy*dy);
    }
};

double solve(const vector<point>& p, const point& a)
{
    double ans=0;
    
    for(const point& P : p)
        ans+=a-P;
    
    return ans;
}

pair<double, double> solve(const vector<point>& p, double x)
{
    double len=INF*INF, ans=0;
    
    for(double l=-INF, r=INF; r-l>EPS; )
    {
        double n=(l+r*2)/3;
        double m=(l*2+r)/3;
        double u=solve(p, point(x, n));
        double v=solve(p, point(x, m));
        
        if( u<v )
        {
            l=m;
            
            if( len>u )
            {
                len=u;
                ans=m+EPS;
            }
        }
        else
        {
            r=n;
            
            if( len>v )
            {
                len=v;
                ans=m-EPS;
            }
        }
    }
    
    return pair<double, double>(len, ans);
}

point solve(const vector<point>& p)
{
    double len=INF*INF;
    point ans;
    
    for(double l=-INF, r=INF; r-l>EPS; )
    {
        double n=(l+r*2)/3;
        double m=(l*2+r)/3;
        pair<double, double> u=solve(p, n);
        pair<double, double> v=solve(p, m);
        
        if( u.first<v.first )
        {
            l=m;
            
            if( len>u.first )
            {
                len=u.first;
                ans=point(m+EPS, u.second);
            }
        }
        else
        {
            r=n;
            
            if( len>v.first )
            {
                len=v.first;
                ans=point(m-EPS, v.second);
            }
        }
    }
    
    return ans;
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n;
        scanf("%d", &n);
        vector<point> p(n);
        
        for(int i=0; i<n; i++)
            p[i].read();
        
        solve(p).show();
    }
}

/*
 
2

3
-3 0
0 3
3 0

5
0 0
0 2
2 0
2 2
1 1

*/
