#include<cstdio>
#include<cstdlib>
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
    
    point operator-(const point& P) const
    {
        return point(x-P.x, y-P.y);
    }
    
    lld operator*(const point& P) const
    {
        return x*P.y-y*P.x;
    }
    
    bool operator<(const point& P) const
    {
        return x==P.x ? y<P.y : x<P.x ;
    }
};

lld area(const point& A, const point& B, const point& C)
{
    return abs(A*B+B*C+C*A);
    
    
}

lld sol(vector<point>& p)
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
    
    n=k-1;
    lld ans=0;
    
    for(int i=0; i<n; i++)
    {
        for(int j=(i+1)%n, k=i, l=j; j!=i; j=(j+1)%n)
        {
            lld s0=area(h[i], h[j], h[k]);
            lld s1=area(h[i], h[j], h[l]);
            
            for(lld t0; k!=j && s0<(t0=area(h[i], h[j], h[(k+1)%n])); k=(k+1)%n)
                s0=t0;
            
            for(lld t1; l!=i && s1<(t1=area(h[i], h[j], h[(l+1)%n])); l=(l+1)%n)
                s1=t1;
            
            ans=max(ans, s0+s1);
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
        
        lld ans=sol(p);
        printf(ans&1 ? "%lld.5\n" : "%lld\n", ans>>1);
    }
}

/*

3

6
0 0
3 7
10 0
11 6
0 10
10 10

5
0 0
-2 -2
3 -2
0 1
0 3

10
3 1
4 1
5 9
2 6
5 3
5 8
9 7
9 3
2 3
8 4

*/
