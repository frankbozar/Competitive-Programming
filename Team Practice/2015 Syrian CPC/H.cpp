#include<cstdio>
#include<algorithm>
using namespace std;

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        int w=max(x, y);
        printf("%d\n", w*w);
    }
}
