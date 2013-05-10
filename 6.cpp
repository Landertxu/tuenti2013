#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>

#define inf 1<<28

using namespace std;

typedef pair<int,int> PI;
typedef pair<int,PI> PT;

int W, H;
vector<string> grid;

int directionX[4] = {0,1,0,-1};
int directionY[4] = {-1,0,1,0};

//obtain the next coordinates in the given direction
PI next (PI a, int direction)
{
  a.first += directionY[direction];
  a.second += directionX[direction];
  return a;
}

//check whether the coordinates of a are valid
bool valid (PI a)
{
  if (a.first < 0 or a.first >= H or a.second < 0 or a.second >= W) return false; //out of the grid
  return grid[a.first][a.second] != '#';
}

int main()
{
  int N;
  cin >> N;
  
  for (int numberCase = 0; numberCase < N; numberCase++)
  {
    int S, T;
    cin >> W >> H >> S >> T;
    
    //in order to avoid inaccuracies, we work with fractions of 1/S seconds, and divide at the end
    
    grid = vector<string> (H);
    for (int i = 0; i < H; i++)
    {
      string s;
      cin >> s;
      
      //t is s where · are replaced by .
      string t;
      for (int j = 0; j < s.size(); j++)
      {
        if (s[j] == 'X' or s[j] == '#' or s[j] == 'O')
          t += s[j];
        else
        {
          t += '.';
          j++;
        }
      }
      
      grid[i] = t;
    }
    
    //compute the initial and final position
    int initialX, initialY;
    int finalX, finalY;
    for (int i = 0; i < H; i++)
    {
      for (int j = 0; j < W; j++)
      {
        if (grid[i][j] == 'X')
        {
          initialY = i;
          initialX = j;
        }
        if (grid[i][j] == 'O')
        {
          finalY = i;
          finalX = j;
        }
      }
    }    
    
    //the algorithm is a Dijkstra where nodes are positions
    vector<vector<int> > distance (H, vector<int> (W, inf));
    distance[initialY][initialX] = 0; //distance in fractions of 1/S seconds
    vector<vector<bool> > visited (H, vector<bool> (W, false));
    
    priority_queue <PT> q; //seen nonvisited nodes
    q.push (PT (0, PI(initialY, initialX))); //insert the first node
    while (not q.empty() and not visited[finalY][finalX])
    {
      PI a = q.top().second;
      q.pop();
      if (visited[a.first][a.second]) continue; //already visited
      visited[a.first][a.second] = true;
      
      //travel in each direction
      for (int direction = 0; direction < 4; direction ++)
      {
        PI b = a; //new coordinate
        int newDistance = T * S + distance[a.first][a.second]; //minimum distance
        while (valid (next(b, direction))) //while the character can move
        {
          b = next (b, direction);
          newDistance ++;
        }
        
        if (distance[b.first][b.second] > newDistance) //improved distance
        {
          distance[b.first][b.second] = newDistance;
          q.push (PT(-newDistance, b));
        }
      }
    }
    
    cout << (distance[finalY][finalX]+S/2)/S << endl;
  }
}