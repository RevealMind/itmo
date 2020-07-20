#include<bits/stdc++.h>
int n, k;
void next(std :: vector<int> arr)
{
    std :: vector <int> next(k + 1);
    for(int i = 0; i < k ; i++)
        next[i] = arr[i];
    next[k] = n + 1;
    int cur = -1;
    for(int i = k - 1; i >= 0; i--)
    {
        if(next[i + 1] - next[i] >= 2)
       {
           cur = i;
           break;
       }
    }
    if(cur >= 0)
    {
        next[cur]++;
        for(int i = cur + 1; i < k; i++)
            next[i] = next[i - 1] + 1;
        for(int i = 0; i < k; i++)
            std :: cout << next[i] << " ";
        return;
    }
    else
        std :: cout << "-1";
}
int main()
{
    freopen("nextchoose.in","r",stdin);
    freopen("nextchoose.out","w",stdout);
    std :: cin >> n >> k;
    std :: vector <int> arr(k);
    for(int i = 0; i < k; i++)
        std :: cin >> arr[i];
    next(arr);
}
