#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

const int N = 100000;

struct node
{
    node *nx[26];
    int cnt, sum;
    node()
    {
        memset(this, 0, sizeof(node));
    }
    ~node()
    {
        for (int i = 0; i < 26; i++)
            if (nx[i])
                delete nx[i];
    }
};

char *S[N + 2];
char str[N + 2];
node *root;
int A[N + 2], B[N + 2], C[N + 2], len[N + 2];

void add(char *s)
{
    node *now = root;
    for (int i = 0; s[i]; i++)
    {
        //printf("i=%d %c %d\n", i, s[i], s[i]-'a');
        if (now->nx[s[i] - 'a'] == NULL)
            now->nx[s[i] - 'a'] = new node();
        now = now->nx[s[i] - 'a'];
    }
    now->cnt++;
}

void getsum(node *p)
{
    p->sum = p->cnt;
    for (int i = 0; i < 26; i++)
        if (p->nx[i] != NULL)
            getsum(p->nx[i]), p->sum += p->nx[i]->sum;
}

int sol(int k)
{
    int l = len[k];
    char *s = S[k];
    for (int i = 0; i < l + 2; i++)
        A[i] = B[i] = C[i] = 0;
    node *now = root;
    for (int i = 0; s[i]; i++)
    {
        A[i] = now->sum;
        B[i] = now->cnt;
        for (int j = 0; j < s[i] - 'a'; j++)
            if (now->nx[j] != NULL)
                C[i] += now->nx[j]->sum;
        now = now->nx[s[i] - 'a'];
    }
    for (int i = l - 2; i >= 0; i--)
        B[i] += B[i + 1], C[i] += C[i + 1];
    int res = l + 1;
    for (int i = 0; i < l; i++)
    {
        int all = A[i], ord = B[i] + C[i];
        res = min(res, i + 1 + min(ord, 1 + (all - ord - 1)));
    }
    return res;
}

int main()
{
    int T;
    for (scanf("%d", &T); T > 0; T--)
    {
        root = new node();
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
        {
            scanf("%s", str);
            add(str);
            len[i] = strlen(str);
            S[i] = new char[len[i] + 1];
            strcpy(S[i], str);
        }
        getsum(root);
        for (int i = 0; i < n; i++)
            printf("%d%s", sol(i), i == n - 1 ? "\n" : " "), delete S[i];
        delete root;
    }
}
