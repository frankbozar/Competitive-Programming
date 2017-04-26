#include<cmath>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const double EPS=1e-10;
const double INF=1e100;
const int N=210000;
pair<double, double> A[N];

int main()
{
    freopen("walk.in", "rb", stdin);
    int T;
    
    for(scanf("%d", &T); T>0; T--)
    {
        int n, p=0;
        double R;
        scanf("%d%lf", &n, &R);
        
        for(int i=0; i<n; i++)
        {
            int dx, dy, dr;
            scanf("%d%d%d", &dx, &dy, &dr);
            double x=dx, y=dy, r=dr, dis=R-r;
            
            if( r>R || fabs(y)>dis )
                continue;
            
            double d=sqrt(dis*dis-y*y);
            A[p].first=x-d;
            A[p++].second=r;
            A[p].first=x+d+EPS;
            A[p++].second=-r;
        }
        
        sort(A, A+p);
        double ans=0, cnt=0;
        
        for(int i=0; i<p; )
        {
            //printf("%.3f %.3f\n", v[i][0], v[i][1]);
            double now=A[i].first;
            cnt+=A[i].second;
            
            while( ++i<p && A[i].first<=now )
                //printf("%.3f %.3f\n", v[i][0], v[i][1]);
                cnt+=A[i].second;
            
            ans=max(ans, cnt);
        }
        
        printf("%.0f\n", ans);
    }
}
