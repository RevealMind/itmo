#include<bits/stdc++.h>
bool is_op(char c) {
    return c == '+' || c == '-' || c == '*';
}
int main() {
    freopen("postfix.in","r", stdin);
    freopen("postfix.out","w", stdout);
    char cmd;
    std::vector <int> arr;
    while(std :: cin >> cmd){
        if(is_op(cmd)) {
               switch(cmd) {
               case '+': arr[arr.size() - 2] = arr[arr.size() - 2] + arr[arr.size() - 1];break;
               case '-': arr[arr.size() - 2] = arr[arr.size() - 2] - arr[arr.size() - 1];break;
               case '*': arr[arr.size() - 2] = arr[arr.size() - 2] * arr[arr.size() - 1];break;
               }
               arr.pop_back();
           }
        else arr.push_back(cmd - '0');
    }
    std::cout << arr.back();
}
