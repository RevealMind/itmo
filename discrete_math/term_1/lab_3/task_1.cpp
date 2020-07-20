#include<bits/stdc++.h>
std :: vector<int> arr;
int n;
void func(int i){
    if(arr.size() == n)
    {
        for(int j = 0; j < n; j++)
            printf("%d", arr[j]);
        printf("\n");
        return;
    }
    arr.push_back(0);
    func(i + 1);
    arr.pop_back();
    arr.push_back(1);
    func(i + 1);
    arr.pop_back();
}

int main()
{
    freopen("allvectors.in","r",stdin);
    freopen("allvectors.out","w",stdout);
    std :: cin >> n;
    func(0);
}
