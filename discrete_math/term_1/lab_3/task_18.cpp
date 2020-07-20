#include<bits/stdc++.h>

int main()
{
    freopen("brackets2num.in","r",stdin);
    freopen("brackets2num.out","w",stdout);
    int deep = 0, n;
    std :: string br;
    long long k = 0LL;
    std :: cin >> br;
    n = br.size();
    std :: vector <std :: vector <long long> > dp(2*n, std :: vector <long long> (n + 1,0LL));
    dp[0][0] = 1LL;
    for(int i = 1; i < 2 * n; i++)
    {
        for(int j = 0; j <= n; j++)
        {
            if(j - 1 >= 0)
                dp[i][j] += dp[i - 1][j - 1];
            if(j + 1 <= n)
                dp[i][j] += dp[i - 1][j + 1];
        }
    }

    for(int i = n - 1; i >= 0; i--)
    {
        if(br[n - i - 1] == '(')
        {
            deep++;
        }
        else
        {
            k += dp[i][deep + 1];
            deep--;
        }
    }
    std :: cout << k;
}
