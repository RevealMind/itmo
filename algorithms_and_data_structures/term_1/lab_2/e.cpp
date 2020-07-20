#include<bits/stdc++.h>
struct Node{
    int parent;
    int min;
    int max;
    int count;
};
Node arr[1000005];
void init(int n)
{
    for(int i = 0; i < n; i++){
            arr[i].parent = i;
            arr[i].max = i;
            arr[i].min = i;
            arr[i].count = 1;
        }
    return;
}

int find(int x)
{
    if(arr[x].parent == x) return x;
    return find(arr[x].parent);
}
void get(int x)
{
    x = find(x);
    printf("%d %d %d\n", arr[x].min, arr[x].max, arr[x].count);
    return;
}

void unite(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return;
    if(arr[x].count >= arr[y].count)
        std :: swap(x, y);
    arr[x].parent = y;
    arr[y].count += arr[x].count;
    arr[y].max = std :: max(arr[y].max, arr[x].max);
    arr[y].min = std :: min(arr[y].min, arr[x].min);
    return;
}
int main()
{
    freopen("dsu.in","r", stdin);
    freopen("dsu.out","w", stdout);
    int n, x , y;
    std :: string cmd;
    scanf("%d", &n);
    init(n + 1);
    while(std :: cin >> cmd)
    {
        switch(cmd[0])
        {
        case 'g':
            scanf("%d", &x);
            get(x);
            break;
        case 'u':
            scanf("%d %d", &x, &y);
            unite(x, y);
            break;
        }
    }
}
