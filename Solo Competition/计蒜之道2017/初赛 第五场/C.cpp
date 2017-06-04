#include<cstdio>
#include<vector>
using namespace std;

int main()
{
    int n, m;
    scanf("%d", &n);
    vector<int> a(n);
    
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);
    
    for(scanf("%d", &m); m>0; m--)
    {
        int k, mat=0;
        scanf("%d", &k);
        vector<int> C(n+1, 0), D(n+1, 0);
        
        for(int i=0; i<k; i++)
        {
            int x;
            scanf("%d", &x);
            C[x]++;
            D[ a[i] ]++;
        }
        
        for(int i=1; i<=n; i++)
            mat+= C[i]==D[i];
        
        int ans= mat==n;
        
        for(int i=0; i+k<n; i++)
        {
            if( C[ a[i] ]==D[ a[i] ] )
                mat--;
            
            D[ a[i] ]--;
            
            if( C[ a[i] ]==D[ a[i] ] )
                mat++;
            
            if( C[ a[i+k] ]==D[ a[i+k] ] )
                mat--;
            
            D[ a[i+k] ]++;
            
            if( C[ a[i+k] ]==D[ a[i+k] ] )
                mat++;
            
            ans+= mat==n;
        }
        
        printf("%d\n", ans);
    }
}
