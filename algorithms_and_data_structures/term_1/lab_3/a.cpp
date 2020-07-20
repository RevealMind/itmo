#include<bits/stdc++.h>

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n, k, max;
    scanf("%d %d", &n, &k);
    std :: vector<int> dp(n + 1, 0);
    std :: vector<int> cmd(n + 1, 0);
    std :: vector<int> way(n + 1, 0), out;
    for(int i = 2; i < n; i++)
        scanf("%d" , &cmd[i]);
    for(int i = 2; i <= n; i++)
    {
        max = i - 1;
        for(int j = std :: max(i - k, 1); j < i; j++)
            if(dp[max] < dp[j])
                max = j;
        dp[i] = dp[max] + cmd[i];
        way[i] = max;
    }
    out.push_back(n);
    int i = n;
    do
    {
        i = way[i];
        out.push_back(i);
    }while(i > 1);
    printf("%d\n%d\n", dp[n], out.size() - 1);
    for(int i = out.size() - 1; i >=  0; i--)
        printf("%d ", out[i]);
}
