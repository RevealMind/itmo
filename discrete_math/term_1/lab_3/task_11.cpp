#include<bits/stdc++.h>
int n;

void nextSubset(int b,std :: vector<int> &arr)
{
    if(arr.size() <= n && !arr.empty()){
    for(int i = 0; i < arr.size(); i++)
        printf("%d ", arr[i]);
    printf("\n");
    if(arr.size() == n)
        return;
    }
    for(int i = b; i <= n; i++)
    {
        arr.push_back(i);
        nextSubset(i + 1,arr);
        arr.pop_back();
    }
}
int main()
{
    freopen("subsets.in","r",stdin);
    freopen("subsets.out","w",stdout);
    std :: vector<int> arr;
    std :: cin >> n;
    std :: cout << " \n";
    nextSubset(1,arr);
}
