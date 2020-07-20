#include<bits/stdc++.h>

std :: vector <std :: vector <long long> > dp;

std :: string cmd;
void init(int n)
{
    dp[0][0] = 1LL;
    for(int i = 1; i < 2 * n; i++)
    {
        for(int j = 0; j <= n; j++)
        {
            if(j - 1 >= 0)
                dp[i][j] += dp[i - 1][j - 1];
            if(j + 1 <= n)
                dp[i][j] += dp[i - 1][j + 1];
        }
    }
}

void printArr(std :: vector <auto> arr)
{
    printf("   ");
    for(int i = 0; i < arr[0].size(); i++)
        printf("%02d ", i);
    printf("\n");
    for(int i = 0; i < arr.size(); i++){
        printf("%02d ", i);
        for(int j = 0; j< arr[i].size(); j++)
            printf("%02lld ", arr[i][j]);
        printf("\n");
    }
}

void print(long long n)
{
    printf("%lld\n", n);
}

void gen(int n)
{
    int deep = 0, ndeep;
    long long num = 0;
    init(n);
    std :: string stack;
    for(int i = 0; i < 2 * n; i++)
    {
        if(cmd[i] == '('){
            stack.push_back('(');
            deep++;
            continue;
        }


        if(deep < n){
            ndeep = deep + 1;
            num += ((dp[2 * n - i - 1][ndeep]) << ((2 * n - i - 1 - ndeep)/2));
        }

        if(cmd[i] == ')')
        {
            stack.erase(stack.end() - 1);
            deep--;
            continue;
        }

        if(!stack.empty() && stack[stack.size() - 1] == '(' && deep > 0){
            ndeep = deep - 1;
            num += ((dp[2 * n - i - 1][ndeep]) << ((2 * n - i - 1 - ndeep)/2));
            continue;
        }

        if(cmd[i] == '['){
            stack.append("[");
            deep++;
            continue;
        }


        if(deep < n){
            ndeep = deep + 1;
            num += ((dp[2 * n - i - 1][ndeep]) << ((2 * n - i - 1 - ndeep)/2));
        }

        if(cmd[i] == ']')
        {
            stack.erase(stack.end() - 1);
            deep--;
            continue;
        }
    }
    std :: cout << num;
}

int main()
{
    freopen("brackets2num2.in","r ",stdin);
    freopen("brackets2num2.out","w",stdout);
    int n;
    long long k;
    std :: cin >> cmd;
    n = cmd.size() / 2;
    dp.resize(2*n, std :: vector <long long> (n + 1,0LL));
    gen(n);
    //printArr(dp);
}
