#include<bits/stdc++.h>

int main()
{
    freopen("kenobi.in","r", stdin);
    freopen("kenobi.out","w", stdout);
    std :: deque <int> arr1, arr2;
    int x, n, k = 0;
    std :: string cmd;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        std :: cin >> cmd;
        switch(cmd[0]){
        case 'a':
            scanf("%d", &x);
            arr2.push_back(x);
            k++;
            if(k % 2 == 0)
                {
                    arr1.push_back(arr2.front());
                    arr2.pop_front();
                }
            break;
        case 't':
            if(!arr2.empty())
            {
                arr2.pop_back();
                k--;
                if(k % 2 == 1)
                {
                    arr2.push_front(arr1.back());
                    arr1.pop_back();
                }
            }
            break;
        case 'm':
            arr1.swap(arr2);
            if(k % 2 == 1)
                {
                    arr2.push_front(arr1.back());
                    arr1.pop_back();
                }
            break;
            }
    }
    printf("%d\n", k);
    for(int i = 0; i < arr1.size(); i++)
        printf("%d ", arr1[i]);
    for(int i = 0; i < arr2.size(); i++)
        printf("%d ", arr2[i]);
}
