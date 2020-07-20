#include<bits/stdc++.h>
const int MAX = 1000000000;
int min(int a, int b){
    return (a < b)? a : b;
}

void init(int &n, std :: vector<auto> &arr, std :: vector<auto> &dp)
{
    int x;
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &x);
        arr.push_back(x);
    }

    dp[0][0] = 0;
    for(int i = 1; i <= n; i++)
        for(int j = 0; j <= n; j++){
            if(arr[i - 1] <= 100){
                dp[i][j] = min(dp[i - 1][j] + arr[i - 1], (j < n)?  dp[i - 1][j + 1]: MAX);
            }
            else
                dp[i][j] = min((j > 0)? dp[i - 1][j - 1] + arr[i - 1] : MAX, (j < n)?  dp[i - 1][j + 1]: MAX);
        }
    /*for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++)
            printf("%d ", (dp[i][j] == MAX)? -1 : dp[i][j]);
        std :: cout << "\n";
    }*/

}

void print(std :: vector<auto> arr)
{
    for(int i = 0; i < arr.size();i++)
        printf("%d ", arr[i]);
}
int main()
{
    int n, k1, k2 = 0, min = MAX;
    std :: cin >> n;
    std :: vector<int> cost, out;
    std :: vector<std :: vector <int> > dp(n + 1, std :: vector<int> (n + 1, MAX));
    init(n, cost, dp);

    for(int i = 0; i <= n; i++){
        if(dp[n][i] <= min){
            min = dp[n][i];
            k1 = i;
        }
    }

    std :: cout << min << "\n" << k1;
    int j = k1;
    for(int i = n; i > 1; i--){
        if(cost[i - 1] <= 100){
            if(j < n && dp[i - 1][j + 1] == dp[i][j]){
                j++;
                k2++;
                out.push_back(i);
            }
        }
        else{
            if(j < n && dp[i - 1][j + 1] == dp[i][j]){
                j++;
                k2++;
                out.push_back(i);
            }
            else{
                j--;
            }
        }
    }
    std :: cout << " " << k2 << "\n";
    for(int i = out.size() - 1; i >= 0; i--)
        std :: cout << out[i] << "\n";
}
