#include<bits/stdc++.h>
int n,k,m;
int main()
{
    freopen("choose2num.in","r",stdin);
    freopen("choose2num.out","w",stdout);
    std :: cin >> n >> k;
    std :: vector <long long> arr(n, 0LL);
    for(int i = 1; i <= k; i++)
        scanf("%d", &arr[i]);
    m++;
    std :: vector  <std :: vector <long long> > c(n, std :: vector<long long> (k));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j <= i && j < k; j++)
        {
            if(i == j || j == 0)
                c[i][j] = 1;
            else
                c[i][j] = c[i-1][j]+c[i-1][j-1];
        }
    }
    long long number = 0LL;
    for(int i = 1; i <= k; i++)
    {
        for(int j = arr[i - 1] + 1; j < arr[i]; j++)
            number += c[n - j][k - i];
    }
    std :: cout << number;
}
