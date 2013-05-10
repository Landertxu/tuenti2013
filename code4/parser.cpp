#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;



//with this code I discovered that all
//lost numbers were either at the beginning or at the end
/*int main()
{
  ifstream fin;
  fin.open("integers", std::ios_base::binary);
  unsigned char a,b,c,d;
  int ii = 0;
  vector<int> sum(200,0);
  while (fin.get()!=EOF){
    fin.get();
    fin.get();
    d = fin.get();
    sum[d]++;
  }
  for (int i = 0; i < 128; i++)
    cout << i << ": " << sum[i] << endl;
}*/


//with this code I discovered that all lost numbers
//begin with 127 254, 127 255, 0 0 or 0 1
/*int main()
{
  ifstream fin;
  fin.open("integers", std::ios_base::binary);
  unsigned char a,b,c,d;
  int ii = 0;
  vector<vector<int> > s (256, vector<int> (256,0));
//   vector<int> s127(256,0);
  while (fin.get()!=EOF){
    fin.get();
    c = fin.get();
    d = fin.get();
    s[d][c]++;
    if (ii++%10000000 == 0) cout << ii << endl;
  }
  for (int i = 0; i < 256; i++)
    cout << i << ": " << s[0][i] << " " << s[127][i] << endl;
  
}*/


//since we know the distribution of the lost numbers,
//we only need 262k positions in memory to keep them all
int main()
{
  ifstream fin;
  fin.open("integers", std::ios_base::binary);
  unsigned char b,c,d;
  int a;
  int ii = 0;
  vector<vector<int> > list (4, vector<int> (65536,0)); //list of missing numbers
  while ((a = fin.get())!=EOF){
    b = fin.get();
    c = fin.get();
    d = fin.get();
    switch (d*4+c) //missing numbers are concentrated in 4 values of c and d
    {
      case 0: //0 0
        list[0][b*256+a] = 1;
        break;
      case 1: //0 1
        list[1][b*256+a] = 1;
        break;
      case 762: //127 254
        list[2][b*256+a] = 1;
        break;
      case 763: //127 255
        list[3][b*256+a] = 1;
        break;
    }
//     if (ii++%10000000 == 0) cout << ii << endl;
  }
  fin.close();
  
  vector<int> missing;
  for (int i = 0; i < 65536; i++)
  {
    if (list[0][i] == 0)
      missing.push_back(i);
    if (list[1][i] == 0)
      missing.push_back(65536+i);
    if (list[2][i] == 0)
      missing.push_back(2147352576+i);
    if (list[3][i] == 0)
      missing.push_back(2147418112+i);
  }
  sort(missing.begin(),missing.end());
  ofstream fout;
  fout.open("list");
  for (int i = 0; i < missing.size(); i++)
  {
    fout << missing[i] << endl;
  }
}
