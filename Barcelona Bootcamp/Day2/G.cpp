#include<cmath>
#include<cstdio>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
const double EPS=1e-8;

struct point
{
    double x, y;
    point(double _x=0, double _y=0) : x(_x), y(_y){}
    
    bool operator<(const point& P) const
    {
        return fabs(x-P.x)<=EPS ? y<P.y-EPS : x<P.x ;
    }
};

struct para
{
    double a, b;
    
    void read()
    {
        scanf("%lf%lf", &a, &b);
        b+=a*a;
        a*=-2;
    }
    
    vector<point> operator*(const para& P)
    {
        vector<point> ans;
        double da=a-P.a;
        double db=b-P.b;
        
        if( fabs(da)>EPS )
        {
            double x=-db/da;
            double y=x*x+a*x+b;
            ans.push_back(point(x, y));
        }
        
        return ans;
    }
    
    bool operator<(const para& P) const
    {
        return fabs(a-P.a)<=EPS ? b<P.b-EPS : a<P.a ;
    }
};

int main()
{
    int n;
    scanf("%d", &n);
    set<para> S;
    
    for(int i=0; i<n; i++)
    {
        para p;
        p.read();
        S.insert(p);
    }
    
    vector<para> a(S.begin(), S.end());
    set<point> T;
    vector<set<point>> t(n);
    n=a.size();
    int e=0;
    
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            vector<point> p=a[i]*a[j];
            
            if( !p.empty() )
            {
                t[i].insert(p[0]);
                t[j].insert(p[0]);
            }
        }
    }
    
    for(int i=0; i<n; i++)
    {
        e+=t[i].size()+1;
        
        for(const point& p : t[i])
            T.insert(p);
    }
    
    int v=T.size();
    printf("%d\n", 1+e-v);
}

/*

4
0 0
1 1
0 1
2 1

3
2 4
3 4
2 4

*/
