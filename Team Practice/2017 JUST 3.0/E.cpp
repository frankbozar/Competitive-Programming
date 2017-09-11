#include<cstdio>
#include<algorithm>
using namespace std;
char s[1<<20];

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, c[3]={0};
        
        for(scanf("%d", &n); n>0; n--)
        {
            scanf("%s", s);
            
            if( s[0]=='b' )
                c[0]++;
            else if( s[0]=='k' )
                c[1]++;
            else//if( s[0]=='l' )
                c[2]++;
        }
        
        printf("%d\n", min(c[0]>>1, min(c[1], c[2])));
    }
}
