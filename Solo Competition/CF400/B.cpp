#include<cstdio>
#include<vector>
using namespace std;
typedef long long lld;

int main()
{
    lld n;
    scanf("%lld", &n);
    
    if( n<=2 )
    {
        printf("1\n");
        
        for(int i=0; i<n; i++)
            printf(i==n-1 ? "1\n" : "1 ");
        
        return 0;
    }
    
    n+=2;
    vector<bool> p(n, true);
    p[0]=p[1]=false;
    printf("2\n");
    
    for(lld i=2; i<n; i++)
    {
        if( !p[i] )
            printf("1");
        else
        {
            printf("2");
            
            for(lld j=i*i; j<n; j+=i)
                p[j]=false;
        }
        
        printf(i==n-1 ? "\n" : " ");
    }
}
