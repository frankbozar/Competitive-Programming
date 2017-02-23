#include<cstdio>
#include<vector>
using namespace std;

struct set
{
    vector<int> p;
    set(int n) : p(n+1, -1){}
    
    int find(int x)
    {
        return p[x]<0 ? x : p[x]=find(p[x]);
    }
    
    bool join(int x, int y)
    {
        x=find(x);
        y=find(y);
        
        if( x==y )
            return false;
        
        p[x]=y;
        return true;
    }
    
    bool same(int x, int y)
    {
        return find(x)==find(y);
    }
};

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> a(n+1, 0);
    vector<vector<int>> b(n+1);
    set S(m<<1);
    
    for(int i=1; i<=n; i++)
        scanf("%d", &a[i]);
    
    for(int i=0; i<m; i++)
    {
        int k;
        
        for(scanf("%d", &k); k>0; k--)
        {
            int x;
            scanf("%d", &x);
            b[x].push_back(i);
            
            if( b[x].size()==2 )
            {
                if( a[x] )
                {
                    S.join(b[x][0], b[x][1]);
                    S.join(b[x][0]+m, b[x][1]+m);
                }
                else
                {
                    S.join(b[x][0]+m, b[x][1]);
                    S.join(b[x][0], b[x][1]+m);
                }
                
                if( S.same(b[x][0], b[x][0]+m) || S.same(b[x][1], b[x][1]+m) )
                {
                    printf("NO\n");
                    return 0;
                }
            }
        }
    }
    
    printf("YES\n");
}
