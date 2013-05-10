#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

int main()
{
  int T;
  cin >> T;
  for (int caseNumber = 0; caseNumber < T; caseNumber ++)
  {
    int W, H, S, C, G;
    cin >> W >> H >> S >> C >> G;
    
    //if we can buy more than W soldiers we win
    if (G / S >= W)
    {
      cout << -1 << endl;
      continue;
    }
    
    
    int best = 0;
    //in the optimal solution, all the soldiers are bought
    //at the beginning, so we iterate over all the possible
    //values of crematoriums
    for (int crematorium = 0; crematorium * C <= G; crematorium ++)
    {
      //the rest is invested in soldiers
      int soldiers = (G - crematorium * C) / S;
      
      //there will be crematorium+1 rounds, and in each of them
      //we survive until a zorg reaches row H after shooting.
      //The formula for each round is is upper((1+w*(h-1))/(w-soldiers))
      //or alternatively lower((w*h-soldiers)/(w-soldiers))
      best = max (best, (W * H - soldiers) / (W - soldiers) * (crematorium + 1));
    }
    cout << best << endl;
  }
}