#pragma GCC optimize (3)
#include<cmath>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1<<20;
int s;

struct query
{
    int l, r, i;
    
    bool operator<(const query& Q)
    {
        return l/s!=Q.l/s ? l/s<Q.l/s : r>Q.r ;
    }
};

int main()
{
    int n, m;
    scanf("%d", &n);
    s=floor(sqrt(n));
    vector<int> a(n);
    
    for(int& x : a)
        scanf("%d", &x);
    
    scanf("%d", &m);
    vector<query> q(m);
    
    for(int i=0; i<m; i++)
    {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].l--;
        q[i].r--;
        q[i].i=i;
    }
    
    sort(q.begin(), q.end());
    vector<int> b(m), c(N, 0);
    
    for(int l=0, r=-1, v=0, i=0; i<m; i++)
    {
        while( r<q[i].r )
        {
            r++;
            
            if( c[ a[r] ]++ )
                v^=a[r];
        }
        
        while( r>q[i].r )
        {
            if( --c[ a[r] ] )
                v^=a[r];
            
            r--;
        }
        
        while( l>q[i].l )
        {
            l--;
            
            if( c[ a[l] ]++ )
                v^=a[l];
        }
        
        while( l<q[i].l )
        {
            if( --c[ a[l] ] )
                v^=a[l];
            
            l++;
        }
        
        b[ q[i].i ]=v;
    }
    
    for(int x : b)
        printf("%d\n", x);
}
