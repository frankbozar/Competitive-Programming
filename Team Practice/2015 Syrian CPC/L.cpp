#include<cstdio>
const int N=120000;
const int p[11]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
int a[N]={0};

int count(int x)
{
    return x==0 ? 0 : count(x>>1)+(x&1) ;
}

int prime(int x, int i=10)
{
    return x==p[i] ? 1 : i==0 ? 0 : prime(x, i-1) ;
}

int main()
{
    for(int i=1; i<N; i++)
        a[i]=a[i-1]+prime(count(i));
    
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        l= l==0 ? 0 : l-1 ;
        printf("%d\n", a[r]-a[l]);
    }
}
