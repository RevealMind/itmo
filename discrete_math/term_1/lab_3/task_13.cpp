#include<bits/stdc++.h>
int n;
long long Fact(int n)
{
    long long ans = 1LL;
    for(int i = 2; i <= n; i++)
        ans *= i;
    return ans;
}
std :: vector<bool> arr(19, false);
void num2perm(long long k)
{
    std :: vector<int> ans;
    for(int i = 0; i < n; i++)
    {
        long long fact = Fact(n - i - 1);
        long long num = k / fact + 1;
        long long j = 1LL;
        long long cur = 0LL;
        while(j <= n)
        {
            if(!arr[j])
                ++cur;
            if(cur == num)
            {
                ans.push_back(j);
                arr[j] = true;
                k = k % fact;
                break;
            }
            ++j;
        }
    }
    for(int i = 0; i < n; i++)
        printf("%d ", ans[i]);
}
int main()
{
    freopen("num2perm.in","r",stdin);
    freopen("num2perm.out","w",stdout);
    long long num;
    std :: cin >> n >> num;
    num2perm(num);
}
