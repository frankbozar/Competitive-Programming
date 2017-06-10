#include<cstdio>
#include<vector>
using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> a(n), b(n), c(n+1, 0);
    int p=-1, q=-1, u=-1, v=-1;
    
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);
    
    for(int i=0; i<n; i++)
        scanf("%d", &b[i]);
    
    for(int i=0; i<n; i++)
    {
        if( a[i]!=b[i] )
            (p<0 ? p : q)=i;
        else
            c[ a[i] ]++;
    }
    
    for(int i=1; i<=n; i++)
        if( c[i]==0 )
            (u<0 ? u : v)=i;
    
    if( q>=0 )
    {
        for(int i=0; i<n; i++)
        {
            if( i!=p && i!=q )
                printf(i==n-1 ? "%d\n" : "%d ", a[i]);
            else
                printf(i==n-1 ? "%d\n" : "%d ", (a[p]==u || b[p]==u) && (a[q]==v || b[q]==v) ? (i==p ? u : v) : (i==p ? v : u));
        }
    }
    else
    {
        for(int i=0; i<n; i++)
            printf(i==n-1 ? "%d\n" : "%d ", i==p ? u : a[i]);
    }
}
