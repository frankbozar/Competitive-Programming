#include<cstdio>
#include<map>
using namespace std;

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        map<int, int> M;
        int n, m=0, ans=-1;
        
        for(scanf("%d", &n); n>0; n--)
        {
            int x;
            scanf("%*s%d", &x);
            M[x]++;
            
            if( m<M[x] || m==M[x] && ans>x )
                m=M[x], ans=x;
        }
        
        printf("%d\n", ans);
    }
}
