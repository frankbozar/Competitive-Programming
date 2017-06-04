#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
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
        int k, ans=0;
        scanf("%d", &k);
        map<int, int> M, S;
        
        for(int i=0; i<k; i++)
        {
            int x;
            scanf("%d", &x);
            M[x]++;
        }
        
        for(int i=0; i+k<=n; i++)
        {
            if( i==0 )
            {
                for(int j=0; j<k; j++)
                    S[ a[j] ]++;
            }
            else
            {
                S[ a[i+k-1] ]++;
                
                if( --S[ a[i-1] ]==0 )
                    S.erase(a[i-1]);
            }
            
            if( M==S )
                ans++;
        }
        
        printf("%d\n", ans);
    }
}
