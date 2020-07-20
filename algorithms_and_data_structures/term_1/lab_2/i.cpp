#include<bits/stdc++.h>

int main()
{
    freopen("hemoglobin.in","r", stdin);
    freopen("hemoglobin.out","w", stdout);
    std :: vector <int> arr(50001);
    arr[0] = 0;
    int i = 1;
    int n;
    scanf("%d", &n);
    std :: string cmd;
    for(int j = 0; j < n; j++){
        std :: cin >> cmd;
        switch(cmd[0]){
        case '+':
            arr[i] = atoi(cmd.substr(1).c_str()) + arr[i - 1];
            i++;
            break;
        case '-':
            printf("%d\n", (arr[i - 1] - arr[i - 2]));
            i--;
            break;
        case '?':
            printf("%d\n", arr[i - 1]-arr[i - 1 - atoi(cmd.substr(1).c_str())]);
            break;
        }
    }
}
