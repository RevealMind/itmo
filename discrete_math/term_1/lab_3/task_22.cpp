#include<bits/stdc++.h>

int main()
{
    freopen("part2num.in","r",stdin);
    freopen("part2num.out","w",stdout);

    std :: vector <long long> arr;
    long long x, n = 0LL;
    while(std :: cin >> x)
    {
        arr.push_back(x);
        n += x;
    }
    /*for(int i = 0; i < n; i++)
        printf("%lld ", arr[i]);*/
    long long  dp[n + 1][n + 1] = {0}; // dp[i][j] - кол-вр разбиений числа i, начинающихся с разбиения, которое содержит j слагаемое
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

//    for(int i = 1; i <= n; i++)
//    {
//        for(int j = 1; j <= n; j++)
//        {
//            std :: cout << dp[i][j] << " ";
//        }
//        std :: cout << std :: endl;
//    }

    long long number = 0LL;
    int add = 1; //слагамое(мин)
    for(int i = 0; i < arr.size(); i++)
    {
        for(; add < arr[i]; add++)
        {
            number += dp[n][add];
        }
        n -= add;
    }
    std :: cout << number;
}

