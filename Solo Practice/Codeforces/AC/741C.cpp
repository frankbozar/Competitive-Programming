#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
#define data pair<int,int>
#define F first
#define S second

int main()
{
    int n;
    scanf("%d", &n);
    vector<data> a(n), e(n<<1);
    
    for(int i=0; i<n; i++)
    {
        scanf("%d%d", &a[i].F, &a[i].S);
        a[i].F--, a[i].S--;
        e[ a[i].F ].F=a[i].S;
        e[ a[i].S ].F=a[i].F;
    }
    
    for(int i=0; i<n<<1; i+=2)
    {
        e[i].S=i|1;
        e[i|1].S=i;
    }
    
    vector<int> d(n<<1, -1);
    
    for(int i=0; i<n<<1; i++)
    {
        if( d[i]>=0 )
            continue;
        
        d[i]=0;
        queue<int> Q;
        
        for(Q.push(i); !Q.empty(); Q.pop())
        {
            int u=Q.front();
            
            if( d[ e[u].F ]<0 )
            {
                d[ e[u].F ]=d[u]^1;
                Q.push(e[u].F);
            }
            
            if( d[ e[u].S ]<0 )
            {
                d[ e[u].S ]=d[u]^1;
                Q.push(e[u].S);
            }
        }
    }
    
    for(int i=0; i<n; i++)
        printf("%d %d\n", d[ a[i].F ]+1, d[ a[i].S ]+1);
}