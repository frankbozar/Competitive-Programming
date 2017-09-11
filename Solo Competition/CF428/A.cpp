#include<cstdio>
#include<algorithm>
using namespace std;

int main()
{
    int n, k, p=0;
    scanf("%d%d", &n, &k);
    
    for(int i=0; i<n; i++)
    {
        int x;
        scanf("%d", &x);
        p+=x;
        int t=min(p, 8);
        p-=t;
        k-=t;
        
        if( k<=0 )
        {
            printf("%d\n", i+1);
            return 0;
        }
    }
    
    printf("-1\n");
}
