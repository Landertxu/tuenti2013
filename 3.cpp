#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

map<string, int> scene2int; //assign an integer to each different scene
vector<string> int2scene; //recover the original name of the scene
vector<vector<int> > graph; //graph of orders,
//if an edge (a,b) belongs to the graph then a happened before b

//return the integer corresponding to a given scene
int getInt (string s)
{
  if (scene2int.find(s) == scene2int.end()) //new scene
  {
    int newNumber = int2scene.size();
    scene2int[s] = newNumber;
    int2scene.push_back(s);    
  }
  
  return scene2int[s];
}

//add a new edge a->b to the graph
void addEdge (int a, int b)
{
  //check whether a and b exist in the graph
  while (graph.size() <= a)
    graph.push_back(vector<int> (0));
  while (graph.size() <= b)
    graph.push_back(vector<int> (0));
  
  //add the edge
  graph[a].push_back(b);
}

int main ()
{
  int numberCases;
  cin >> numberCases;
  
  string script;
  getline (cin, script); //to avoid the first endline
  for (int numberCase = 0; numberCase < numberCases; numberCase++)
  {
    getline (cin, script);
    
    scene2int = map<string, int>(); //initialize the assignment
    int2scene = vector<string> (0);
    graph = vector<vector<int> > (0); //initialize the graph
    
    int last = 0; //index to the beginning of the last scene
    int current = 1;
    int lastOrdered = -1; //number of the last chronologically ordered scene
    
    //parse the input
    while (current < script.size())
    {
      if (script[current] == '.' or script[current] == '<' or script[current] == '>') //new scene
      {
        int index = getInt (script.substr(last+1, current-last-1));
        if (lastOrdered == -1) //first scene
          lastOrdered = index;
        else
        {
          if (script[last] == '.') //new chronologically ordered scene
          {
            addEdge (lastOrdered, index);
            lastOrdered = index;
          }
          else if (script[last] == '<') //flashback
          {
            addEdge (index, lastOrdered);
          }
          else //flashforward
          {
            addEdge (lastOrdered, index);
          }
        }
        last = current;
      }
      current++;
    }
    //last scene
    int index = getInt (script.substr(last+1));
    if (lastOrdered == -1) //only one scene
    {
      graph.push_back(vector<int> (0));
    }
    else
    {
      if (script[last] == '.') //new chronologically ordered scene
      {
        addEdge (lastOrdered, index);
      }
      else if (script[last] == '<') //flashback
      {
        addEdge (index, lastOrdered);
      }
      else //flashforward
      {
        addEdge (lastOrdered, index);
      }
    }
    
    //try a topological sort of the graph
    
    int n = graph.size();
        
    vector<int> indegree (n, 0); //indegree of the nodes of the graph
    
    for (int i = 0; i < n; i++)
      for (int j = 0; j < graph[i].size(); j++)
        indegree[graph[i][j]]++;
      
    bool notUnique = false; //if notUnique is true, there exist
    //either more than one solution, or none at all
    
    queue<int> q; //seen nonvisited nodes
    bool valid = true;
    
    for (int i = 0; i < n; i++)
      if (indegree[i] == 0)
        q.push(i);
      
    if (q.size() > 1) valid = false; //more than one beginning scene
      
    vector<int> order (n); //current ordering of the nodes
    int seen = 0; //nodes already seen
    
    while (not q.empty())
    {
      if (q.size() > 1) //the solution is not unique
        notUnique = true;
      
      if (q.size() > 1 and seen + q.size() == n) //more than one ending scene
        valid = false;
      
      int a = q.front();
      q.pop();
      order[seen] = a;
      seen++;
      
      for (int i = 0; i < graph[a].size(); i++)
      {
        int b = graph[a][i];
        indegree[b]--;
        if (indegree[b] == 0) //the node b can be selected
          q.push(b);
      }
    }
    
    if (seen < n) //not all the nodes have been seen
      valid = false;
    
    if (not valid)
      cout << "invalid" << endl;
    else if (notUnique) //more than one solution
      cout << "valid" << endl;
    else //unique solution
    {
      for (int i = 0; i < n; i++)
      {
        if (i > 0) cout << ",";
        cout << int2scene[order[i]];
      }
      cout << endl;
    }
    
  }
}