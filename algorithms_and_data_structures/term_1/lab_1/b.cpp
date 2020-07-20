#include<bits/stdc++.h>

std :: string cmd;
int val, counter = 0;
std :: vector < std :: pair<int, int> > arr;

void siffUp(int v)
{
    while (v > 0)
    {
         int parant = (v - 1) / 2;
         if(arr[parant].first > arr[v].first)
            std :: swap(arr[parant], arr[v]);
         else return;
         v = parant;
    }
}


void siffDown(int v)
{
    int child1 = 2 * v + 1,
        child2 = 2 * v + 2;

    if (child1 >= arr.size())
        return;
    else if (child2 >= arr.size())
        child2 = child1;

    if(arr[v] <= arr[child1] &&  arr[v] <= arr[child2])
        return;

    int min = child1;
    if(arr[min] > arr[child2])
        min = child2;
    std :: swap (arr[min],arr[v]);

    siffDown(min);

}

void getMin()
{
    std :: cout << arr[0].first << "\n";

    std :: swap (arr[0], arr[arr.size()-1]);

    arr.pop_back();

    siffDown(0);
}

int main()
{
    freopen("priorityqueue.in","r",stdin);
    freopen("priorityqueue.out","w",stdout);
    while(std :: cin >> cmd)
    {
        counter++;
        if(cmd[0] == 'p')
        {
            std :: cin >> val;

            arr.push_back(std :: pair<int, int>(val,counter));

            siffUp(arr.size()-1);

        }
        else if(cmd[0] == 'd')
        {
            int ind, val, k;
            std :: cin >> ind >> val;
            for(int j = 0; j < arr.size(); j++)
                if(arr[j].second == ind)
                {

                    arr[j].first = val;

                    int v = j;

                    while (v > 0)
                    {
                         int parant = (v - 1) / 2;
                         if(arr[parant].first > arr[v].first)
                            std :: swap(arr[parant], arr[v]);
                         else break;
                         v = parant;
                    }

                    break;
                }

        }
        else if(cmd[0] == 'e')
        {
            if(arr.size() != 0)
            {
                getMin();
            }
            else
                std :: cout << "*\n";
        }
    }
}
