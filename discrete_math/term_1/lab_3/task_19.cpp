#include<bits/stdc++.h>

std :: vector <std :: vector <long long> > dp;

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

void gen(int n, long long k)
{
    int deep = 0, ind = 0;
    long long cur;
    init(n);
    char stack[2*n];
    for(int i = 2 * n - 1; i >= 0; i--)
    {
//---------------------------------------------------------------
        if(deep + 1 <= n){
            cur = ((dp[i][deep + 1]) << ((i - deep - 1)/2));
        }
        else{
            cur = 0LL;
        }

        if(cur >= k){
            printf("(");
            stack[ind] = '(';
            ind++;
            deep++;
            continue;
        }

        k -= cur;
 //---------------------------------------------------------------
        if(ind > 0 && stack[ind - 1] == '(' && deep - 1 >= 0){
            cur = ((dp[i][deep - 1]) << ((i - deep + 1)/2));
        }
        else{
            cur = 0LL;
        }

        if(cur >= k){
            printf(")");
            ind--;
            deep--;
            continue;
        }

        k -= cur;
//---------------------------------------------------------------
        if(deep + 1 <= n){
            cur = ((dp[i][deep + 1]) << ((i - deep - 1)/2));
        }
        else{
            cur = 0LL;
        }
        if(cur - k >= 0){
            printf("[");
            stack[ind] = '[';
            ind++;
            deep++;
            continue;
        }

        k -= cur;

        printf("]");
        ind--;
        deep--;
    }
}

int main()
{
    freopen("num2brackets2.in","r",stdin);
    freopen("num2brackets2.out","w",stdout);
    int n;
    long long k;
    std :: cin >> n >> k;
    dp.resize(2*n, std :: vector <long long> (n + 1,0LL));
    gen(n, k + 1);
    //printArr(dp);
}
