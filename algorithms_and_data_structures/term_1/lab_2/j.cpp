#include<bits/stdc++.h>

int main()
{
    freopen("bureaucracy.in","r", stdin);
    freopen("bureaucracy.out","w", stdout);
    int x, n, m, det;
    scanf("%d %d", &n, &m);
    det = m / n;
    std :: deque <int> arr;
    for(int i = 0; i < n; i ++)
    {
        scanf("%d", &x);
        arr.push_back(x);
        //sum += x;
    }

    if(det)
    {
        for(int i = 0; i < n; i++)
        {
            if (arr.front() > det)
            {
                m -= det;
                arr.push_back(arr.front() - det);
                arr.pop_front();
                continue;
            }
            else
            {
                m -= arr.front();
                arr.pop_front();
                continue;
            }
        }
    }

    for(int i = 0; i < m && !arr.empty(); i++)
    {
        arr.front()--;
        if(arr.front() == 0){
            arr.pop_front();
            continue;
        }
        else
        {
            arr.push_back(arr.front());
            arr.pop_front();
            continue;
        }
    }
    if(!arr.empty()){
    std :: cout << arr.size() << "\n";
    for(int i = 0; i < arr.size() ; i++)
            printf("%d ", arr[i]);
    }
    else printf("-1");


}
