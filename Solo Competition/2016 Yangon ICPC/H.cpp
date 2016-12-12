#include<cmath>
#include<cstdio>
#include<set>
#include<map>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
const double INF=1e50;
const double EPS=1e-8;
char buf[1<<20];

struct point
{
    double x, y;
    point(double _x=0, double _y=0) : x(_x), y(_y){}
    
    void read()
    {
        scanf("%lf%lf", &x, &y);
    }
    
    bool operator<(const point& P) const
    {
        return fabs(x-P.x)>EPS ? x<P.x : y<P.y-EPS;
    }
    
    double operator()() const
    {
        return sqrt(x*x+y*y);
    }
    
    point operator-(const point& P) const
    {
        return point(x-P.x, y-P.y);
    }
    
    point operator/(double s) const
    {
        return point(x/s, y/s);
    }
};

struct data
{
    int n;
    string name;
    vector<point> p;
    double scale;
    
    data(const char* s, int _n) : n(_n), name(s), p(n)
    {
        scale=INF;
        
        for(int i=0; i<n; i++)
        {
            p[i].read();
            
            for(int j=0; j<i; j++)
                scale=min(scale, (p[i]-p[j])());
        }
        
        norm();
    }
    
    data lr() const
    {
        data ans=*this;
        
        for(int i=0; i<n; i++)
            ans.p[i].x*=-1;
            
        ans.norm();
        return ans;
    }

    data rot() const
    {
        data ans=*this;
        
        for(int i=0; i<n; i++)
        {
            swap(ans.p[i].x, ans.p[i].y);
            ans.p[i].x*=-1;
        }
        
        ans.norm();
        return ans;
    }
    
    bool operator<(const data& D) const
    {
        return p<D.p;
    }
    
    void norm()
    {
        sort(p.begin(), p.end());
        
        for(int i=n-1; i>=0; i--)
            p[i]=p[i]-p[0];
        
        for(int i=n-1; i>=0; i--)
            p[i]=p[i]/p[1]();
    }
};

int main()
{
    int n, m;
    scanf("%*s%d", &n);
    vector<data> f, s;
    
    for(int i=0; i<n; i++)
    {
        int l;
        scanf("%s%d", buf, &l);
        f.push_back(data(buf, l));
    }
    
    map<data, set<int>> M;
    scanf("%*s%d", &m);
        
    for(int i=0; i<m; i++)
    {
        int l;
        scanf("%s%d", buf, &l);
        s.push_back(data(buf, l));
        
        for(int j=0; j<4; j++)
        {
            M[s[i]].insert(i);
            M[s[i].lr()].insert(i);
            s[i]=s[i].rot();
        }
    }
    
    for(int i=0; i<n; i++)
    {
        const set<int>& S=M[f[i]];
        printf("%s", f[i].name.c_str());
        
        for(set<int>::iterator it=S.begin(); it!=S.end(); ++it)
            if( s[*it].scale<=f[i].scale+EPS )
                printf(" %s", s[*it].name.c_str());
        
        printf("\n");
    }
}

/*

F 1
S5 5
6 2
6.5 3
6 4
7 4
7 2
S 1
F2 5
10 1
10 3
12 2
14 3
14 1

F 1
F1 5
2 6
4 4
2 8
6 8
6 6
S 1
S1 5
8 6
8 7
9 8
10 7
10 6

F 2
F1 5
2 6
4 4
2 8
6 8
6 6
F2 5
10 1
10 3
12 2
14 3
14 1
S 5
S1 5
8 6
8 7
9 8
10 7
10 6
S2 5
13 7
13 9
14 9
13.5 8
14 7
S3 5
7 10
7 11
9 11
8 10.5
9 10
S4 5
1 1.5
1 2
2 2
2 1.5
1.5 1
S5 5
6 2
6.5 3
6 4
7 4
7 2

*/