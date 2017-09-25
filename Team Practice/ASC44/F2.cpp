#include<cstdio>
#include<map>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    for(int n, m; scanf("%d%d", &n, &m) && (n||m); )
    {
        map<int, int> M;
        vector<int> a(n+1), p(n+1, 0);
        vector<vector<int>> o;
        
        for(int i=1; i<=n; i++)
        {
            scanf("%d", &a[i]);
            
            if( M.find(a[i])==M.end() )
            {
                M[ a[i] ]=o.size();
                o.resize(o.size()+1);
            }
            
            a[i]=M[ a[i] ];
            p[i]=o[ a[i] ].size();
            o[ a[i] ].push_back(i);
        }
        
        vector<int> X(n+1, 0);
        vector<vector<int>> P(m, vector<int>(n+1, -1));
        
        for(int k=0; k<m; k++)
        {
            vector<int> Y(n+1, 0);
            vector<stack<pair<int, int>>> S(o.size());
            
            for(int i=1; i<=n; i++)
            {
                int v=X[i-1]+o[ a[i] ].size()-p[i];
                for(; !S[ a[i] ].empty() && S[ a[i] ].top().first<v; S[ a[i] ].pop());
                S[ a[i] ].push(pair<int, int>(v, i));
            }
            
            for(int i=o.size()-1; i>=0; i--)
            {
                int l=o[i].size();
                
                for(int j=l-1; j>=0; j--)
                {
                    for(; !S[i].empty() && S[i].top().second>o[i][j]; S[i].pop());
                    
                    if( S[i].empty() )
                    {
                        printf("!!!\n");
                        Y[ o[i][j] ]=0;
                        P[k][ o[i][j] ]=0;
                    }
                    else
                    {
                        
                        if( j==l-1 )
                            Y[ o[i][j] ]=S[i].top().first;
                        else
                        Y[ o[i][j] ]=S[i].top().first-(X[ o[i][l-1] ]-X[ o[i][j]-1 ]+1);
                        P[k][ o[i][j] ]=S[i].top().second;
                    }
                }
            }
            
            for(int i=1; i<=n; i++)
                X[i]=max(X[i-1], Y[i]);
            
        }
        
        printf("%d\n", X[n]);
    }
}

/*

10 2
2 3 2 3 2 1 2 1 2 1

0 0

*/
