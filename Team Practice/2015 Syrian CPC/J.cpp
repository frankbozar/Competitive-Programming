#include<cstdio>
#include<set>
#include<map>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
vector<vector<int>> dep;
char s[1<<20];

void solve(set<int>& S, int u)
{
    if( S.find(u)!=S.end() )
        return ;
    
    S.insert(u);
    
    for(int v : dep[u])
        solve(S, v);
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        dep.clear();
        dep.resize(n);
        vector<string> str(n);
        map<string, int> M;
        
        for(int i=0; i<n; i++)
        {
            int k;
            scanf("%s%d", s, &k);
            str[i]=s;
            M[s]=i;
            
            for(; k>0; k--)
            {
                scanf("%s", s);
                
                if( M[s]!=i )
                    dep[i].push_back(M[s]);
            }
        }
        
        set<int> S;
        
        for(; m>0; m--)
        {
            scanf("%s", s);
            solve(S, M[s]);
        }
        
        for(int i : S)
            printf("%s\n", str[i].c_str());
    }
}
