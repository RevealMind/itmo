#include<bits/stdc++.h>
std :: vector<int> arr;
int n;

std :: string tobinary(int i, int size)
{
    std :: string s = "";
    while(i > 0)
    {
        char ss = (i % 2) + '0';
        s = ss + s;
        i /= 2;
    }
    while(s.size() < size)
        s ='0' + s;
        //std :: cout << s << "\n";
    return s;
}

int main()
{
    freopen("gray.in","r",stdin);
    freopen("gray.out","w",stdout);
    std :: cin >> n;
    for(int i = 0; i < (1<<n); i++)
        arr.push_back(i^(i/2));
    for(int i = 0; i < (1<<n); i++)
        std :: cout << tobinary(arr[i], n) << "\n";

}
