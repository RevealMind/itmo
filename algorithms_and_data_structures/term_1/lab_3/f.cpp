#include<bits/stdc++.h>

int main()
{
    std :: string str;
    std :: cin >> str;
    std :: vector<std :: vector<int> > dp(str.size(), std :: vector<int>(str.size()));
    int minimum;
    char close,open;
    for(int e = 0; e < str.size(); e++)
        for(int b = e; b >= 0; b--)
        {
            if(b != e)
            {
                minimum = 1000000000;
                close = str[e]; open = str[b];
                if(close-open >= 1 && close-open<= 2)
                    minimum = dp[b + 1][e - 1];
                for(int k = b; k < e; k++)
                    if(dp[b][k] + dp[k+1][e] < minimum)
                        minimum = dp[b][k] + dp[k+1][e];
                dp[b][e] = minimum;
            }
            else
                dp[b][e] = 1;
        }
    std :: cout << str.size() - dp[0][str.size()-1];
}
