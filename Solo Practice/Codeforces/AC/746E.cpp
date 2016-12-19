#include<cstdio>
#include<set>
#include<vector>
using namespace std;

int main()
{
    int n, m, ans=0, o=0, e=0;
    scanf("%d%d", &n, &m);
    vector<int> a(n);
    set<int> S;
    
    for(int i=0; i<n; i++)
    {
        scanf("%d", &a[i]);
        
        if( S.find(a[i])!=S.end() )
        {
            a[i]=-1;
            ans++;
        }
        else if( a[i]%2==1 && o>=n>>1 )
        {
            a[i]=-1;
            ans++;
        }
        else if( a[i]%2==0 && e>=n>>1 )
        {
            a[i]=-1;
            ans++;
        }
        else
        {
            a[i]&1 ? o++ : e++;
            S.insert(a[i]);
        }
    }
    
    for(int p=1, q=2, i=0; i<n; i++)
    {
        if( a[i]>0 )
            continue;
        else if( o<n>>1 )
        {
            for(; S.find(p)!=S.end(); p+=2);
            
            if( p>m )
            {
                printf("-1\n");
                return 0 ;
            }
            
            o++;
            a[i]=p;
        }
        else
        {
            for(; S.find(q)!=S.end(); q+=2);
            
            if( q>m )
            {
                printf("-1\n");
                return 0;
            }
            
            e++;
            a[i]=q;
        }
        
        S.insert(a[i]);
    }
    
    printf("%d\n", ans);
    
    for(int i=0; i<n; i++)
        printf(i==n-1 ? "%d\n" : "%d ", a[i]);
}