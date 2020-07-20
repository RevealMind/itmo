#include<bits/stdc++.h>

int main()
{
    freopen("mtf.in","r", stdin);
    freopen("mtf.out","w", stdout);
    std :: string list = "abcdefghijklmnopqrstuvwxyz", cmd;
    int x;
    std :: cin >> cmd;
    for(int i = 0; i < cmd.size(); i++)
    {
        x = list.find(cmd[i]);
        std :: cout << x+1 << " ";
        list.erase(list.begin()+x);
        list.insert(list.begin(), cmd[i]);
    }
}
