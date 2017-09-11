#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    vector<int> a(n<<1);
    
    for(int i=0; i<n<<1; i++)
        scanf("%d", &a[i]);
    
    sort(a.begin(), a.end());
    printf(a[n]>a[n-1] ? "YES\n" : "NO\n");
}
