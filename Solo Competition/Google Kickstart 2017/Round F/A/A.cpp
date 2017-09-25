#include<cstdio>
#include<vector>
using namespace std;

bool sol(const vector<int>& a, int n)
{
    int l=1, r=n, m;
    
    for(int i=0; i<n; i++)
    {
        if( n&1 )
            m= i&1 ? (n>>1)-(i>>1)-1 : (n>>1)+(i>>1) ;
        else
            m= i&1 ? (n>>1)+(i>>1) : (n>>1)-(i>>1)-1 ;
        
        if( a[m]==l )
            l++;
        else if( a[m]==r )
            r--;
        else
            return false;
    }
    
    return true;
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n;
        scanf("%d", &n);
        vector<int> a(n);
        
        for(int i=0; i<n; i++)
            scanf("%d", &a[i]);
        
        printf("Case #%d: %s\n", cases, sol(a, n) ? "YES" : "NO");
    }
}
