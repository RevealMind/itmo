#include<bits/stdc++.h>

std :: vector <int> a(70000);

void antiQ(int n)
{
    for(int i = 0; i < n; i++)
        a[i] = i+1;

    for(int i = 0; i < n; i++)
        std :: swap(a[i],a[i/2]);

}
int main()
{
    freopen("antiqs.out","w",stdout);
    freopen("antiqs.in", "r", stdin);

    int n;

    std :: cin >> n;

    antiQ(n);

    for(int i = 0;  i < n; i++)
        std :: cout << a[i] << " ";
}
