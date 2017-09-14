#include<cstdio>

int main()
{
    int N;

    for(scanf("%d", &N); N>0; N--)
    {
        int n;
        scanf("%d", &n);
        printf(90000/50>=n*120 ? "KFCCA\n" : "PCCA\n");
    }
}

/*

2
5
40

*/
