#include<cstdio>

int main()
{
    int n;
    scanf("%d", &n);
    printf("+-----+\n");
    printf("|%-1s%4s|\n", n<20 ? "" : "-", n>=90 ? "4G" : n>=60 ? "3G" : "E");
    printf("|%-5s|\n", n< 40 ? "" : "--");
    printf("|%-5s|\n", n< 60 ? "" : "---");
    printf("|%-5s|\n", n< 80 ? "" : "----");
    printf("|%-5s|\n", n<100 ? "" : "-----");
    printf("+-----+\n");
}
