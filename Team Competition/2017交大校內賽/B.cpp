#include<cstdio>
#include<set>
using namespace std;

int main()
{
    int N;

    for(scanf("%d", &N); N>0; N--)
    {
        int n, ans=0;
        scanf("%d", &n);
        set<int> S;

        for(int i=0; i<n; i++)
        {
            int x;
            scanf("%d", &x);
            S.insert(x);
        }

        for(S.erase(1); !S.empty(); ans++)
        {
            S.erase(*S.rbegin()-1);
            S.erase(*S.rbegin());
        }

        printf("%d\n", ans);
    }
}

/*

2
5
1 2 3 4 4
10
1 2 4 5 7 9 10 10 1 1

*/
