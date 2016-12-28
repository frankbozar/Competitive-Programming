#include<cstdio>
#include<vector>
using namespace std;

int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    vector<int> a(m+1, 0);
    
    for(int i=0; i<m; i++)
        scanf("%d", &a[i]);
    
    if( k>n-m )
    {
        printf("-1\n");
        return 0;
    }
    
    for(int i=0; i<m; i++)
        if( a[i]>a[i+1] )
            k-=a[i]-a[i+1];
    
    if( k<0 )
    {
        printf("-1\n");
        return 0;
    }
    
    printf("%d\n", n);
    
    for(int p=1, q=1, u=2, i=0; i<m; i++)
    {
        int tmp=min(k, min(q-p, a[i]-1));
        k-=tmp;
        p=q-min(a[i]-1, q-p)+tmp;
        
        if( a[i]<q-p+1 )
            p+=q-p+1-a[i];
        
        for(tmp=a[i]; tmp>0; tmp--)
            printf("%d %d\n", p<q ? p++ : p, u++);
        
        p=q+1;
        q+=a[i];
    }
}
