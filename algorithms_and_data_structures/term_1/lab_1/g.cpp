#include<bits/stdc++.h>

int n1, n2, n3, n4,
    minA, minB, minC, minD;
int a[100001],b[100001],c[100001],d[100001];

void solve()
{
    int min, max;

    min = std :: min(std :: min(a[0],b[0]),std :: min(c[0],d[0]));

    max = std :: max(std :: max(a[0],b[0]),std :: max(c[0],d[0]));

    int minRaz = abs(max-min);

    int i = 0, j = 0 , k = 0, l = 0, x;
    minA = i;
    minB = j;
    minC = k;
    minD = l;
    while(i < n1 && j < n2 && k < n3 && l < n4)
    {
        int min, max;

        min = std :: min(std :: min(a[i],b[j]),std :: min(c[k],d[l]));

        max = std :: max(std :: max(a[i],b[j]),std :: max(c[k],d[l]));

        x = abs(max - min);
        if(x < minRaz)
        {
            minRaz = abs(x);
            minA = i;
            minB = j;
            minC = k;
            minD = l;
        }

        if(x == 0)
            break;

        while(min == a[i] || min == b[j] || min == c[k] || min == d[l]){
        if(min == a[i])
            i++;
        if (min == b[j])
            j++;
        if (min == c[k])
            k++;
        if (min == d[l])
            l++;
        }
    }
   std :: cout << a[minA] << " " << b[minB] << " " << c[minC] << " " << d[minD];
}

int main()
{
    freopen("style.out","w",stdout);
    freopen("style.in", "r", stdin);
    scanf("%d", &n1);
    for(int i = 0; i < n1; i++)
        scanf("%d", &a[i]);

    scanf("%d", &n2);
    for(int i = 0; i < n2; i++)
        scanf("%d", &b[i]);

    scanf("%d", &n3);
    for(int i = 0; i < n3; i++)
        scanf("%d", &c[i]);


    scanf("%d", &n4);
    for(int i = 0; i < n4; i++)
        scanf("%d", &d[i]);

    std :: sort(a, a + n1);
	std :: sort(b, b + n2);
	std :: sort(c, c + n3);
	std :: sort(d, d + n4);
    solve();

}
