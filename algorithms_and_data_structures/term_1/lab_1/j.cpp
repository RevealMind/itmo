#include<bits/stdc++.h>
// h2 = 2 * h1 - h0 + 2
double binSearch(double a, double n)
{
    double l = 0;
    double r = a;
    double min;
    while(true)
    {
        double m = (l + r) / 2;
        double h0, h1;
        h0 = a;
        h1 = m;
        bool k = true;
        if(m <= 0)
            k = false;
        for(int j = 2; j < n ; j++)
        {
            double h2 = 2 * h1 - h0 + 2 ;
            if(h2 < 0)
                {
                    k = false;
                    break;
                }
            h0 = h1;
            h1 = h2;
        }
        if(m == l || m == r)
            break;

        if(k){
            r = m;
            min = h1;
        }
        else
            l = m;
    }
    return min;
}


int main()
{
    double a, n;
    std :: cin >> n >> a;
    printf("%.2f", binSearch( a, n));
}
