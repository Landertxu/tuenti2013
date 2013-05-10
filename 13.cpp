#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <fstream>

using namespace std;

vector<int> intervalTree;
vector<int> positionIni;
vector<int> positionEnd;

int getMaximum (int begin, int end, int index)
{
  if (begin > end) //empty interval
    return 0;
  if (begin <= positionIni[index] and end >= positionEnd[index]) //full interval
    return intervalTree[index];
  
  int middle = (positionIni[index] + positionEnd[index]) / 2;
  return max (getMaximum (begin, min(end, middle), index*2),
              getMaximum (max(middle+1,begin), end, index*2+1));
}

int main()
{
  int T;
  cin >> T;
  for (int numCase = 1; numCase <= T; numCase ++)
  {
    cout << "Test case #" << numCase << endl;
    int N, M;
    cin >> N >> M;
    vector<int> values (N);
    for (int i = 0; i < N; i++)
      cin >> values[i];
    
    //for the preprocess, we compute, for each position,
    //the first and las position with the same value, and
    //the number of different integers strictly lower than them
    vector<int> firstEqual (N);
    vector<int> lastEqual (N);
    vector<int> order (N); //relative order
    
    firstEqual[0] = 0;
    for (int i = 1; i < N; i++)
    {
      if (values[i] == values[i-1])
        firstEqual[i] = firstEqual[i-1];
      else
        firstEqual[i] = i;
    }
    
    lastEqual[N-1] = N-1;
    for (int i = N-1; i >= 0; i--)
    {
      if (values[i] == values[i+1])
        lastEqual[i] = lastEqual[i+1];
      else
        lastEqual[i] = i;
    }
    
    order[0] = 0;
    for (int i = 1; i < N; i++)
    {
      if (values[i] == values[i-1])
        order[i] = order[i-1];
      else
        order[i] = order[i-1] + 1;
    }
    
    int different = order[N-1]+1; //number of different integers
    
    //we will use a structor of interval tree, saving
    //for each value its number of occurrences
    
    //the size of the interval tree will be a power of two
    int K = 1;
    while (K < different) K *= 2;
    
    //nuumber of occurrences
    vector<int> occurrences (K);
    for (int i = 0; i < N; i++)
      occurrences[order[i]] ++;
    
    //node i will be the parent of nodes 2*i and 2*i+1
    intervalTree = vector<int> (2*K);
    //interval of an internal node
    positionIni = positionEnd = intervalTree;
    for (int i = 0; i < K; i++)
      intervalTree[i+K] = occurrences[i];
    
    for (int i = K-1; i > 0; i--)
      intervalTree[i] = max (intervalTree[i*2], intervalTree[i*2+1]);
    
    for (int i = 0; i < K; i++)
      positionIni[i+K] = positionEnd[i+K] = i;
    
    for (int i = K-1; i > 0; i--)
    {
      positionIni[i] = positionIni[i*2];
      positionEnd[i] = positionEnd[i*2+1];
    }
    
    for (int i = 0; i < M; i++)
    {
      int sm, em; //interval to analyze
      cin >> sm >> em;
      sm--; em--; //change to 0-indexed
      
      int order1 = order[sm];
      int order2 = order[em];
      
      if (order1 == order2) //same number
      {
        cout << em - sm + 1 << endl;
      }
      else if (order1 + 1 == order2) //consecutive different numbers
      {
        //maximum of the two intervals
        cout << max(lastEqual[sm]-sm+1, em-firstEqual[em]+1) << endl;
      }
      else //several intervals
      {
        int ans = max(lastEqual[sm]-sm+1, em-firstEqual[em]+1);
        ans = max (ans, getMaximum (order1 + 1, order2 - 1, 1) );
        cout << ans << endl;
      }
    }
    
    
  }
}