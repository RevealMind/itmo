#include<bits/stdc++.h>
const int MAX = 214748364, undef = -1;
bool is_pair(char op, char cl)
{
    return cl-op >= 1 && cl - op <= 2; // ')' - '(' = 1; other = 2
}
int minint(int i, int j){
    return j < i? j : i ;
}
void init(std :: vector<auto> &dp, int n, std :: string cmd, std :: vector<auto> &way)
{
    int min, ind;
    for(int i = 0; i < n; i++)
        dp[i][i] = 1;
    for(int j = 0; j < n; j++)
        for(int i = j; i >= 0; i--)
        {
            if(i != j)
            {
                min = MAX;
                ind = undef;
                if(is_pair(cmd[i], cmd[j]))
                    min = dp[i + 1][j - 1];
                for(int k = i; k < j; k++)
                    if(dp[i][k] + dp[k + 1][j] < min){
                            min = dp[i][k] + dp[k + 1][j];
                            ind = k;
                }

                dp[i][j] = min;
                way[i][j] = ind;
            }
        }
}
void print(std :: vector <auto> arr)
{
    for(int i = 0; i < arr.size(); i++){
        for(int j = 0; j < arr[i].size(); j++) std :: cout << arr[i][j] << " ";
        std :: cout << "\n";
    }

}

void printsub(std :: string cmd, int i, int j)
{
    for(int k = i; k <= j; k++) printf("%c", cmd[k]);
}
void answer(std :: vector<auto> dp, std :: vector<auto> way, std :: string cmd, int i, int j)
{
    if(dp[i][j] == j - i + 1) return;
    else if(dp[i][j] == 0){
        printsub(cmd, i , j);
        return;
    }
    if(way[i][j] == undef){
        printf("%c", cmd[i]);
        answer(dp, way, cmd, i + 1, j - 1);
        printf("%c", cmd[j]);
        return;
    }
    answer(dp, way, cmd, i, way[i][j]);
    answer(dp, way, cmd, way[i][j] + 1, j);
}
int main()
{
    //freopen("input.txt","r",stdin);
    std :: string cmd;
    std :: getline(std :: cin, cmd);
    int n = cmd.size();
    std :: vector<std :: vector<int> > dp(n, std :: vector<int>(n)), way(n, std :: vector<int>(n));
    init(dp, n, cmd, way);
//    print(dp);
//    std :: cout << "\n";
//    print(way);
    answer(dp, way, cmd, 0, n - 1);
    //std :: cout << n - dp[0][n - 1];
}
