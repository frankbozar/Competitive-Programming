#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

const int N = 100000;

int child[N + 2][2];
int isr[N + 2], dep[N + 2];
double L[N + 2][2], R[N + 2][2], C[N + 2][2];
double ans[N + 2][2];

void com(int u)
{
    if (child[u][0] == 0)
    {
        L[u][0] = R[u][0] = 1;
        L[u][1] = R[u][1] = 0;
        return;
    }
    int l = child[u][0], r = child[u][1];
    dep[l] = dep[u] + 1;
    com(l);
    dep[r] = dep[u] + 1;
    com(r);
    //ar+bH
    double a = R[l][0] + L[r][0], b = R[l][1] + L[r][1] + 1;
    a /= 2, b /= 2;
    C[u][0] = a, C[u][1] = b;
    L[u][0] = a + L[l][0], L[u][1] = b + L[l][1];
    R[u][0] = a + R[r][0], R[u][1] = b + R[r][1];
    //printf("u=%d %f %f %f %f %f %f\n", u, L[u][0], L[u][1], R[u][0], R[u][1], C[u][0], C[u][1]);
}

void sol(int u)
{
    if (child[u][0] == 0)
        return;
    int l = child[u][0], r = child[u][1];
    ans[l][0] = ans[u][0] - C[u][0], ans[l][1] = ans[u][1] - C[u][1];
    sol(l);
    ans[r][0] = ans[u][0] + C[u][0], ans[r][1] = ans[u][1] + C[u][1];
    sol(r);
    //printf("u=%d %f %f\n", u, ans[u][0], ans[u][1]);
}

int main(int argc)
{
    int T;
    for (scanf("%d", &T); T > 0; T--)
    {
        memset(isr, 1, sizeof(isr));
        memset(child, 0, sizeof(child));
        int n, q;
        scanf("%d%d", &n, &q);
        for (int i = 1, k; i <= n; i++)
        {
            scanf("%d", &k);
            if (k)
                scanf("%d%d", &child[i][0], &child[i][1]), isr[child[i][0]] = isr[child[i][1]] = 0;;
        }
        int root = 0;
        for (int i = 1; i <= n; i++)
            if (isr[i])
                root = i;
        dep[root] = 0;
        com(root);
        ans[root][0] = ans[root][1] = 0;
        sol(root);
        //for (int i = 1; i <= n; i++)
        //printf("dep %d %d\n", i, dep[i]);
        for (int i = 0; i < q; i++)
        {
            int r, v, h, u;
            scanf("%d%d%d%d", &r, &v, &h, &u);
            printf("%.4f %.4f\n", ans[u][0] * r + ans[u][1] * h, -dep[u] * (2.0 * r + v));
        }
    }
    return 0;
}
