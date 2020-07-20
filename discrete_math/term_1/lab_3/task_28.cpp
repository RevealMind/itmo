#include<bits/stdc++.h>
int n;
std :: vector <int> arr;
void swap(int i, int j)
{
    int t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}


void next()
{
    int cur = n - 2 ;
    for(int i = n - 2; i >= 0; i--, cur--)
    {
        if(arr[i] < arr[i + 1])
            break;

    }

    if(cur >= 0)
    {
        int min = cur + 1;
        for(int i = cur + 1; i < n - 1; i++ , min++)
        {
            if(arr[i + 1] <= arr[cur])
                break;
        }
        //std :: cout << cur << " " << min << "\n";
        swap(cur,min);
        int k = cur + 1;
        int t = n - 1;
        while (k < t)
        {
           swap(k,t);
           k++;
           t--;
        }
        for(int i = 0; i < n; i++)
            std :: cout << arr[i] << " ";
    }
    else
    {
        for(int i = 0; i < n; i++)
            std :: cout << "0 ";
    }
}
int main()
{
    freopen("nextmultiperm.in","r",stdin);
    freopen("nextmultiperm.out","w",stdout);
    std :: cin >> n;
    arr.resize(n);
    for(int i = 0; i < n; i++)
        std :: cin >> arr[i];
    next();
}
