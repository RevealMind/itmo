#include<bits/stdc++.h>
int n;
std :: vector<int> prevPermutations(std :: vector<int> arr)
{
    int max;
    std :: vector<int> null(n, 0);
    for(int i = n - 2; i >= 0; i--)
    {
        if(arr[i] > arr[i + 1])
        {
            max = i + 1;
            for(int j = i + 1; j < n; j++)
            {
                if(arr[j] > arr[max] && arr[j] < arr[i])
                    max = j;
            }
            std :: swap(arr[i],arr[max]);
            int k = i + 1;
            int t = n - 1;
            while (k < t)
                std :: swap(arr[k++], arr[t--]);
            return arr;
        }
    }
    return null;
}

std :: vector<int> nextPermutations(std :: vector<int> arr)
{
    int min;
    std :: vector<int> null(n, 0);
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
    return null;
}

int main()
{
    freopen("nextperm.in","r",stdin);
    freopen("nextperm.out","w",stdout);
    std :: cin >> n;
    std :: vector <int> arr(n), next, prev;
    for(int i = 0; i < n; i++)
        std :: cin >> arr[i];
    prev = prevPermutations(arr);
    next = nextPermutations(arr);
    for(int i = 0; i < n; i++)
        std :: cout << prev[i] << " ";
    std :: cout << "\n";
    for(int i = 0; i < n; i++)
        std :: cout << next[i] << " ";
}
