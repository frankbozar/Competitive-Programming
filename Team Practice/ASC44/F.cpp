#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    for(int n, m; scanf("%d%d", &n, &m) && (n||m); )
    {
        vector<int> num(n+1), pos(n+1, 0);
        vector<vector<int>> occ;
        map<int, int> M;
        
        for(int i=1; i<=n; i++)
        {
            scanf("%d", &num[i]);
            
            if( M.find(a[i])==M.end() )
            {
                M[ num[i] ]=occ.size();
                occ.resize(occ.size()+1);
            }
            
            num[i]=M[ num[i] ];
            pos[i]=occ[ num[i] ].size();
            occ[ num[i] ].push_back(i);
        }
        
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        vector<vector<int>> pr(m+1, vector<int>(n+1, 0));
        
        for(int k=1; k<=m; k++)
        {
            for(int i=1; i<=n; i++)
            {
                int v=dp[][i-1]+o[ a[i] ].size()-p[i];
                
                if( Y[ o[ a[i] ].back() ]<v )
                    Y[ o[ a[i] ].back() ]=v;
            }
            
            for(const vector<int>& O : o)
            {
                int l=O.size();
                
                for(int i=l-1; i>0; i--)
                {
                    int u=O[i-1];
                    int v=O[i];
                    
                    if( Y[u]<Y[v]-(X[v]-X[u]+1) )
                        Y[u]=Y[v]-(X[v]-X[u]+1);
                }
            }
            
            for(int i=1; i<=n; i++)
                X[i]=max(X[i-1], Y[i]);
            
            printf("~~ ");
            for(int v : X)
                printf("%d ", v);
            printf("\n");
        }
        
        printf("%d\n", X[n]);
    }
}

/*

10 2
2 3 2 3 2 1 2 1 2 1

0 0

*/
