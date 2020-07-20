#include<bits/stdc++.h>

int main()
{
    freopen("num2brackets.in","r",stdin);
    freopen("num2brackets.out","w",stdout);
    int deep = 0, n;
    long long k;
    std :: cin >> n >> k;
    k++;
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
    /*for(int i = 0; i < 2*n; i++)
    {
        for(int j = 0; j < n + 1; j++)
            std :: cout << dp[i][j] << " ";
        std :: cout << "\n";
    }*/

    for(int i = 2 * n - 1; i >= 0; i--)
    {
        if(deep + 1 <= n && dp[i][deep + 1] >= k)
        {
            printf("(");
            deep++;
        }
        else
        {
            printf(")");
            if(deep + 1 <= n)
                 k -= dp[i][deep + 1];
            deep--;
        }
    }
}
