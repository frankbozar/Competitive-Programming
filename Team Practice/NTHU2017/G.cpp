#include<cmath>
#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
const int N=100100;
int s, a[N], b[N], c[N]={0};

struct query
{
    int l, r, i;
    query(int _l=0, int _r=0, int _i=0) : l(_l), r(_r), i(_i){}
    
    bool operator<(const query& Q) const
    {
        return l/s==Q.l/s ? r<Q.r : l<Q.l ;
    }
} q[N];

int main()
{
    for(int n, m; scanf("%d%d", &n, &m)!=EOF; )
    {
        s=sqrt(n);
        map<int, int> M;
        
        for(int i=0; i<n; i++)
        {
            scanf("%d", &a[i]);
            
            if( M.find(a[i])==M.end() )
            {
                int t=M.size();
                M[ a[i] ]=t;
            }
            
            a[i]=M[ a[i] ];
        }
        
        for(int i=0; i<m; i++)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            q[i]=query(l-1, r, i);
        }
        
        sort(q, q+m);
        
        for(int t=0, l=0, r=0, i=0; i<m; i++)
        {
            while( r<q[i].r )
                t+=c[ a[r++] ]++==0;
            
            while( r>q[i].r )
                t-=--c[ a[--r] ]==0;
            
            while( l<q[i].l )
                t-=--c[ a[l++] ]==0;
            
            while( l>q[i].l )
                t+=c[ a[--l] ]++==0;
            
            b[ q[i].i ]=t;
        }
        
        for(int i=0; i<n; i++)
            c[ a[i] ]=0;
        
        for(int i=0; i<m; i++)
            printf("%d\n", b[i]);
    }
}
