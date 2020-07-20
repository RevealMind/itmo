#include<bits/stdc++.h>
std :: vector <std :: string> arr; // массив нащей таблицы истинностти
std :: vector <std :: pair < int , int > > in;

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

void init(int n)
{
    for(int i = 0; i < pow(2,n); i++)
        arr.push_back(tobinary(i,n));
}

int main()
{
    std :: pair <int , int> x;
    int n, m, a , b;

    scanf("%d %d", &n,&m);

    init(n);
    bool pr = false;
    bool if_repeat;

    for(int i = 0; i < m ; i++)
    {
        if_repeat = false;
        scanf("%d %d", &x.first, &x.second);
        for( int k = 0; k < in.size(); k++)
        {
            if(in[k].first == x.first && in[k].second == x.second || in[k].first == x.second && in[k].second == x.first )
            {
                if_repeat = true;
                break;
            }
        }
        if(!if_repeat)
            in.push_back(x);
    }
    int count = 0;
    for(int i = 0; i < pow(2, n); i++)
    {
        for(int j = 0;  j < in.size(); j++)
        {
            a = (in[j].first > 0)? (arr[i][in[j].first - 1] - '0') : ((arr[i][abs(in[j].first) - 1] - '0')^1);
            b = (in[j].second > 0)? (arr[i][in[j].second - 1] - '0') : ((arr[i][abs(in[j].second) - 1] - '0')^1);
            if(a == 0 && b == 0)
            {
                pr = true;
                break;
            }
        }

        if(!pr)
        {
            std :: cout << "NO";
            return 0;
        }
        pr = false;
    }
    std :: cout << "YES";
    return 0;
}
