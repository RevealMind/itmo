#include<bits/stdc++.h>
const int undef = -1, inf = 1000000000;

int min(int i, int j)
{
    return i < j? i : j;
}
void printm(std :: vector<auto> m)
{
    for(int i = 0; i < m.size(); i++){
        for(int j = 0; j < m[i].size(); j++)
            printf("%d ", m[i][j]);
        printf("\n");
    }
}
int main()
{
    //freopen("input.txt","r",stdin);
    int n;
    scanf("%d", &n);
    if(n == 1){
        printf("0\n1");
        return 0;
    }
    std :: vector < std :: vector<int> > arr(n, std :: vector<int> (n));
    std :: vector < std :: vector<std :: vector<int> > >  dp(13 , std :: vector<std :: vector<int> > (13 , std :: vector<int>(1 << n, undef))), way(13 , std :: vector<std :: vector<int> > (13 , std :: vector<int>(1 << n, undef)));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &arr[i][j]);
    for(int i = 0; i < n; i++)
        dp[0][i][1 << i] = 0;
    for(int step = 0; step < n; step++)
        for(int from = 0; from < n; from++){
            for(int mask = 0; mask < (1<<n); mask++){
                    if(dp[step][from][mask] != undef){
                        for(int to = 0; to < n; to++){
                            if(from == to || (mask & (1 << to)) != 0) continue;
                            if(dp[step][from][mask] + arr[from][to] < dp[step + 1][to][mask | (1 << from)] || dp[step + 1][to][mask | (1 << from)] == undef)
                            {
                                way[step + 1][to][mask | (1 << from)] = from;
                                dp[step + 1][to][mask | (1 << from)] = dp[step][from][mask] + arr[from][to];
                            }
                        }

                    }
            }
        }
    int min = inf, ind;
    for(int i = 0; i < n; i++)
        if(dp[n - 1][i][((1 << n) - 1) ^ (1 << i)] != undef && dp[n - 1][i][((1 << n) - 1) ^ (1 << i)] <= min){
            min  = dp[n - 1][i][((1 << n) - 1) ^ (1 << i)];
            ind = i;
        }
    printf("%d\n%d ", min, ind + 1);
    int mask = ((1 << n) - 1) ^ (1 << ind);
    for(int i = n - 1; i > 0; i--)
    {
        ind = way[i][ind][mask];
        mask = mask ^ (1 << ind);
        printf("%d ", ind + 1);
    }
    return 0;
}
