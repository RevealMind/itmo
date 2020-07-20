#include<bits/stdc++.h>

int L;
bool if_less(std :: vector <std :: pair <double, double> > &arr, double time)
{
    int i = 0, j = 0;
    double dist = 0;
    while(time > arr[i].first)
    {
        time -= arr[i].first;
        dist += arr[i].first * arr[i].second;
        i++;
    }

    dist += time * arr[i].second;
    if(dist < L)
        return false;

    double t1, t2, pass1 = time, pass2 = 0;; // t1 -- времени до след отрезка пути I; t2 -- ... J;

    while(i < arr.size())
    {
        t1 = arr[i].first - pass1;
        t2 = arr[j].first - pass2;

        if(t1 < t2)
        {
            dist += t1 * arr[i].second - t1 * arr[j].second;

            if(dist < L)
                return false;

            i++;
            pass1 = 0;
            pass2 += t1;
        }
        else
        {
            dist += t2 * arr[i].second - t2 * arr[j].second;

            if(dist < L)
                return false;

            j++;
            pass1 += t2;
            pass2 = 0;
        }
    }
    return true;
}

double bin(std :: vector <std :: pair <double, double> > &arr, double l, double r)
{
    double key;
    while(r - l > 0.00001)
    {
        key = (r + l) / 2;

        if(if_less(arr, key))
             r = key;
        else
             l = key;
    }
    return r;
}



int main()
{
    freopen("trains.in" ,"r",stdin);
    freopen("trains.out", "w", stdout);
    int n, V, T;
    double r = 0, l = 0;
    std :: cin >> L >> n;

    std :: vector <std :: pair <double, double> > arr(n);

    for(int i = 0; i < n; i++)
    {
        scanf("%lf %lf", &arr[i].first, &arr[i].second);
        r += arr[i].first;
    }

    printf("%.3lf",bin(arr, l, r));

}
