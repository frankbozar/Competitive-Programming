#include <stdio.h>
#include <algorithm>

using namespace std;

const int INF = 0x3FFFFFFF;

int cmp(int a, int b, int c, int d)
{
    if( a*d == b*c )
        return 0;
    else if( a*d > b*c )
        return 1;
    return 2;
}

int main()
{
    int T;
    scanf("%d",&T);

    for(int t = 0; t < T; t++)
    {
        int n;
        scanf("%d",&n);

        int a,b;
        scanf("%d %d",&a,&b);

        int c[3] = {INF,INF,INF};

        for(int i = 0; i < n; i++)
        {
            int x,y,z;
            scanf("%d %d %d",&x,&y,&z);
            c[ cmp(x,y,a,b) ] = min(c[ cmp(x,y,a,b) ], z);
        }
        int ans = min(c[0],c[1]+c[2]);

        if( ans >= INF )
            puts("Impossible");
        else
            printf("%d\n",ans);
    }

	return 0;
}

/*
2
1
1 2
2 1 1
2
1 2
2 1 1
1 3 1
*/
