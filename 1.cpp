#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main()
{
  int T; //number of test cases
  cin >> T;
  for (int ncase = 1; ncase <= T; ncase ++)
  {
    long long N; //initial budget
    cin >> N;
    vector<long long> valueList;
    string s;
    getline(cin,s); //to avoid the initial endline
    getline(cin,s);
    stringstream ss(s);
    long long value;
    while (ss >> value)
    {
      valueList.push_back (value);
    }
    long long euros = N; //current amount of euros
    long long bitcoins = 0; //current amount of bitcoins
    for (int i = 0; i < valueList.size()-1; i++)
    {
      //if the next value is greater, buy as much bitcoins as possible
      if (valueList[i] < valueList[i+1])
      {
        bitcoins += euros / valueList[i];
        euros %= valueList[i];
      }
      //if the next value is lower, sell all the available bitcoins
      if (valueList[i] > valueList[i+1])
      {
        euros += bitcoins * valueList[i];
        bitcoins = 0;
      }
      //if the next value is equal, do nothing
    }
    //finally, sell all the bitcoins to get as much euros as possible
    euros += bitcoins * valueList[valueList.size()-1];
    
    //print the number of euros
    cout << euros << endl;
  }
}