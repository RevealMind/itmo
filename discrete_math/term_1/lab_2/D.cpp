#include<bits/stdc++.h>

int main()
{
    freopen("lzw.in", "r" , stdin);
    freopen("lzw.out", "w", stdout);
    std :: string t;
    char c;
    std :: map <std :: string, int> d;
    for(int i = 1; i < 27 ; i++)
    {
        t = 'a' + i - 1;
        d[t] = i;
    }
    int k = 27;
    std :: string cmd;
    std :: cin >> cmd;
    t = cmd[0];
    for(int j = 1; j < cmd.size(); j++)
    {
         //std :: cout << t.size() << "\n";
         c = cmd[j];

         if(j  == cmd.size())
            std :: cout << d[t] - 1;
         else
         {
            // std :: cout << t + c<< "\n";
             if(d[t + c] != 0)
             {
                t.push_back(c);
                //std :: cout  << "t = " << t << "\n";
             }
             else
             {
                 std :: cout << d[t] - 1 << " ";
                 d[t + c] = k;
                 k++;
                 t = c;
             }

         }
    }
    std :: cout << d[t] - 1;
}
