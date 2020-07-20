#include<bits/stdc++.h>

int main()
{
    freopen("huffman.in","r", stdin);
    freopen("huffman.out","w", stdout);
    int n;
    scanf("%d", &n);
    long long ans = 0;
    long long *a = new long long[n];
    long long *b = new long long[n];

    for(int i = 0; i < n; i++)
        {scanf("%I64d", &a[i]);
         b[i] = 1000000000000;
        }

    std :: sort(a, a + n);
    long long  sumII, sumIJ, sumJJ;
    int i = 0, j = 0;
    for(int k = 0; k < n-1; k ++)
    {

        if(i + 1 < n){
            sumII = a[i] + a[i + 1];
            sumIJ = a[i] + b[j];
            sumJJ = b[j] + b[j + 1];
            if(sumII <= sumIJ && sumII <= sumJJ)
            {
                b[k] = sumII;
                ans += sumII;
                i += 2;
                continue;
            }
            if(sumIJ <= sumII && sumIJ <= sumJJ)
            {
                b[k] = sumIJ;
                ans += sumIJ;
                i++;
                j++;
                continue;
            }
            if(sumJJ <= sumII && sumJJ <= sumIJ)
            {
                b[k] = sumJJ;
                ans += sumJJ;
                j += 2;
                continue;
            }
        }
        else if(i < n){
            sumIJ = a[i] + b[j];
            sumJJ = b[j] + b[j + 1];
            if(sumIJ <= sumJJ)
            {
                b[k] = sumIJ;
                ans += sumIJ;
                i++;
                j++;
                continue;
            }
            if(sumJJ <= sumIJ)
            {
                b[k] = sumJJ;
                ans += sumJJ;
                j += 2;
                continue;
            }
        }
        else
        {
            sumJJ = b[j] + b[j + 1];
            b[k] = sumJJ;
            ans += sumJJ;
            j += 2;
            continue;
        }


    }
    //std :: cout << "i = " << i << "\n";
    std :: cout << ans;
}
