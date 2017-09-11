#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int,int> tv;

int main()
{
    int n, p=0, v=0;
    scanf("%d", &n);
    vector<tv> a;
    
    for(int i=0; i<n; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        a.push_back(tv(l, -1));
        a.push_back(tv(r, 1));
    }
    
    sort(a.begin(), a.end());
    
    for(const tv& T : a)
    {
        p+=T.second;
        v=min(v, p);
    }
    
    printf(v<-2 ? "NO\n" : "YES\n");
}
