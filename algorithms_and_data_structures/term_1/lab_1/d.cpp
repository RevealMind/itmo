#include<bits/stdc++.h>


void sort(std :: string *arr,int n,int m, int k)
{
    int c[26];

    for(int i = 0; i < k; i++)
    {
        for(int j = 0; j < 26; j++)
            c[j] = 0;

        for(int j =0; j < n; j++)
        {
            int d = (int)(arr[j][m-i-1] - 'a');

            c[d]++;
        }

        int count = 0;

        for(int j = 0;  j < 26; j++)
        {
            int tmp = c[j];
            c[j] = count;
            count += tmp;
        }

        std :: string b[n];
        for(int j = 0; j < n; j++)
        {
            int d = (int)(arr[j][m-i-1] - 'a');
            b[c[d]] = arr[j];
            c[d]++;
        }
        for(int i = 0; i < n; i++)
            arr[i] = b[i];
    }


}

int main()
{
    freopen("radixsort.out","w",stdout);
    freopen("radixsort.in", "r", stdin);
    int n, m, k;

    std ::cin >> n >> m >> k;

    std :: string arr[n];

    for(int i = 0; i < n; i++)
    {
        std :: cin >> arr[i];
    }

    sort(arr, n, m, k);

    for(int i = 0; i < n; i++)
    {
         std :: cout << arr[i] << std :: endl;
    }
}
