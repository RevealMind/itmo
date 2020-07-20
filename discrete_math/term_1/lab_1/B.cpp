#include<bits/stdc++.h>

int main()
{
    int count, x, n , k, bit;
    bool flag = false;
    scanf("%d %d", &n, &k);
    std :: pair <int, int> one;
    std :: vector <std :: vector <int> > arr(k);
    for(int i = 0; i < k ; i++)
    {
        for(int j = 0; j < n; j++)
        {
            scanf("%d", &x);
            arr[i].push_back(x);
        }
    }

    if(n == 1)
        {
            for(int i = 0; i < k; i++)
                arr[i].push_back(-1);
            n++;
        }

    int len = arr.size();
    while(len != 0)
    {
        flag = false;
        for(int i = 0; i < k; i++)
        {
            count = 0;
            for(int j = 0; j < n; j++)
            {
                if(arr[i][j] == -1)
                    count++;
                else
                    one.second = j;
            }
            if(count + 1 == n)
            {
                one.first = i;
                flag = true;
                break;
            }
        }
        if(!flag)
            {
                std :: cout << "NO";
                return 0;
            }
        else
        {
            bit = arr[one.first][one.second];
            for(int i = 0; i < arr.size(); i++)
            {
                if(arr[i][one.second] == -1 || arr[i][one.second] == -2)
                        continue;
                if(arr[i][one.second] == (1^bit))  // 1 and 0 - > -1
                {
                    arr[i][one.second] = -1;
                    flag = false;
                    for(int j = 0; j < n; j++)
                    {
                        //std :: cout << "In arr["<< i << "]["<<j<<"] = " << arr[i][j]<< "\n";

                        if(arr[i][j] != -1)
                        {
                            flag = true;
                            break;
                        }
                    }
                    if(!flag)
                    {
                        std :: cout << "YES";
                        return 0;
                    }
                }
                else
                {
                    for(int j = 0; j < n; j++)
                        arr[i][j] = -2;
                    len--;
                }
            }
        }

    }
    std :: cout << "NO";
    return 0;



}
