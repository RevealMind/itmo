#include<bits/stdc++.h>

bool is_open(char c)
{
    return c == '[' || c == '(' || c == '{';
}

bool is_pair(char op, char cl)
{
    return cl-op >= 1 && cl - op <= 2; // ')' - '(' = 1; other = 2
}

int main()
{
    freopen("brackets.in","r", stdin);
    freopen("brackets.out","w", stdout);
    std :: stack <char> arr;
    std :: string cmd;
    std :: cin >> cmd;
    for(int i = 0; i < cmd.size(); i++){
        if(is_open(cmd[i]))
            arr.push(cmd[i]);
        else if(!arr.empty() && is_pair(arr.top(), cmd[i]))
            arr.pop();
        else{
            std :: cout << "NO";
            return 0;
        }
    }
    if(arr.empty())
        std :: cout << "YES";
    else
        std :: cout << "NO";
}
