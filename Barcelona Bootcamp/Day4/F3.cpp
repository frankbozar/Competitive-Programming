#include<cmath>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const double INF=1e50;
const double EPS=1e-7;

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
    
    point operator-(const point& P) const
    {
        return point(x-P.x, y-P.y);
    }
    
    point operator+(const point& P) const
    {
        return point(x+P.x, y+P.y);
    }
    
    point operator/(const double s) const
    {
        return point(x/s, y/s);
    }
    
    point operator*(const double s) const
    {
        return point(x*s, y*s);
    }
    
    double operator()() const
    {
        return sqrt(x*x+y*y);
    }
};


int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n;
        scanf("%d", &n);
        vector<point> p(n);
        point s;
        
        for(int i=0; i<n; i++)
        {
            p[i].read();
            s=s+p[i];
        }
        
        s=s/n;
        s.x=floor(s.x)+0.5;
        
        for(; ; )
        {
            point t;
            double l=0;
            
            for(int i=0; i<n; i++)
            {
                point v=(p[i]-s);
                l+=1.0/v();
                t=t+p[i]/v();
            }
			//if (fabs(old_l-l)/old_l < EPS)
            if( (s-t/l)()<EPS )
                break;
            s=t/l;
        }
        
        s.show();
    }
}

/*

1
3
-3 0
0 3
3 0


1
5
0 0
0 2
2 0
2 2
1 1

*/
