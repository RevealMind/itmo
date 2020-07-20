#include<bits/stdc++.h>
int minI,minJ;
int n , _n;
std :: vector <int> a(100000), b(100000);
void solve()
{
    int min = abs(a[0]-b[0]);
    int i = 0, j =0;
    minI = i;
    minJ = j;
    while(i < n && j <_n)
    {
        int x = a[i]-b[j];
        if(abs(x) < min)
        {
            min = abs(x);
            minI = i;
            minJ = j;
        }
        if(x < 0)
        {
            i++;
        }
        else if (x > 0)
        {
            j++;
        }
        else return;
    }

}

int main()
{
    freopen("style.out","w",stdout);
    freopen("style.in", "r", stdin);

    std :: cin >> n;

    for(int i = 0; i < n; i++)
    {
        std :: cin >> a[i];
    }

    std :: cin >> _n;

    for(int i = 0; i < _n; i++)
    {
        std :: cin >> b[i];
    }

    solve();

    std::cout << a[minI]<< " " << b[minJ];
}
