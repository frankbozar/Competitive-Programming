#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1LL<<31;

struct point
{
    lld x, y;
    point(lld _x=0, lld _y=0) : x(_x), y(_y){}
    
    void operator()(lld w, lld h)
    {
        lld t=x;
        x=y;
        y=h-t+1;
    }
    
    bool operator<(const point& P) const
    {
        return x<P.x;
    }
};

bool ok(vector<point>& a, lld w, lld h, lld t)
{
    lld p[4];
    
    for(int i=0; i<4; i++)
    {
        sort(a.begin(), a.end());
        map<lld, int> M;
        
        for(const point& P : a)
        {
            
            
            
            
            
        }
        
        for(point& P : a)
            P(w, h);
        
        swap(w, h);
    }
    
}

int main()
{
    lld w, h, n, ans=-1;
    scanf("%lld%lld%lld", &w, &h, &n);
    vector<point> a(n);
    
    for(point& P : a)
        scanf("%lld%lld", &P.x, &P.y);
    
    for(lld l=0, r=INF; l<r; )
    {
        lld m=(l+r)>>1;
        
        if( ok(a, w, h, m) )
            r=ans=m;
        else
            l=m+1;
    }
    
    printf("%lld\n", ans);
}
