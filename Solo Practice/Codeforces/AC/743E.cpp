#include<cstdio>
#include<cstring>
#include<bitset>
#include<vector>
#include<algorithm>
using namespace std;
typedef bitset<8> set;
int p[8][1024][128];

bool check(set& u, int n, int m, int c=0)
{
    if( c<0 )
        return false;
    else if( u.all() )
        return true;
    
    for(int i=0; i<8; i++)
        if( !u[i] )
        {
            u[i]=true;
            
            if( m<=8-u.count() && check(u, n, m, p[i][c][n]) )
                return true;
            else if( m>0 && check(u, n, m-1, p[i][c][n+1]) )
                return true;
                
            u[i]=false;
        }
    
    return false;
}

int main()
{
    int n, ans=-1;
    scanf("%d", &n);
    vector<int> a(n);
    memset(p, 0xFF, sizeof(p));
    
    for(int i=0; i<n; i++)
    {
        scanf("%d", &a[i]);
        a[i]--;
    }
    
    for(int k=0; k<8; k++)
    {
        for(int i=0; i<n; i++)
        {
            p[k][i][0]=i;
            
            for(int c=1, j=i; c<=(n+7)>>3 && j<n; j++)
                if( a[j]==k )
                    p[k][i][c++]=j+1;
        }
    }
    
    for(int l=0, r=n+1; l<r; )
    {
        int m=(l+r)>>1;
        set u;
        
        if( !check(u, m>>3, m&7) )
            r=m;
        else
        {
            l=m+1;
            ans=m;
        }
    }
    
    printf("%d\n", ans);
}