#include<cstdio>
#include<algorithm>
#include<map>
#include<queue>
#include<string>
#include<vector>
using namespace std;

typedef long long lld;

const int N=50;

int pos[N+2];

lld sol(int a, int b, int c, int n)
{
    if(n==1)
    {
        return pos[n]==a?0:pos[n]==c?1:-1;
    }
    if(pos[n]==a)
    {
        return sol(a, c, b, n-1);
    }
    else if(pos[n]==c)
    {
        lld t=sol(b, a, c, n-1);
        if(t==-1)
            return t;
        return (1LL<<(n-1))+t;
    }
    else
        return -1;
}

int main()
{
    int n=1;
    for(int k=0; k<3; k++)
    {
        int m;
        scanf("%d", &m);
        vector<int> v(m);
        for(int i=0; i<m; i++)
        {
            scanf("%d", &v[i]);
            pos[v[i]]=k;
            n=max(n, v[i]);
            if(i>0 && v[i-1]<=v[i])
            {
                printf("No\n");
                return 0;
            }
        }
    }
    lld t=sol(0, 1, 2, n);
    if(t==-1)
    {
        printf("No\n");
        return 0;
    }
    printf("%lld\n", (1LL<<n)-1-t);
}

/*

4 6
Pashto French Amheric Swedish
English Pashto 1
English French 1
English Amheric 5
Pashto Amheric 1
Amheric Swedish 5
French Swedish 1

2 1
A B
English B 1

*/
