#include<bits/stdc++.h>
int n, r = 1;
std :: vector<int> nextPermutations(std :: vector<int> arr)
{
    int min;
    for(int i = n - 2; i >= 0; i--)
    {
        if(arr[i] < arr[i + 1])
        {
            min = i + 1;
            for(int j = i + 1; j < n; j++)
            {
                if(arr[j] < arr[min] && arr[j] > arr[i])
                    min = j;
            }
            std :: swap(arr[i],arr[min]);
            int k = i + 1;
            int t = n - 1;
            while (k < t)
                std :: swap(arr[k++], arr[t--]);
            return arr;
        }
    }
    //return arr;
}
int main()
{
    freopen("permutations.in","r",stdin);
    freopen("permutations.out","w",stdout);
    std :: cin >> n;
    for(int i = 2 ; i <= n; i++)
        r*=i;
    std :: vector <std :: vector<int> > arr(r);
    for(int i = 0; i < n; i++)
        arr[0].push_back(i + 1);
    for(int i = 1; i < r; i++)
        arr[i] = nextPermutations(arr[i - 1]);
    for(int j = 0; j < arr.size(); j++)
    {
        for(int i = 0; i < n; i++)
            printf("%d ",arr[j][i]);
        std :: cout << "\n";
    }
}
