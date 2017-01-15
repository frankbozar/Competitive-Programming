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
};

int main()
{
    int n;
    scanf("%d", &n);
    set S(n+1);
    int ans=n;
    
    for(int i=1; i<=n; i++)
    {
        int p;
        scanf("%d", &p);
        
        if( S.join(i, p) )
            ans--;
    }
    
    printf("%d\n", ans);
}
