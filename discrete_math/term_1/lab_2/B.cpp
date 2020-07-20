#include<bits/stdc++.h>
std :: string word;

void sort(std :: string *arr,int n,int m, int k)
{
    int c[26];

    for(int i = 0; i < k; i++)
    {
        for(int j = 0; j < 26; j++)
            c[j] = 0;

        for(int j =0; j < n; j++)
        {
            int d = (int)(arr[j][m-i-1] - 'a');

            c[d]++;
        }

        int count = 0;

        for(int j = 0;  j < 26; j++)
        {
            int tmp = c[j];
            c[j] = count;
            count += tmp;
        }

        std :: string b[n];
        for(int j = 0; j < n; j++)
        {
            int d = (int)(arr[j][m-i-1] - 'a');
            b[c[d]] = arr[j];
            c[d]++;
        }
        for(int i = 0; i < n; i++)
            arr[i] = b[i];
    }


}
int main()
{
    freopen("bwt.in","r", stdin);
    freopen("bwt.out","w", stdout);
    std :: string cmd;
    std :: cin >> cmd;
    std :: string word[cmd.size()];
    word[0] = cmd;
    for(int i = 1; i < cmd.size(); i++)
    {
        word[i] = word[i-1];
        word[i].push_back(word[i][0]);
        word[i].erase(word[i].begin());
    }
    sort(word, cmd.size(), cmd.size(), cmd.size());
    for(int i = 0; i < cmd.size(); i++)
        std :: cout << word[i][cmd.size()-1];
}
