#include<bits/stdc++.h>
std :: vector<int> arr;
std :: vector<std :: vector<int> > mas;
int n, k = 0;
void func(int i){
    if(arr.size() == n)
    {
        mas.push_back(arr);
        k++;
        return;
    }
    arr.push_back(0);
    func(i + 1);
    arr.pop_back();
    if(arr.empty() || !arr.back()){
    arr.push_back(1);
    func(i + 1);
    arr.pop_back();}
}

int main()
{
    freopen("vectors.in","r",stdin);
    freopen("vectors.out","w",stdout);
    std :: cin >> n;
    func(0);
    std :: cout << k << "\n";
    for(int i = 0; i < mas.size(); i++){
        for(int j = 0; j < mas[i].size(); j++)
            printf("%d", mas[i][j]);
    printf("\n");
    }

}
