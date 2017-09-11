#include<cstdio>
#include<map>
using namespace std;

int f(int x)
{
    if( x==1 )
        return 0;
    
    static map<int, int> M;
    
    if( M.find(x)==M.end() )
    {
        int b=0;
        
        for(int i=1; 1<<i<=x; i++)
            b|=1<<f((x>>i)|((x&((1<<i)-1))));
        
        M[x]=30;
        
        for(int i=29; i>=0; i--)
            if( !((b>>i)&1) )
                M[x]=i;
    }
    
    return M[x];
}

int main()
{
    int n, ans=0;
    map<int, int> M;
    
    for(scanf("%d", &n); n>0; n--)
    {
        int x;
        scanf("%d", &x);
        
        for(int i=2; i*i<=x; i++)
        {
            int cnt=0;
            
            for(; x%i==0; x/=i)
                cnt++;
            
            if( cnt>0 )
                M[i]|=1<<cnt;
        }
        
        if( x>1 )
            M[x]|=2;
    }
    
    for(const auto& it : M)
        ans^=f(it.second);
    
    printf(ans!=0 ? "Mojtaba\n" : "Arpa\n");
}
