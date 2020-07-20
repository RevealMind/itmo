#include<bits/stdc++.h>

int main()
{
    freopen("telemetry.in","r",stdin);
    freopen("telemetry.out","w",stdout);
    long long n, k , counter, cur, flag = 0;

    std :: cin >> n >> k;
    std :: vector<std :: vector<int> > arr(120000, std::vector<int> (n, -1));

    for(int i = 0; i < k; i++)
        arr[i + 1][0] = i;

    counter = k;
    for(int i = 1; i < n; i++)
    {
        cur = counter;
        flag = 0;
        int num = 0;
        counter = counter * k;

        for(int j = (counter / k + 1); j <= counter; j++)
        {
            arr[j] = arr[cur];
            cur--;
            if(cur == flag)
            {
                flag += counter/k;
                cur = counter/k + flag;
            }

            //std :: cout << cur << "\n";

        }
        flag = counter / k;
        for(int j = 1; j <= counter; j++)
        {
            arr[j][i] = num;
            if(j == flag)
            {
                flag += counter / k;
                num++;
            }
        }
    }
    for(int i = 1; i <= pow(k,n)+ 1; i++)
    {
        for(int j = 0; arr[i][j] != -1 && j < n; j++)
            std :: cout << arr[i][j];
        std :: cout << "\n";
    }
}
