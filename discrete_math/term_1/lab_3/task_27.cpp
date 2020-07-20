#include<bits/stdc++.h>
void next(std :: string arr)
{
    int cl = 0, op = 0;
    for(int i = arr.size() - 1; i >= 0; i--)
    {
        if(arr[i] == '(')
        {
            op++;
            if(cl > op)
                break;
        }
        else cl++;
    }
    std :: string next = arr.substr(0,arr.size() - op - cl);
    if(next == "")
        std :: cout << "-";
    else
    {
        next.append(")");
        for(int i = 1; i <= op; i++)
            next.append("(");
        for(int i = 1; i < cl; i++)
            next.append(")");
        std :: cout << next;
    }
}
int main()
{
    freopen("nextbrackets.in","r",stdin);
    freopen("nextbrackets.out","w",stdout);
    std :: string arr;
    std :: cin >> arr;
    next(arr);
}
