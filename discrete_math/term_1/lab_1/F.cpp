#include<bits/stdc++.h>

int main()
{
    int _n,x,n = 1;
    std :: cin >> _n;
    for(int i = 0; i < _n ; i++)
        n *= 2;
    std :: vector <std :: vector<int> > arr(n);
    std :: string str[n];
    for(int i = 0; i < n; i++)
        {
            std :: cin >> str[i] >> x;
            arr[0].push_back(x);
        }

    for(int i = 1 ; i < n; i++)
    {
        for(int j = 0 ; j < arr[i-1].size()-1; j++)
            {
                x = (arr[i-1][j] + arr[i-1][j+1])%2;
                arr[i].push_back(x);
            }
    }

    for(int i = 0 ; i< n; i++)
        std :: cout << str[i] << " " <<  arr[i][0] << "\n";
}
