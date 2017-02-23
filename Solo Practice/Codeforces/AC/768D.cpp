#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N=10000;

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<double> a(N), u(n+1, 0);
    u[0]=1;
    
    for(int i=0; i<N; i++)
    {
        a[i]=u[n];
        
        for(int j=n; j>0; j--)
            u[j]=(u[j]*j+u[j-1]*(n-j+1))/n;
        
        u[0]=0;
    }
    
    for(; m>0; m--)
    {
        int p;
        scanf("%d", &p);
        printf("%ld\n", lower_bound(a.begin(), a.end(), p/2000.0)-a.begin());
    }
}
