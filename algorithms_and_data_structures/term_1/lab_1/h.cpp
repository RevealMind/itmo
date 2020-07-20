#include<bits/stdc++.h>

int arr[30000001];

int findKSt(int *arr, int l, int r, int k)
{
    int i = l, j = r, key = arr[rand() % (r - l + 1) + l];

    while (i <= j)
    {
        while (arr[i] < key)
            i++;
        while (arr[j] > key)
            j--;
        if (i <= j)
        {
           std::swap(arr[i],arr[j]);
            i++;
            j--;
        }
    }
    if (l <= k && k <= j)
        return findKSt(arr, l, j, k);
    else if (i <= k && k <= r)
        return findKSt(arr, i, r, k);
    return arr[k];
}





int main()
{
    srand(242453);
    freopen("kth.in","r",stdin);
    freopen("kth.out","w",stdout);
    int n, k, A, B, C , a1, a2;

    std :: cin >> n >> k >> A >> B >> C >> a1 >> a2;
    arr[0]=a1;
    arr[1]=a2;

    if (n == 1)
    {
        std :: cout << arr[0];
        return 0;
    }

    for(int i = 2; i < n; i++)
    {
        arr[i] = A * arr[i-2] + B * arr[i-1] + C;
    }

    std :: cout << findKSt(arr, 0, n-1, k-1);
}
