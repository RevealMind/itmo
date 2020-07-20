#include<bits/stdc++.h>
/*int deep_max = 0;
void findDeep(std :: vector <std :: vector<int> > in, std :: vector <std :: vector<int> > out,int v , int deep){
    if(in[v].empty()){
        if(deep > deep_max)
            deep_max = deep;
    }
    else
        for(int i = 0; i < in[v].size(); i++){
            findDeep(in, out, in[v][i], deep + 1);
        }

}*/
std :: vector <int>  leaves, ans, deep;
std :: vector <std :: vector<int> > in, out;
void func(int i){
    if(leaves.size() == i)
    {
        for(int j = 0; j < in.size(); j++){
            if(!in[j].empty()){
                    int mark = 0;
                for(int k = 0; k < in[j].size(); k++){
                    mark += ans[in[j][k]] * (1 << in[j].size()-k-1);
                }
            ans[j] = out[j][mark];
            }
        }
        printf("%d", ans.back());
        return;
    }
    ans[leaves[i]] = 0;
    func(i + 1);
    ans[leaves[i]] = 1;
    func(i + 1);
}


int main()
{
    //freopen("input.txt","r",stdin);
    int n,num;
    scanf("%d", &n);
    ans.resize(n,0);
    deep.resize(n);
    in.resize(n);
    out.resize(n);
    for(int i = 0; i < n; i++){
        scanf("%d", &num);
        if(num == 0){
            deep[i] = 0;
            leaves.push_back(i);
        }
        else{
            deep[i] = 0;
            in[i].resize(num);
            out[i].resize((1 << num));
            for(int j = 0; j < num; j++){
                scanf("%d", &in[i][j]);
                in[i][j]--;
                if(deep[in[i][j]] > deep[i])
                    deep[i] = deep[in[i][j]];
            }
            for(int j = 0; j < (1 << num); j++){
                scanf("%d", &out[i][j]);
            }
            deep[i]++;
        }
    }
    /*findDeep(in, out, n-1, 0);*/
    std :: cout << deep.back() << "\n";
    func(0);
    return 0;
}
