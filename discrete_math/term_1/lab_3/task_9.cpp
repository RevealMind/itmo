#include<bits/stdc++.h>
int n;

void nextBrackets(int op, int cl, std :: string arr)
{
    //std :: cout << arr << "\n";
    if(op + cl == 2 * n)
    {
        std :: cout << arr << "\n";
        return;
    }

    if(op < n)
        nextBrackets(op + 1 , cl, arr + "(");
    if(op > cl)
        nextBrackets(op, cl + 1, arr + ")");
}
int main()
{
    freopen("brackets.in","r",stdin);
    freopen("brackets.out","w",stdout);
    std :: cin >> n;
    std :: string arr = "";
    nextBrackets(0, 0, arr);
}
