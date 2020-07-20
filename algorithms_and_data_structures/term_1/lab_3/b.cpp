#include<bits/stdc++.h>

int main()
{

    int n, max, maxI;
    std :: cin >> n;
    std :: vector <int> arr(n), dp(n,0), out;
    dp[0] = 1;
    for(int i = 0 ; i < n; i ++)
        std :: cin >> arr[i];
    for(int i = 1; i < n ; i++)
    {
        max = 0;
        for(int j = 0; j < i; j++)
        {
            if(max < dp[j] && arr[j] < arr[i])
            {
                max = dp[j];
            }
        }
        dp[i] = max + 1;
    }
    max = 0;
    for(int i = 0; i < n; i++)
    {
        if(max < dp[i]){
            max = dp[i];
            maxI = i;
        }
    }
    out.push_back(arr[maxI]);
    int j = maxI;
    while(j >= 0 && dp[maxI] != 1)
    {
        if(dp[j] + 1 == dp[maxI])
        {
            out.push_back(arr[j]);
            maxI = j;
        }
        j--;
    }
    printf("%d\n", max);
    for(int i = out.size() - 1; i >= 0; i--)
            printf("%d ", out[i]);

}
