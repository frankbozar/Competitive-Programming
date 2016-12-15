#include <stdio.h>
#include <string.h>

typedef unsigned long long lld;

const int t[3][3] = {{0,0,0},{0,3,2},{0,2,1}};
lld ans[31][3];

int main()
{
    memset(ans,0,sizeof(ans));
    ans[0][1] = 1;
    ans[1][1] = 3;
    ans[1][2] = 2;

    for(int i = 2; i <= 30; i++)
        for(int j = 1; j <= 2; j++)
            for(int k = 1; k <= 2; k++)
                ans[i][j] += ans[i-1][k]*t[k][j];

    int T;
    scanf("%d",&T);

    for(int c = 0; c < T; c++)
    {
        int n;
        scanf("%d",&n);

        printf("%llu\n",ans[n][1]+ans[n][2]);
    }

    return 0;
}
