#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define edge pair<int,int>
#define u first
#define v second
int vc;
vector<edge> e;

void solve(vector<int> a, int l, int r)
{
    if( l>=r-1 )
        return ;
    
    int m=(l+r)>>1;
    vector<edge> b;
    
    for(int i=m; i<r; i++)
    {
        b.push_back(edge(a[i], vc+1));
        e.push_back(edge(++vc, i+1));
    }
    
    sort(b.begin(), b.end());
    
    for(int i=m+1; i<r; i++)
        e.push_back(edge(b[i-m].v, b[i-m-1].v));
    
    for(int i=l; i<m; i++)
    {
        int it=lower_bound(b.begin(), b.end(), edge(a[i], 0))-b.begin()-1;
        
        if( it>=0 )
            e.push_back(edge(i+1, b[it].v));
    }
    
    solve(a, l, m);
    solve(a, m, r);
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> a(n);
    vc=n;
    
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);
    
    solve(a, 0, n);
    printf("%d %lu\n", vc, e.size());
    
    for(edge& E : e)
        printf("%d %d\n", E.u, E.v);
}

/*

4
3 4 1 2

*/
