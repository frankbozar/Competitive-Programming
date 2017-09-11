#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int, int> data;

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> a(n, 0), c(n, 0);
    vector<data> b;
    
    for(int i=0; i<n; i++)
    {
        scanf("%d", &a[i]);
        b.push_back(data(a[i], i));
    }
    
    sort(b.begin(), b.end());
    
    for(int i=0; i<n; i++)
        c[ b[i].second ]=i;
    
    vector<vector<int>> ans;
    
    for(int i=0; i<n; i++)
    {
        if( c[i]<0 )
            continue;
        
        ans.resize(ans.size()+1);
        
        for(int j=i; j>=0; )
        {
            ans.back().push_back(j);
            int t=c[j];
            c[j]=-1;
            j=t;
        }
    }
    
    printf("%lu\n", ans.size());
    
    for(auto& it : ans)
    {
        it.pop_back();
        printf("%lu", it.size());
        
        for(int x : it)
            printf(" %d", x+1);
        
        printf("\n");
    }
}
