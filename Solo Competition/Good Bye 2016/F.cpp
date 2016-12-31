#include<cstdio>
#include<cstring>
#include<map>
using namespace std;

struct data
{
    int k, c, b[3];
    
    data()
    {
        memset(this, 0, sizeof(data));
    }
    
    void read()
    {
        scanf("%d", &k);
        
        for(int i=0; i<k; i++)
            scanf("%d", &b[i]);
    }
};

map<int, data> M;
int n, ans;

data query(int x)
{
    if( M.find(x)!=M.end() )
        return M[x];
    
    printf("? %d\n", x);
    data D;
    D.read();
    
    if( D.k==2 )
        ans=x;
    
    M[x]=D;
    return D;
}

int fh(int x, int d=0)
{
    if( d>n-2 )
        return -1;
    
    data D=query(x);
    
    if( D.k==1 )
        return n;
    else if( D.k==2 )
        return 1;
    
    int h=-1;
    
    for(int i=0; i<D.k-1; i++)
    {
        if( fh(D.b[i], d+1)<0 )
            continue;
    }
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int x=1;
        scanf("%d", &n);
        M.clear();
        ans=-1;
        int h=fh(a);
        
        
        
        
        
        printf("! %d\n", ans);
    }
}
