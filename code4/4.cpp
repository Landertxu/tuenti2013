#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

int main()
{
  ifstream fin;
  fin.open("list"); //list calculated with parser.cpp
  vector<int> list;
  int x;
  while (fin >> x)
    list.push_back(x);
  
  int T; //number of cases
  cin >> T;
  for (int caseNum = 0; caseNum < T; caseNum ++)
  {
    int N; // Nth missing integer to be found
    cin >> N;
    
    cout << list[N-1] << endl; //the list is 0-based
  }
}