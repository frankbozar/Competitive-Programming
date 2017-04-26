#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
vector<vector<double>> p, tp, gp;
vector<int> a;

int main()
{
    freopen("trip.in", "rb", stdin);
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m, k, q, z;
        scanf("%d%d%d%d%d", &n, &m, &k, &q, &z);
        p.assign(k, vector<double>(n, 0));
        tp.assign(n, vector<double>(n));
        gp.assign(n, vector<double>(m));
        a.resize(k);
        
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                scanf("%lf", &tp[i][j]);
        
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                scanf("%lf", &gp[i][j]);
        
        for(int i=0; i<k; i++)
            scanf("%d", &a[i]);
        
        p[0][0]=1;
        
        for(int i=1; i<k; i++)
            for(int u=0; u<n; u++)
                for(int v=0; v<n; v++)
                    p[i][u]+=p[i-1][v]*tp[v][u];
        
        
        
        
        
        
        printf("%.3f\n", 0.0);
    }
}
