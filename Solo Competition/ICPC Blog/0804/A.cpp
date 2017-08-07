#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int n, ans=0;
    scanf("%d", &n);
    vector<int> a(n), b(n);
    
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);
    
    for(int i=0; i<n; i++)
        scanf("%d", &b[i]);
    
    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());
    for(; ans<n && a[ans]+b[ans]>0; ans++);
    printf("%d\n", ans);
}
