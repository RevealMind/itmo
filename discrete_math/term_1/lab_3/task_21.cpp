#include<bits/stdc++.h>

int main()
{
    freopen("num2part.in","r",stdin);
    freopen("num2part.out","w",stdout);
    int n;
    long long k;
    std :: cin >> n >> k;
    k++;
    long long dp[n + 1][n + 1] = {0}; // dp[i][j] - кол-вр разбиений числа i, начинающихся с разбиения, которое содержит j слагаемое
    for(int i = 1; i <= n; i ++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(i != j)
            {
                for(int k = j ; k <= i; k++)
                {
                    dp[i][j] += dp[i-j][k]; // шаг
                }
            }
            else
            {
                dp[i][i] = 1; // база
            }
        }
    }

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            std :: cout << dp[i][j] << " ";
        }
        std :: cout << std :: endl;
    }

    int i = n;
    int j = 1;
    while(i != j)
    {
        if(dp[i][j] >= k)
        {
            printf("%d+", j);
            i -= j;
            continue;
        }
        else
        {
            k -= dp[i][j];
            j++;
            continue;
        }
    }
    std :: cout << j;
}
