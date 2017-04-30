#include<cstdio>
#include<set>
#include<map>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
#define data pair<int,int>
#define d first
#define t second
char s[1<<20];

bool check(vector<data>& a)
{
    sort(a.begin(), a.end());
    int n=a.size();
    
    for(int i=0; i<n; i+=2)
        if( a[i].t!=-1 || a[i+1].t!=1 )
            return false;
    
    return true;
}

int main()
{
    int N, n;
    
    for(scanf("%d", &N); N>0; N--)
    {
        map<string, vector<data>> M;
        
        for(scanf("%d", &n); n>0; n--)
        {
            int l, r, k;
            
            for(scanf("%*s%d%d%d", &l, &r, &k); k>0; k--)
            {
                scanf("%s", s);
                M[s].push_back(data(r, 1));
                M[s].push_back(data(l, -1));
            }
        }
        
        set<string> S;
        
        for(auto& it : M)
            if( !check(it.second) )
                S.insert(it.first);
        
        printf("%lu\n", S.size());
        
        for(const string& s : S)
            printf("%s\n", s.c_str());
    }
}
