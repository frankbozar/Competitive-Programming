#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const double INF=1e100;

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<int> a(n+1, 0);
        
        for(int i=1; i<=n; i++)
            scanf("%d", &a[i]);
        
        sort(a.rbegin(), a.rend()-1);
        
        for(int i=1; i<=n; i++)
            a[i]+=a[i-1];
        
        vector<vector<double>> d(m+1, vector<double>(n+1, INF));
        d[0][0]=0;
        
        for(int i=1; i<=m; i++)
            for(int j=1; j<=n; j++)
                for(int k=0; k<j; k++)
                    d[i][j]=min(d[i][j], d[i-1][k]+j*(a[j]-a[k])/(double)a[n]);
        
        printf("%.4f\n", d[m][n]);
    }
}

/*

2

5 2
30 5 10 30 25

5 5
30 5 10 30 25

*/
