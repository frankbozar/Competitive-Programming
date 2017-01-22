#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;
const lld INF=1<<30;
#define polld pair<lld,lld>
#define x first
#define y second

inline lld square(lld n=0, lld m=0)
{
    return n*n+m*m;
}

bool check(const vector<polld>& p, const vector<lld>& mY, const vector<lld>& MY, lld n, lld v)
{
    for(lld my=INF, My=-INF, j=0, i=0; i<n; i++)
    {
        j=max(j, i+1);
        
        while( j<n && square(p[j].x-p[i].x)<=v )
            j++;
        
        lld x=p[i].x;
        lld X=p[j-1].x;
        lld y=min(my, mY[j]);
        lld Y=max(My, MY[j]);
        
        if( square(Y-y)<=v && square(x, y)<=v && square(x, Y)<=v && square(X, y)<=v && square(X, Y)<=v )
            return true;
        
        my=min(my, p[i].y);
        My=max(My, p[i].y);
    }
    
    return square(MY.front()-mY.front())<=v || square(p.back().x-p.front().x)<=v ;
}

int main()
{
    lld n;
    scanf("%lld", &n);
    vector<polld> p(n);
    
    for(lld i=0; i<n; i++)
        scanf("%lld%lld", &p[i].x, &p[i].y);
    
    sort(p.begin(), p.end());
    vector<lld> mY(n+1, INF), MY(n+1, -INF);
    
    for(lld i=n-1; i>=0; i--)
    {
        mY[i]=min(mY[i+1], p[i].y);
        MY[i]=max(MY[i+1], p[i].y);
    }
    
    lld ans=INF;
    
    for(lld l=0, r=square(INF); l<r; )
    {
        lld m=(l+r)>>1;
        
        if( check(p, mY, MY, n, m) )
            r=ans=m;
        else
            l=m+1;
    }
    
    printf("%lld\n", ans);
}
