#include<cmath>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const double INF=1e100;
const double EPS=1e-10;
#define data pair<double,int>
#define t first
#define e second

int main()
{
    int n;
    double x1, x2, y1, y2;
    scanf("%d%lf%lf%lf%lf", &n, &x1, &y1, &x2, &y2);
    vector<data> a;
    
    for(int i=0; i<n; i++)
    {
        double rx, ry, vx, vy, p=INF, q=-INF;
        scanf("%lf%lf%lf%lf", &rx, &ry, &vx, &vy);
        
        for(int j=0; j<2; j++)
        {
            for(int k=0; vx!=0 && k<2; k++)
            {
                swap(x1, x2);
                double s=max((x1-rx)/vx, 0.0);
                double y=ry+vy*s;
                
                if( y1<=y && y<=y2 )
                    p=min(p, s), q=max(q, s);
            }
            
            swap(rx, ry);
            swap(vx, vy);
            swap(x1, y1);
            swap(x2, y2);
        }
        
        if( vx==0 && vy==0 && x1<=rx && rx<=x2 && y1<=ry && ry<=y2 )
            p=0, q=INF;
        
        p+=EPS;
        rx+=vx*p;
        ry+=vy*p;
        const int C=-100;
        
        if( !(log(rx-x1)>C && log(x2-rx)>C && log(ry-y1)>C && log(y2-ry)>C) )
            p=INF, q=-INF;
        
        a.push_back(data(p, 1));
        a.push_back(data(q, 0));
    }
    
    sort(a.begin(), a.end());
    
    for(const data& D : a)
    {
        if( D.e==0 )
        {
            printf("-1\n");
            break;
        }
        else if( n==1 )
        {
            printf("%.10f\n", D.t);
            break;
        }
        
        n--;
    }
}
