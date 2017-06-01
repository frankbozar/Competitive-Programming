#include<cstdio>
#include<map>
using namespace std;
map<int, int> M;

int main()
{
    int n;
    
    for(scanf("%d", &n); n>0; n--)
    {
        int x;
        scanf("%d", &x);
        M[x]++;
    }
    
    for(scanf("%d", &n); n>0; n--)
    {
        int x;
        scanf("%d", &x);
        printf("%d\n", M[x]);
    }
}
