#include<bits/stdc++.h>

int main()
{
    freopen("decode.in","r", stdin);
    freopen("decode.out","w", stdout);
    std :: vector <char> arr;
    std :: string cmd;
    std :: cin >> cmd;
    arr.push_back(cmd[0]);
    for(int i = 1; i < cmd.size(); i++){
        if(cmd[i] == arr.back()){
            arr.pop_back();
            continue;
        }
        else arr.push_back(cmd[i]);
    }
    for(int i = 0; i < arr.size(); i++)
        std :: cout << arr[i];
}
