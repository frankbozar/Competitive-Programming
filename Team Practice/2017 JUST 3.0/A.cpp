#include<cstdio>

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", a*100/(100+b));
    }
}
