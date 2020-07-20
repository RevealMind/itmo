#include<bits/stdc++.h>

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    std :: string arr1, arr2;
    std :: cin >> arr1 >> arr2;
    std :: vector<std :: vector <int> > dp(arr1.size() + 1, std :: vector<int>(arr2.size() + 1));
    dp[0][0] = 0;
    for(int i = 1; i <= arr1.size(); i++)
    {
        dp[i][0] = i;
    }
    for(int i = 1; i <= arr2.size(); i++)
    {
        dp[0][i] = i;
    }
    for(int i = 1;i <= arr1.size(); i++)
        for(int j = 1;j <= arr2.size(); j++)
        {
            if(arr1[i - 1] == arr2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = std :: min(std :: min(dp[i-1][j], dp[i][j-1]),dp[i-1][j-1]) + 1;
        }
    std :: cout << dp[arr1.size()][arr2.size()];
}

