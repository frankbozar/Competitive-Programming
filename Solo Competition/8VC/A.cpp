#include<cstdio>
#include<vector>
using namespace std;
const int N=1024;

int main()
{
    vector<bool> p(N, true);
    p[0]=p[1]=false;
    
    for(int i=2; i<N; i++)
        if( p[i] )
            for(int j=i*i; j<N; j+=i)
                p[j]=false;
    
    int n;
    scanf("%d", &n);
    
    for(int i=1; i<N; i++)
        if( !p[n*i+1] )
        {
            printf("%d\n", i);
            break;
        }
}
