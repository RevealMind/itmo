#include<bits/stdc++.h>
int main()
{
    freopen("hospital.in","r", stdin);
    freopen("hospital.out","w", stdout);
    int n,a;
    char c;
    std :: cin >> n;
    std :: deque<int> que;
    for(int i = 0; i < n; i++)
    {
        std :: cin >> c;
        if (c == '+')
        {
            std :: cin >> a;
            que.push_back(a);
        }
        else if (c == '-')
           {
             std :: cout << que.front()<<std :: endl;
             que.pop_front();
           }
        else if(c=='*')
        {
            std :: cin >> a;
            int pos = (que.size()+1)/2;
            que.insert(que.begin()+pos,a);
        }
    }
}
