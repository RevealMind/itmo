#include<bits/stdc++.h>

int main()
{
    freopen("saloon.in","r", stdin);
    freopen("saloon.out","w", stdout);
    int n, h, m ,k, time, x;
    scanf("%d", &n);
    std :: deque <int> arr;
    int person = 0, j = 0;
    for(int i = 0; i < n; i++)
    {
        scanf("%d %d %d", &h, &m, &k);
        time = h * 60 + m;
        while(person != 0 && arr[j] <= time)
        {
            person--;
            j++;
        }

        if(person == 0)
        {
            arr.push_back(time + 20);
            person++;
            printf("%d %d\n", (time + 20)/60, (time + 20)%60);
            continue;
        }

        if(person <= k)
        {
            x = arr[j] + person * 20;
            arr.push_back(x);
            person++;
            printf("%d %d\n", x/60, x%60);
            continue;
        }
        else
        {
            printf("%d %d\n", time/60, time%60);
            continue;
        }
    }
}
