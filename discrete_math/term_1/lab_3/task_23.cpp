#include<bits/stdc++.h>
void prev(char arr[], int n)
{
  for(int j = n; j >= 0; j--)
  {
      if(arr[j] == '1')
      {
          arr[j] = '0';
          break;
      }
      else
        arr[j] = '1';
  }
  std :: cout << arr << "\n";
}
void next(char arr[],int n)
{
    for(int j = n; j >= 0; j--)
  {
      if(arr[j] == '0')
      {
          arr[j] = '1';
          break;
      }
      else
        arr[j] = '0';
  }
  std :: cout << arr;
}
int main()
{
  freopen("nextvector.in","r",stdin);
  freopen("nextvector.out","w",stdout);
  char arr[200100], arr1[200100];
  std :: cin >> arr;
  int n = 0, i = 0, count0 = 0, count1 = 0;
  while(arr[i] != NULL)
  {
      if(arr[i] == '1')
        count1++;
      else
        count0++;
      arr1[i] = arr[i];
      n++;
      i++;
  }
  if(count0 != n)
    prev(arr, n - 1);
  else
    std :: cout << "-\n";
  if(count1 != n)
    next(arr1, n - 1);
  else
    std :: cout << "-";
}
