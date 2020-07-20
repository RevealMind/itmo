#include<bits/stdc++.h>
std :: vector<int> arr;
int n;

std :: string toternary(int i, int size)
{
    std :: string s = "";
    while(i > 0)
    {
        char ss = (i % 3) + '0';
        s = ss + s;
        i /= 3;
    }
    while(s.size() < size)
        s ='0' + s;
        //std :: cout << s << "\n";
    return s;
}
func(std :: string str)
{
    for(int i = 0; i < 2; i++)
    {

        for(int j = 0; j < str.size(); j++)
        {
            str[j] = (((str[j] - '0') + 1) % 3) + '0';
        }
        std :: cout << str << "\n";
    }
}
int main()
{
    freopen("antigray.in","r",stdin);
    freopen("antigray.out","w",stdout);
    std :: cin >> n;
    for(int i = 0; i < pow(3, n-1); i++){
         func(toternary(i, n));
         std :: cout << toternary(i, n) << "\n";
    }

}
