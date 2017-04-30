#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
vector<vector<int>> e;
vector<int> mh, mc, ta;

void dfsh(int u=1, int p=0)
{
    mh[u]=0, mc[u]=1;
    
    for(int v : e[u])
    {
        if( v==p )
            continue;
        else
            dfsh(v, u);
        
        if( mh[u]<mh[v]+1 )
            mh[u]=mh[v]+1, mc[u]=1;
        else if( mh[u]==mh[v]+1 )
            mc[u]++;
    }
}

void dfss(int k, int u=1, int p=0, int h=0)
{
    ta[u]= mh[u]>k || h>k ? 0 : 1 ;
    
    for(int v : e[u])
    {
        if( v==p )
            continue;
        else if( mh[v]!=mh[u]-1 || mc[u]!=1 )
            dfss(k, v, u, max(mh[u], h)+1);
        else
        {
            int tmp=h;
            
            for(int w : e[u])
                if( w!=p && w!=v )
                    tmp=max(tmp, mh[w]+1);
            
            dfss(k, v, u, tmp+1);
        }
    }
}

int main()
{
    int N, n, m, k;
    
    for(scanf("%d", &N); N>0; N--)
    {
        scanf("%d%d", &m, &k);
        double ans=0;
        
        for(int i=0; i<m; i++)
        {
            scanf("%d", &n);
            e.clear();
            e.resize(n+1);
            mh.resize(n+1);
            mc.resize(n+1);
            ta.resize(n+1);
            
            for(int u=2; u<=n; u++)
            {
                int v;
                scanf("%d", &v);
                e[u].push_back(v);
                e[v].push_back(u);
            }
            
            dfsh();
            dfss(k);
            int a[2]={0};
            
            for(int i=1; i<=n; i++)
                a[ ta[i] ]++;
            
            double p=a[1]/(double)n;
            double q=a[0]/(double)n;
            ans+=(ans+4)*q/p+1;
        }
        
        printf("%.4f\n", ans);
    }
}

/*

3

2 2
2 1
3 1 1

3 5
7 3 4 7 1 5 6
6 1 4 2 1 5
5 1 1 5 1

4 3
4 4 1 1
6 1 2 1 1 5
5 4 1 3 4
1

*/
