#include<bits/stdc++.h>
int n, k;
void nextPart2sets(int count, int numofpart, std :: vector <std :: vector <int> > &arr)
{
         /*  for(int i = 0; i < arr.size(); i++)
        {
            for(int j = 0; j < arr[i].size(); j++)
                printf("%d ", arr[i][j]);
            std :: cout << "\n";
        }*/
    if(count == n && numofpart != k){
        return;
    }
    if(count == n) // here must be out
    {
        for(int i = 0; i < arr.size() && !arr[i].empty(); i++)
        {

            for(int j = 0; j < arr[i].size(); j++)
                printf("%d ", arr[i][j]);
             std :: cout << "\n";

        }
         std :: cout << "\n";
        return;
    }
    for(int i = 0; i <= numofpart; i++)
    {
        /*std :: cout << "i = " << i << "\n";
        system("pause >> void");*/
        arr[i].push_back(count + 1);
        if(i == numofpart)
        nextPart2sets(count + 1, numofpart + 1, arr);
        else nextPart2sets(count + 1, numofpart, arr);
        if(!arr[i].empty())
            arr[i].pop_back();
    }
    //arr.clear();
    //return;
}
int main()
{
    freopen("part2sets.in","r",stdin);
    freopen("part2sets.out","w",stdout);
    std :: cin >> n >> k;
    std :: vector < std :: vector <int> > arr(10);
    nextPart2sets(0,0,arr);
}
