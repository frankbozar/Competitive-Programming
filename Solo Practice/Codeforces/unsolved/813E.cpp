#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N=100001;

void f(const vector<int>& a, int n, int m, int k)
{
    vector<int> c(N, 0);
    
    for(int p=0; k>0; k--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        l=(l+p)%n+1;
        r=(r+p)%n+1;
        
        if( l>r )
            swap(l, r);
        
        p=0;
        
        for(int i=l; i<=r; i++)
            if( ++c[ a[i] ]<=m )
                p++;
        
        for(int i=l; i<=r; i++)
            c[ a[i] ]=0;
        
        printf("%d\n", p);
    }
}

void g(const vector<int>& a, int n, int m, int k)
{
    vector<int> b, c(N, 0);
    vector<vector<int>> d(N);
    
    for(int i=1; i<=n; i++)
        c[i]++;
    
    for(int i=1; i<=n; i++)
    {
        if( c[i]>=m )
        {
            b.push_back(i);
            d[i].assign(n+1, 0);
        }
    }
    
    for(int i=1; i<=n; i++)
    {
        if( c[ a[i] ]>=m )
            d[ a[i] ][i]=1;
        
        for(int x : b)
            d[x][i]+=d[x][i-1];
    }
    
    for(int p=0; k>0; k--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        l=(l+p)%n+1;
        r=(r+p)%n+1;
        
        if( l>r )
            swap(l, r);
        
        p=r-l+1;
        
        for(int x : b)
            p-=max(d[x][r]-d[x][l-1]+1-m, 0);
        
        printf("%d\n", p);
    }
}

int main()
{
    int n, m, k;
    scanf("%d%d", &n, &m);
    vector<int> a(n+1, 0);
    
    for(int i=1; i<=n; i++)
        scanf("%d", &a[i]);
    
    scanf("%d", &k);
    n/m>m ? f(a, n, m, k) : g(a, n, m, k) ;
}
