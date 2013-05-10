#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <set>
#include <cmath>

#define epsilon 1e-9

using namespace std;

int main()
{
  int N; //test cases
  cin >> N;
  for (int numCase = 0; numCase < N; numCase ++)
  {
    int V, E;
    cin >> V >> E;
    vector<int> a, b, d; //from, to, cost
    a = b = d = vector<int> (E);
    for (int i = 0; i < E; i++)
      cin >> a[i] >> b[i] >> d[i];
    
    vector<double> c(E); //cost in double precision
    for (int i = 0; i < E; i++)
      c[i] = log(1. + d[i] / 100.);
    
    //variant of the bellman ford algorithm    
    //initially, weights are 1 instead of infinity,
    //and our goal is to get as much enery as possible
    //since we work with logarithms initial values are log(1)=0
    vector<double> energy (V, 0);
    
    for (int iteration = 0; iteration < V-1; iteration ++)
    {
      vector<double> newEnergy = energy;
      //relax each edge
      for (int i = 0; i < E; i++)
        newEnergy[b[i]] = max (newEnergy[b[i]], energy[a[i]] + c[i]);
      
      energy = newEnergy;
      
    }
    //check for negative cycles
    bool negativeCicles = false;
    for (int i = 0; i < E and not negativeCicles; i++)
      if (energy[b[i]] < energy[a[i]] + c[i] - epsilon)
        negativeCicles = true;
      
    if (negativeCicles)
      cout << "True" << endl;
    else
      cout << "False" << endl;
    
  }
}