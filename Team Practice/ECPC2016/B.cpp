#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

const double INF=1e100;


int main()
{
    freopen("street.in", "rb", stdin);
    
    int T;
    scanf("%d", &T);
    for(; T>0; T--)
    {
        int n;
        double h, w;
        scanf("%d%lf%lf", &n, &h, &w);
        vector<vector<double>> D(n+2, vector<double>(n+2, INF));
        vector<double> x(n+2), y(n+2), x2(n+2), y2(n+2);
        for(int i=0; i<n; i++)
        {
            double a, b, c, d;
            scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
            x[i]=0;
            y[i]=c;
            x2[i]=b;
            y2[i]=c+a;
            if(d==1)
                x[i]=w-b, x2[i]=w;
        }
        x[n]=0, y[n]=h, x2[n]=w, y2[n]=h+100;
        x[n+1]=0, y[n+1]=-100, x2[n+1]=w, y2[n+1]=0;
        n+=2;
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
            {
                double& res=D[i][j];
                if(i==j)
                    res=0;
                
                else if(!(x[i]>=x2[j] || x2[i]<=x[j]))
                {
                    vector<double> l={y[i], y2[i]};
                    vector<double> r={y[j], y2[j]};
                    for(double L: l)
                        for(double R: r)
                            res=min(res, abs(L-R));
                }
                else if(!(y[i]>=y2[j] || y2[i]<=y[j]))
                {
                    vector<double> l={x[i], x2[i]};
                    vector<double> r={x[j], x2[j]};
                    for(double L: l)
                        for(double R: r)
                            res=min(res, abs(L-R));
                }
                else
                {
                    vector<vector<double>> l={{x[i], y[i]}, {x[i], y2[i]}, {x2[i], y[i]}, {x2[i], y2[i]}};
                    
                    vector<vector<double>> r={{x[j], y[j]}, {x[j], y2[j]}, {x2[j], y[j]}, {x2[j], y2[j]}};
                    for(vector<double>& L: l)
                        for(vector<double>& R: r)
                            res=min(res, sqrt((L[0]-R[0])*(L[0]-R[0])+(L[1]-R[1])*(L[1]-R[1])));
                }
            }
        //printf("A\n");
        for(int k=0; k<n; k++)
            for(int i=0; i<n; i++)
                for(int j=0; j<n; j++)
                    D[i][j]=min(D[i][j], D[i][k]+D[k][j]);
        
        printf("%.6f\n", D[n-2][n-1]);
    }
}
