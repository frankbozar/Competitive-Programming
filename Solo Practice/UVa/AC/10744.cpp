#include<cmath>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const double PI=acos(-1);
const double EPS=1e-6;

struct point
{
    double x, y;
    point(double _x=0, double _y=0) : x(_x), y(_y){}
    
    bool read()
    {
        return scanf("%lf%lf", &x, &y)==2;
    }
    
    point operator-(const point& P) const
    {
        return point(x-P.x, y-P.y);
    }
    
    double operator()() const
    {
        double t=mcos(x/sqrt(x*x+y*y));
        return y<0 ? PI-t : t ;
    }
    
    point operator()(double s) const
    {
        return point(cos(s)*x-sin(s)*y, sin(s)*x+cos(s)*y);
    }
    
    static double mcos(double x)
    {
        return acos(max(min(x, 1.0), -1.0));
    }
};

double sol(vector<point> p, double s)
{
    vector<double> y;
    
    for(const point& P : p)
        y.push_back(P(-s).y);
    
    sort(y.begin(), y.end());
    int n=y.size();
    double ans=0;
    
    for(int i=0; i<n-i-1; i++)
        ans+=y[n-i-1]-y[i];
    
    return ans;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<point> p(n);
    
    for(int i=0; i<n; i++)
        p[i].read();
    
    for(int cases=1; cases<=m; cases++)
    {
        point A, B;
        A.read();
        B.read();
        printf("Case %d: %.0f\n", cases, sol(p, (A-B)()));
    }
}

/*

6 2
1 1
1 10
20 12
2 4
1 1
2 4
10 10 11 11
2 3 3 4

*/
