#include<bits/stdc++.h>

int main()
{
    int n;
    std :: cin >> n;
    std :: vector<std :: vector<long long> > dp(n + 1, std :: vector<long long>(10, 1));
    dp[0][5] = 0;
    dp[0][8] = 0;
    dp[0][0] = 0;
    for(int i = 2; i <= n; i++)
    {
        dp[i][0] = (dp[i - 1][4] + dp[i - 1][6]) % 1000000000;
        dp[i][1] = (dp[i - 1][8] + dp[i - 1][6]) % 1000000000;
        dp[i][2] = (dp[i - 1][7] + dp[i - 1][9]) % 1000000000;
        dp[i][3] = (dp[i - 1][4] + dp[i - 1][8]) % 1000000000;
        dp[i][4] = (dp[i - 1][0] + dp[i - 1][3] + dp[i - 1][9]) % 1000000000;
        dp[i][6] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][7]) % 1000000000;
        dp[i][7] = (dp[i - 1][2] + dp[i - 1][6]) % 1000000000;
        dp[i][8] = (dp[i - 1][1] + dp[i - 1][3]) % 1000000000;
        dp[i][9] = (dp[i - 1][2] + dp[i - 1][4]) % 1000000000;
    }

    int ans = (n == 1)? 1:0;
    for(int i = 0; i <=9; i++)
        if(i != 0 && i != 8 && i!= 5)
            ans = (ans + dp[n][i]) % 1000000000;

    std :: cout <<  ans;
}
