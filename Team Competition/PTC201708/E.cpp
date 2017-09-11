#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int step[4][2]={{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m, sx, sy, tx, ty;
        scanf("%d%d%d%d%d%d", &n, &m, &sx, &sy, &tx, &ty);
        vector<vector<double>> p(n, vector<double>(m, 0)), e(n, vector<double>(m, 0));
        p[sx-1][sy-1]=1;
        double ans=0;
        
        for(int l=1; l<=100000; l++)
        {
            double sum=0;
            vector<vector<double>> q(n, vector<double>(m, 0));
            
            for(int x=0; x<n; x++)
                for(int y=0; y<m; y++)
                {
                    sum+=p[x][y];
                    int cnt=0;
                    
                    for(int k=0; k<4; k++)
                    {
                        int nx=x+step[k][0];
                        int ny=y+step[k][1];
                        
                        if( 0<=nx && nx<n && 0<=ny && ny<m )
                            cnt++;
                    }
                    
                    for(int k=0; k<4; k++)
                    {
                        int nx=x+step[k][0];
                        int ny=y+step[k][1];
                        
                        if( 0<=nx && nx<n && 0<=ny && ny<m )
                            q[nx][ny]+=p[x][y]/cnt;
                    }
                }
            
            swap(p, q);
            ans+=p[tx-1][ty-1]*l;
            p[tx-1][ty-1]=0;
            
            if( sum<1e-8 )
                break;
        }
        
        printf("%.2f\n", ans);
    }
}

/*

4
2 2 1 2 2 1
1 2 1 1 1 2
1 3 1 2 1 1
3 3 2 2 1 1

*/
