#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int,int> data;

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> a(n+1);
    
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);
    
    a[n]=a[0];
    vector<data> b;
    
    for(int i=0; i<n; i++)
        b.push_back(data(n-a[i]-a[i+1], i));
    
    sort(b.begin(), b.end());
    vector<int> ans(n);
    
    for(int i=0; i<n; i++)
        ans[ b[i].second ]=n-i-1;
    
    for(int i=0; i<n; i++)
        printf(i==n-1 ? "%d\n" : "%d ", ans[i]);
}
