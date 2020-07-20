#include<bits/stdc++.h>
int n,k,m;
int main()
{
    freopen("num2choose.in","r",stdin);
    freopen("num2choose.out","w",stdout);
    std :: cin >> n >> k >> m;
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
    /*for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < c[i].size(); j++)
            std :: cout << c[i][j] << " ";
        std :: cout <<"\n";
    }*/
    int count = 1;
    for(int i = 1; i <= n && count <= k; i++)
    {
        if(c[n-i][k-count] < m)
        {
            m -= c[n-i][k-count];
        }
        else
        {
            std :: cout << i << " ";
            count++;
        }
    }
}

