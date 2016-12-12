#include<cstdio>
#include<bitset>
using namespace std;

int f(const bitset<32>& S)
{
    return 1<<(30-S.count());
}

int solution(int a, int b, int c)
{
    return f(a)+f(b)+f(c)-f(a|b)-f(b|c)-f(c|a)+f(a|b|c);
}

int main()
{
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    printf("%d\n", solution(a, b, c));
}

/*

1073741727
1073741631
1073741679

*/