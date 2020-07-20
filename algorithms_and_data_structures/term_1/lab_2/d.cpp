#include<bits/stdc++.h>

int main()
{
    freopen("stack-min.in","r", stdin);
    freopen("stack-min.out","w", stdout);
    std :: stack<std :: pair<int,int> > arr;
    int cmd, x, n;
    std :: pair<int, int> num;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &cmd);
        switch(cmd){
        case 1:
            scanf("%d", &num.first);
            if(!arr.empty())
                num.second = std :: min(arr.top().second, num.first);
            else
                num.second = num.first;
            arr.push(num);
            break;
        case 2:
            arr.pop();
            break;
        case 3:
            printf("%d\n", arr.top().second);
            break;
        }
    }
}
