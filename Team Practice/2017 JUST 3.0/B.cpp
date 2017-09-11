#include<cstdio>
#include<map>
#include<set>
using namespace std;
typedef long long lld;

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        map<int, int> A, B;
        set<int> S;
        int n;
        
        for(scanf("%d", &n); n>0; n--)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            A[x]++;
            B[y]++;
            S.insert(x);
            S.insert(y);
        }
        
        lld ans=0;
        
        for(int x : S)
            ans+=A[x]*(lld)B[x];
        
        printf("%lld\n", ans);
    }
}
