#include<bits/stdc++.h>

std :: vector <int> a(100000);

int n,k;
int binSearchD(int key)
{
    int l = -1;
    int r = n;
    while(l < r - 1)
    {
        int m = (l + r) / 2;
        if(a[m] < key)
            l = m;
        else
            r = m;
    }
    if(key != a[r])
        return -1;
    else
        return r+1;
}

int binSearchU(int key)
{
    int l = -1;
    int r = n;
    while(l < r - 1)
    {
        int m = (l + r) / 2;
        if(a[m] <= key)
            l = m;
        else
            r = m;
    }
    if(key != a[r-1])
        return -1;
    else
        return r;
}

int main()
{
    freopen("binsearch.out","w",stdout);
    freopen("binsearch.in", "r", stdin);

    std :: cin >> n;

    for(int i = 0; i < n; i++)
    {
        std :: cin >> a[i];
    }

    std :: cin >> k;

    for(int i = 0; i < k; i++)
    {
      int key;
      std :: cin >> key;
      std :: cout << binSearchD(key) << " " << binSearchU(key)<< std :: endl;
    }

}
