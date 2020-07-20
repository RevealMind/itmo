#include<bits/stdc++.h>

int partition(std :: vector <int> &arr, int l, int r)
{
    srand(2424);
    int sw = (rand()%(r-l+1))+l;
    std :: swap(arr[sw], arr[r]);
    int x = arr[r];
    int i = l - 1;
    for(int j = l; j <= r-1; j++)
    {
        if(arr[j] <= x)
        {
            i++;
            std :: swap(arr[i], arr[j]);
        }
    }
    std :: swap(arr[i+1], arr[r]);
    return i+1;
}

void sort(std :: vector <int> &arr, int l, int r)
{
    if(l < r)
    {
        int q = partition(arr, l, r);
        sort(arr, l, q-1);
        sort(arr, q+1, r);
    }
}




int main()
{
    freopen("sort.in","r",stdin);
    freopen("sort.out","w",stdout);

    int n;


    std :: cin >> n;

    std :: vector <int> arr;

    for(int i = 0; i < n; i++)
    {
        int x;
        std :: cin >> x;
        arr.push_back(x);
    }

    sort(arr, 0, arr.size()-1);

    for(int i = 0; i < n; i++)
        std :: cout << arr[i] << " ";
}
