#include<cstdio>
#include<cstring>
const int INF=1<<20;
int dp[64][64][64];
int solve1(int a, int b, int c);
int solve2(int a, int b, int c);

int solve1(int a, int b, int c)
{
    if( a==b || b==c || c==a )
        return INF;
    
    int& ans=dp[a][b][c];
    
    if( ans==-1 )
    {
        ans=INF;
        int xa=a>>3, ya=a&7;
        int xb=b>>3, yb=b&7;
        int xc=c>>3, yc=c&7;
        
        for(int i=0; i<8; i++)
        {
            int na=(i<<3)|ya;
            
            if( na!=a && na!=b && na!=c )
                ans=min(ans, solve2(na, b, c));
            
            na=(xa<<3)|i;
            
            if( i!=ya )
            {
                
                
                
                
            }
        }
        
        
        
        
        
        
        ans=tmp;
    }
    
    return ans;
}

int main()
{
    memset(dp, -1, sizeof(dp));
    
    int N;
    scanf("%d", &N);
    
    
    
}
