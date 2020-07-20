#include<bits/stdc++.h>

bool T0 = true,
     T1 = true,
     SD = true,
     M  = true,
     L  = true;

std :: string tobinary(int i, int size)
{
    std :: string s = "";
    while(i > 0)
    {
        char ss = (i % 2) + '0';
        s = ss + s;
        i /= 2;
    }
    while(s.size() < size-1)
        s ='0' + s;
    return s;
}
bool if_dom(int i, int j, int size)
{
    std :: string maz = tobinary(i, size), dominator = tobinary(j, size);
    for(int j = size-1; j >= 0; j--)
    {
        if(dominator[j] < maz[j])
            return false;
    }
    return true;
}
void test(std :: string s, int size)
{

    if(s[0] == '1') // T0
        T0 = false;
    if(s[size-1] == '0') // T1
        T1 = false;
//----------------------------------------
    for(int i = 0; i < size/2 ; i++) // SD
        if(s[i] == s[size-i-1])
            SD = false;
    if(size == 1)
        SD = false;
//-----------------------------------------
    std :: vector <std :: vector <int> > arr(size); //L

    for(int i = 0; i < size; i++)
        arr[0].push_back(s[i] - '0');

    for(int i = 1; i < size; i++)
    {
        for(int j = 0; j < arr[i-1].size()-1; j++)
        {
            arr[i].push_back((arr[i-1][j] + arr[i-1][j+1])% 2);
        }
        if(i != 1 && i != 2 && i != 4 && i != 8 && i != 16)
            if(arr[i][0] == 1)
                L = false;
    }
//-----------------------------------------
     int shift = 1;
     if(M)
     for(int i = 0; i < size/2; i++) // M
     {
         if(s[i] == '1')
         {
            int j = i + 1;
            while(j < size)
            {
                if(s[j] == '0')
                    if(if_dom(i,j,size))
                        M  = false;
                j++;
            }
         }
     }
}

int main()
{
    int _n, n;
    std :: string str;
    std :: cin >> n;
    for(int i = 0; i < n; i++)
    {
        std :: cin >> _n >> str;
        test(str,pow(2,_n));
    }

    if(!T0 && !T1 && !SD && !M && !L)
        std :: cout <<"YES";
    else
        std :: cout << "NO";
    //std :: cout << T0 << T1 << SD << M << L;
}
