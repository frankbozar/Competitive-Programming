#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

double top(vector<double>& p, double u, int l, int r)
{
    for(int i=r-1; i>=l; i--)
    {
        if( u<=(1-p[i])*(i-l+1) )
        {
            for(int j=l; j<=i; j++)
                p[j]+=u/(i-l+1);
            
            return 0;
        }
        else
        {
            u-=(1-p[i])*(i-l+1);
            
            for(int j=l; j<=i; j++)
                p[j]+=1-p[i];
        }
    }
    
    return u;
}

double bot(vector<double>& p, double u, int l, int r)
{
    for(int i=l; i<r; i++)
    {
        if( u<=(p[i+1]-p[i])*(i-l+1) )
        {
            for(int j=l; j<=i; j++)
                p[j]+=u/(i-l+1);
            
            return 0;
        }
        else
        {
            u-=(p[i+1]-p[i])*(i-l+1);
            
            for(int j=l; j<=i; j++)
                p[j]=p[i+1];
        }
    }
    
    return u;
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n, m;
        double u, ans=0;
        scanf("%d%d%lf", &n, &m, &u);
        vector<double> p(n);
        
        for(int i=0; i<n; i++)
            scanf("%lf", &p[i]);
        
        sort(p.begin(), p.end());
        p.push_back(1);
        u=bot(p, u, n-m, n);
        u=bot(p, u, 0, n-m);
        vector<vector<double>> a(n+1, vector<double>(n+1, 0));
        a[0][0]=1;
        
        for(int i=1; i<=n; i++)
        {
            for(int j=0; j<=i; j++)
            {
                a[i][j]=a[i-1][j]*(1-p[i-1]);
                
                if( j>0 )
                    a[i][j]+=a[i-1][j-1]*p[i-1];
            }
        }
        
        for(int i=m; i<=n; i++)
            ans+=a[n][i];
        
        printf("Case #%d: %.10f\n", cases, ans);
    }
}

/*

4

4 4
1.4000
0.5000 0.7000 0.8000 0.6000

2 2
1.0000
0.0000 0.0000

2 1
0.0000
0.9000 0.8000

2 1
0.1000
0.4000 0.5000

*/
