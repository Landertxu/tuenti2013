#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

int N, M; //grid dimensions
vector<vector<int> > grid; //grid with the gem values
int optimal; //optimal value

int directionX[4] = {0,1,0,-1};
int directionY[4] = {-1,0,1,0};

//X,Y is the current position of the character
void backtracking (int X, int Y, int lastDirection, int remainingSeconds, int currentValue)
{
  currentValue += grid[Y][X]; //add the value of the gem at the current position
  
  optimal = max (optimal, currentValue); //check if the current value is better than the optimal
  
  if (remainingSeconds * 5 + currentValue <= optimal)
    return; //check if we can still improve the value 
    //note that if remainingSeconds == 0, then this condition always holds
  
  int lastValue = grid[Y][X];
  grid[Y][X] = 0; //void taking the same gem twice
  
  for (int direction = 0; direction < 4; direction ++) //check all possible direction
  {
    if (abs(direction - lastDirection) == 2) //avoid going backwards
      continue;
    
    int newX = X + directionX[direction];
    int newY = Y + directionY[direction];
    if (newX < 0 or newX >= M or newY < 0 or newY >= N)
      continue; //check whether we remain inside the grid
      
      
    backtracking (newX, newY, direction, remainingSeconds-1, currentValue);
  }
  
  grid[Y][X] = lastValue;
    
}

int main()
{
  int T; //number of test cases
  cin >> T;
  for (int caseNum = 0; caseNum < T; caseNum ++)
  {
    int X, Y, Z, G;
    char dummy;
    cin >> M >> dummy >> N;
    cin >> X >> dummy >> Y;
    cin >> Z >> G;
    
    grid = vector<vector<int> > (N, vector<int> (M, 0)); //initialize the grid
    optimal = 0;
    for (int i = 0; i < G; i++)
    {
      if (i > 0) cin >> dummy;
      int xg, yg, vg; //coordinates and value of the gem
      cin >> xg >> dummy >> yg;
      cin >> dummy >> vg;
      
      grid[yg][xg] = vg;
    }
    
    backtracking (X, Y, -10, Z, 0);
    
    cout << optimal << endl;
  }
  
}