#include<cstdio>
#include<vector>
using namespace std;

const int N=100000;
const int INF=0x3FFFFFFF;


int main()
{
    freopen("jumping.in", "rb", stdin);
 
    int T;
    scanf("%d", &T);
    for(; T>0; T--)
    {
    int n;
    scanf("%d", &n);
    vector<int> D(n, INF);
    vector<vector<int>> E(n);
    for(int i=0; i<n; i++)
    {
        int t;
        scanf("%d", &t);
        if(i-t>=0)
            E[i-t].push_back(i);
        if(i+t<n)
            E[i+t].push_back(i);
    }
    //printf("A\n");
    D[n-1]=0;
    vector<int> q, q2;
    q.push_back(n-1);
    for(; q.size()>0; )
    {
        for(int u:q)
        {
      //      printf("u=%d\n", u);
            for(int v:E[u])
                if(D[v]==INF)
                {
                    D[v]=D[u]+1;
                    q2.push_back(v);
                }
        }
        q.clear();
        q.swap(q2);
    }
    for(int i=0; i<n; i++)
        printf("%d%s", D[i]==INF?-1:D[i], i==n-1?"\n":"\n");
}
}
