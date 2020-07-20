#include<bits/stdc++.h>

#define l first
#define r second

std :: vector <std ::pair <int , int> > arr;

void left(int I, int J)
{
    if(arr[J].l != 0)
    {
        arr[arr[J].l].r = I;
    }
    arr[I].l = arr[J].l;
    arr[I].r = J;
    arr[J].l = I;
    return;

}

void right( int I, int J)
{
    if(arr[J].r != 0)
    {
        arr[arr[J].r].l = I;
    }
    arr[I].r = arr[J].r;
    arr[I].l = J;
    arr[J].r = I;
    return;

}

void leave( int I)
{
    if(arr[I].l != 0)
        arr[arr[I].l].r = arr[I].r;
    if(arr[I].r != 0)
        arr[arr[I].r].l = arr[I].l;
    return;
}

int main()
{
    freopen("formation.in","r", stdin);
    freopen("formation.out","w", stdout);
    int n, m;
    std :: string cmd;
    scanf("%d %d", &n, &m);
    arr.resize(n+1);
    for(int i = 0; i < m; i++)
    {
        int x, y;
        std :: cin >> cmd;
        if(cmd == "left")
        {
            scanf("%d %d", &x, &y);
            left(x, y);
            continue;

        }
        else if(cmd == "right")
        {
            scanf("%d %d", &x, &y);
            right(x, y);
            continue;
        }
        else if(cmd == "name")
        {
            scanf("%d", &x);
            printf("%d %d\n", arr[x].l, arr[x].r);
            continue;
        }
        else if(cmd == "leave");
        {
            scanf("%d", &x);
            leave(x);
            continue;
        }
    }

}
