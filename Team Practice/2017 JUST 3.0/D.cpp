#include<cstdio>
#include<vector>
using namespace std;
const int N=1<<16;
#define data pair<int,int>
#define p first
#define w second

int main()
{
    vector<vector<int>> a(N, vector<int>(7, N));
    a[0][1]=0;
    
    for(int i=0; i<N; i++)
        for(int j=1; j<=6; j++)
        {
            a[i][0]=min(a[i][0], a[i][j]);
            
            for(int k=1; k<=6; k++)
                if( k!=j && k!=7-j && i+k<N )
                    a[i+k][k]=min(a[i+k][k], a[i][j]+1);
        }
    
    int T;
    
    for(scanf("%d", &T); T>0; T--)
    {
        int n;
        scanf("%d", &n);
        printf("%d\n", a[n][0]>=N ? -1 : a[n][0]);
    }
}
