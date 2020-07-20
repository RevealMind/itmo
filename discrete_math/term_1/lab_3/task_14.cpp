#include<bits/stdc++.h>
std :: vector <int> arr;
std :: vector<bool> used(19, false);
long long Fact(int n)
{
    long long ans = 1LL;
    for(int i = 2; i <= n; i++)
        ans *= i;
    return ans;
}
int main()
{
    freopen("perm2num.in","r",stdin);
    freopen("perm2num.out","w",stdout);
    int n;
    std :: cin >> n;
    arr.resize(n);
    for(int i = 0; i < n; i++)
        std :: cin >> arr[i];
    long long ans = 0;
    for(int i = 0; i < n; i++)
    {
        int j = 1;
        long long k = 0LL;
        while(j < arr[i])
        {
            if(!used[j])
                ++k;
            ++j;
        }
        ans += k * Fact(n - i - 1);
        used[arr[i]] = true;
    }
    std :: cout << ans;
}
