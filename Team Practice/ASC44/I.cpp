#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;

struct exam
{
    lld d, p;
    int i;
    
    bool operator<(const exam& E) const
    {
        return d<E.d;
    }
};

struct hike
{
    lld l, r;
    
    bool operator<(const hike& H) const
    {
        return l<H.l;
    }
};

struct data
{
    lld p;
    int i;
    data(lld _p=0, int _i=0) : p(_p), i(_i){}
    
    bool operator<(const data& D) const
    {
        return p<D.p;
    }
};

int main()
{
    freopen("intelligent.in", "rb", stdin);
    freopen("intelligent.out", "wb", stdout);
    
    for(int n, m; scanf("%d", &n) && n>0; )
    {
        vector<exam> e(n);
        
        for(int i=0; i<n; i++)
        {
            scanf("%lld%lld", &e[i].d, &e[i].p);
            e[i].i=i;
        }
        
        scanf("%d", &m);
        vector<hike> h(m);
        
        for(int i=0; i<m; i++)
            scanf("%lld%lld", &h[i].l, &h[i].r);
        
        sort(e.begin(), e.end());
        sort(h.begin(), h.end());
        priority_queue<data> PQ;
        lld d=0;
        
        for(int j=0, i=0; i<n; i++)
        {
            for(; j<m && h[j].r<e[i].d; j++)
                d+=h[j].r-h[j].l+1;
            
            if( e[i].d>=d+e[i].p+1 )
            {
                PQ.push(data(e[i].p, e[i].i));
                d+=e[i].p+1;
            }
            else if( !PQ.empty() && PQ.top().p>e[i].p )
            {
                d-=PQ.top().p;
                PQ.pop();
                d+=e[i].p;
                PQ.push(data(e[i].p, e[i].i));
            }
        }
        
        printf("%lu\n", PQ.size());
        
        for(; !PQ.empty(); PQ.pop())
            printf(PQ.size()==1 ? "%d\n" : "%d ", PQ.top().i+1);
    }
}
