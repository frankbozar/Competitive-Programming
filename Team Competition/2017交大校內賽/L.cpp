#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

const int INF=0x3FFFFFFF;
char A[200][200];
int tr[4][2]={{0, 1}, {1, 0}, {0, -1}, {-1, 0}}, ind[200][200];

struct edge
{
    int t, c, r;
    edge(int _t, int _c, int _r)
    {
        t=_t;
        c=_c;
        r=_r;

    }

};

struct Dinic
{
    vector<int> l;
    vector<vector<edge>> e;
    Dinic(int n):e(n) {}
    void add(int u, int v, int w)
    {
        e[u].push_back(edge(v, w, e[v].size()));
        e[v].push_back(edge(u, 0, e[u].size()-1));

    }
    edge& rev(const edge& E)
    {
        return e[E.t][E.r];

    }
    bool bfs(int s, int t)
    {
        l.assign(e.size(), INF);
        l[s]=1;
        queue<int> Q;
        for(Q.push(s); !Q.empty(); Q.pop())
        {
            s=Q.front();
            for(const edge& E: e[s])
            {
                if(E.c>0 && l[E.t]>l[s]+1)
                {
                    l[E.t]=l[s]+1;
                    Q.push(E.t);
                }

            }

        }
        return l[t]<INF;
    }
    int dfs(int s, int t, int num=INF)
    {
        if(s==t || num==0)
            return num;
        int ans=0;
        for(edge& E: e[s])
            if(E.c>0 && l[s]+1==l[E.t])
            {
                int tmp=dfs(E.t, t, min(num, E.c));
                rev(E).c+=tmp, ans+=tmp;
                E.c-=tmp, num-=tmp;

            }
        return ans>0?ans:l[s]=0;

    }
    int operator()(int s, int t)
    {
        int ans=0, tmp=0;
        while(bfs(s, t))
            while((tmp=dfs(s, t)))
                ans+=tmp;
        return ans;

    }
};




int main()
{
    int T;

    for(scanf("%d", &T); T>0; T--)
    {
        int h, w;
        scanf("%d%d", &h, &w);
        int a=0, b=0, c=0;
        for(int i=0; i<h; i++)
        {
            scanf("%s", A[i]);
            for(int j=0; j<w; j++)
            {
                if(A[i][j]=='H')
                    a++;
                else if(A[i][j]=='B')
                    b++;
                else
                    c++;

            }
        }
        int n=a+2*b+c+2;
        int cnt[3]= {0};
        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                if(A[i][j]=='H')
                    ind[i][j]=cnt[0]++;
                else if(A[i][j]=='B')
                    ind[i][j]=a+(cnt[1]++)*2;
                else
                    ind[i][j]=a+2*b+(cnt[2]++);
            }
        }
        //printf("a=%d b=%d c=%d n=%d\n", a, b, c, n);
        Dinic D(n);
        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                //printf("i=%d j=%d\n", i, j);
                if(A[i][j]=='H')
                {
                    D.add(n-2, ind[i][j], 1);
                    //printf("AAA\n");
                    for(int d=0; d<4; d++)
                    {
                    //printf("ddd %d\n", d);
                        int xt=i+tr[d][0], yt=j+tr[d][1];
                        if(xt<0 || xt>=h || yt<0 || yt>=w)
                            continue;
                        if(A[xt][yt]!='B')
                            continue;
                            //printf("d=%d\n", d);
                        D.add(ind[i][j], ind[xt][yt], 1);
                    }

                }
                else if(A[i][j]=='B')
                {
                    //printf("BBB\n");
                    D.add(ind[i][j], ind[i][j]+1, 1);
                    //printf("ind %d %d\n", ind[i][j], ind[i][j]+1);
                    for(int d=0; d<4; d++)
                    {
                        int xt=i+tr[d][0], yt=j+tr[d][1];
                        if(xt<0 || xt>=h || yt<0 || yt>=w)
                            continue;
                        if(A[xt][yt]!='T')
                            continue;
                        D.add(ind[i][j]+1, ind[xt][yt], 1);
                    }
                }
                else
                {
                    //printf("TTT\n");
                    D.add(ind[i][j], n-1, 1);
                }
            }
        }
        printf("%d\n", D(n-2, n-1));

    }

}


/*

2
1 4
BHBT
2 3
BHH
TTB

*/


