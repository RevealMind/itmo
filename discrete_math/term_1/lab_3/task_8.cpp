#include<bits/stdc++.h>


int n, k;

void nextPermutations(int cur, int size, std :: vector<int> &choose)
{
    if(size == k)
    {
        for(int j = 0; j < k; j++)
            printf("%d ", choose[j]);
        std :: cout << "\n";
        //choose.pop_back();
        return;
    }
    for (int i = cur + 1; i < n+1 ; i++){
        choose.push_back(i);
        nextPermutations(i, size + 1, choose);
        choose.pop_back();
    }
    //choose.clear();

}
int main()
{
    freopen("choose.in","r",stdin);
    freopen("choose.out","w",stdout);
    std :: cin >> n >> k;
    std :: vector<int> arr;
    nextPermutations(0, 0, arr);
}
