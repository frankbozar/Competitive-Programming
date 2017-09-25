#include<cstdio>
#include<vector>
using namespace std;
const int N=1<<20;

int main()
{
    vector<int> a(N, N);
    a[0]=0;
    
    for(int i=0; i<N; i++)
        for(int j=1; i+j*j<N; j++)
            a[i+j*j]=min(a[i+j*j], a[i]+1);
    
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n;
        scanf("%d", &n);
        printf("Case #%d: %d\n", cases, a[n]);
    }
}
