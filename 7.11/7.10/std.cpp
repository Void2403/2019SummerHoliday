#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 16;
const int M = 5e4;
int n,m,full;
char s[M + 5];
int w[N + 5][N + 5],v[N + 5][N + 5];
int f[(1 << 16) + 5][N + 5];
int ans = 0x3f3f3f3f;
int main()
{
    scanf("%d%s",&n,s + 1),m = strlen(s + 1),full = (1 << n) - 1;
    for(register int i = 1;i <= m;i += n)
        for(register int j = 1;j <= n;++j)
            for(register int k = 1;k <= n;++k)
                w[j][k] += (bool)(s[i + j - 1] ^ s[i + k - 1]);
    for(register int i = 1;i + n <= m;i += n)
        for(register int j = 1;j <= n;++j)
            for(register int k = 1;k <= n;++k)
                v[j][k] += (bool)(s[i + j - 1] == s[i + n + k - 1]);
    for(register int j = 1;j <= n;++j)
    {
        memset(f,0x3f,sizeof f);
        f[1 << j - 1][j] = m / n;
        for(register int i = 0;i <= full;++i)
            if(i & (1 << j - 1))
                for(register int k = 1;k <= n;++k)
                    if(i & (1 << k - 1))
                        for(register int l = 1;l <= n;++l)
                            if(!(i & (1 << l - 1)))
                                f[i | (1 << l - 1)][l] = min(f[i | (1 << l - 1)][l],f[i][k] + w[k][l]);
        for(register int i = 1;i <= n;++i)
            ans = min(ans,f[full][i] - v[i][j]);
    }
    printf("%d\n",ans);
}
