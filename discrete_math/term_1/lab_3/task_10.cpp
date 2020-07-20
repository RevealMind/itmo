#include<bits/stdc++.h>
int n;
void nextPartition(int e, int b, std :: vector<int> &arr)
{
    if(e == 0)
    {
        printf("%d",arr[0]);
        for(int i = 1; i < arr.size(); i++)
            printf("+%d",arr[i]);
        std :: cout << "\n";
        return;
    }

    for(int i = b; i <= e; i++)
    {
        arr.push_back(i);
        nextPartition(e - i, i, arr);
        arr.pop_back();
    }
}
int main()
{
    freopen("partition.in","r",stdin);
    freopen("partition.out","w",stdout);
    std :: cin >> n;
    std :: vector <int> arr;
    nextPartition(n,1,arr);*/
    for (int i = 0; i < 10; i++) {
        std::cout << std::abs(rand()) % 10;
    }

}
