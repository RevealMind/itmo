#include<bits/stdc++.h>
int n;
void next(std :: vector <int> arr)
{
    if(arr.size() == 1)
    {
        std :: cout << "No solution";
        return;
    }
    arr[arr.size() - 1]--;
    arr[arr.size() - 2]++;
    if(arr[arr.size() - 2] > arr[arr.size() - 1])
    {
        arr[arr.size() - 2] += arr[arr.size() - 1];
        arr.pop_back();
    }
    else
    {
        while(arr[arr.size() - 2] * 2 <= arr[arr.size() - 1])
        {
            arr.push_back(arr[arr.size() - 1] - arr[arr.size() - 2]);
            arr[arr.size() - 2] = arr[arr.size() - 3];
        }
    }
    std :: cout << n << "=" << arr[0];
    for(int i = 1; i < arr.size(); i++)
    {
        printf("+%d", arr[i]);
    }
}
int main()
{
    freopen("nextpartition.in","r",stdin);
    freopen("nextpartition.out","w",stdout);
    std :: string str;
    std :: vector <int>  arr;
    int x;
    std :: cin >> str;
    //std :: cout << str.find("=");
    n = atoi(str.substr(0,str.find("=")).c_str());
    str.erase(str.begin(), str.begin() + str.find("=") + 1);
    //std :: cout << str;
    std :: stringstream cmd(str);
    while (std::getline(cmd, str, '+'))
    {
        x = atoi(str.c_str());
        arr.push_back(x);
    }
    next(arr);
}
