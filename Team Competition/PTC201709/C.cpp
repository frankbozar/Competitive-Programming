#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;

struct point
{
    lld x, y;
    point(lld _x=0, lld _y=0) : x(_x), y(_y){}
    
    void read()
    {
        scanf("%lld%lld", &x, &y);
    }
    
    point operator-(const point& P)
    {
        return point(x-P.x, y-P.y);
    }
    
    lld operator*(const point& P)
    {
        return x*P.y-y*P.x;
    }
    
    bool operator<(const point& P)
    {
        return x==P.x ? y<P.y : x<P.x ;
    }
};

lld hull(vector<point>& p)
{
    int n=p.size(), k=0;
    vector<point> h(n<<1);
    sort(p.begin(), p.end());
    
    for(int i=0; i<n; i++)
    {
        for(; k>=2 && (h[k-1]-h[k-2])*(p[i]-h[k-1])<=0; k--);
        h[k++]=p[i];
    }
    
    for(int t=k, i=n-2; i>=0; i--)
    {
        for(; k>t && (h[k-1]-h[k-2])*(p[i]-h[k-1])<=0; k--);
        h[k++]=p[i];
    }
    
    lld ans=0;
    
    for(int i=1; i<k; i++)
        ans+=h[i-1]*h[i];
    
    return ans<0 ? -ans : ans ;
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
        
        lld ans=hull(p);
        printf(ans&1 ? "%lld.50\n" : "%lld.00\n", ans>>1);
    }
}

/*

2

5
0 0
1 1
2 0
0 2
2 2

3
0 0
3 0
0 1

*/
