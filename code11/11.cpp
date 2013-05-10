#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <queue>
#include <set>
#include <fstream>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

struct tree
{
  char value; //b, p or m
  tree* children [4]; //only defined if value = p
};

//convert a given string into a tree
tree* convert (string s)
{
  tree* ans = new tree;
  ans->value = s[0];
  queue<tree*> q;
  if (ans->value == 'p')
    q.push(ans);
  int index = 1; //current position of s
  while (not q.empty())
  {
    tree* a = q.front();
    q.pop();
    for (int i = 0; i < 4; i++)
    {
      tree* b = new tree;
      b->value = s[index];
      index ++;
      a->children[i] = b;
      if (b->value == 'p')
	q.push(b);
    }
  }
  return ans;
}

//recursively remove t and its children
void deleteTree (tree* t)
{
  if (t->value == 'p')
    for (int i = 0; i < 4; i++)
      deleteTree (t->children[i]);
  delete t;
}

//recursively replace each occurrence of pwwww by w,
//and each occurence of pbbbb by b
void reduce (tree* t)
{
  if (t->value != 'p') return;
  
  for (int i = 0; i < 4; i++)
    reduce (t->children[i]);
  
  set<char> childrenValues; //different values of the children  
  for (int i = 0; i < 4; i++)
    childrenValues.insert (t->children[i]->value);
  
  if (childrenValues.size() > 1) return; //already reduced
  
  char newValue = *(childrenValues.begin());
  if (newValue == 'p') return;
  
  t->value = newValue;
  for (int i = 0; i < 4; i++)
    deleteTree (t->children[i]);
}

//sum a pair of trees
tree* sumTrees (tree *a, tree *b)
{
  tree *ans;
  if (a->value == 'b' or b->value == 'b')
  {
    ans = new tree;
    ans->value = 'b';
    return ans;
  }
  
  if (a->value == 'w')
  {
    ans = b;
    return ans;
  }
  if (b->value == 'w')
  {
    ans = a;
    return ans;
  }
  
  //now a->value = b->value = p;
  ans = new tree;
  ans->value = 'p';
  for (int i = 0; i < 4; i++)
    ans->children[i] = sumTrees (a->children[i], b->children[i]);
  
  return ans;
  
}


//print tree t level by level
void printLevel (tree* t)
{
  queue<tree*> q;
  q.push(t);
  while (not q.empty())
  {
    tree* a = q.front();
    q.pop();
    cout << a->value;
    if (a->value == 'p')
      for (int i = 0; i < 4; i++)
	q.push(a->children[i]);
  }
  cout << endl;
}

//return the height of t
int getHeight (tree* t)
{
  int ans = 0;
  if (t->value == 'p')
    for (int i = 0; i < 4; i++)
      ans = max (ans, 1 + getHeight (t->children[i]));
  return ans;
}

void printSquare(tree* t, vector<vector<int> > &mosaic, int inii, int endi, int inij, int endj)
{
  if (t->value != 'p')
  {
    int fill = 0;
    if (t->value == 'b') fill = 1;
    for (int i = inii; i < endi; i++)
    {
      for (int j = inij; j < endj; j++)
	mosaic[i][j] = fill;
    }
    return;
  }
  
  int midi = (inii + endi) / 2;
  int midj = (inij + endj) / 2;
  
  printSquare(t->children[0], mosaic, inii, midi, midj, endj);
  printSquare(t->children[1], mosaic, inii, midi, inij, midj);
  printSquare(t->children[2], mosaic, midi, endi, inij, midj);
  printSquare(t->children[3], mosaic, midi, endi, midj, endj);
}

void printMosaic (tree* t)
{
  ofstream fout;
  fout.open ("image.pbm");
  fout << "P1" << endl; //format
  int h = getHeight (t);
  fout << (1<<h)+3 << " " << (1<<h)+3 << endl; //dimensions
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < (1<<h)+3 ; j++)
      fout << "0 ";
    fout << endl;
  }
  vector<vector<int> > ans (1<<h, vector<int> (1<<h, 0));
  printSquare (t, ans, 0,1<<h, 0, 1<<h);
  for (int i = 0; i < (1<<h); i++)
  {
    fout << "0 0 0";
    for (int j = 0; j < (1<<h); j++)
      fout << " " << ans[i][j];
    fout << endl;
  }
  
  //code that reads qr
  system ("perl 11.pl");
}

int main()
{
  int N;
  cin >> N;
  string s;
  getline (cin,s); //avoid endl
  for (int caseNum = 0; caseNum < N; caseNum++)
  {
    getline (cin, s);
    stringstream ss(s);
    ss >> s; //first 
    tree* sum = convert (s);
    reduce (sum); //pwwww -> w
    
    while (ss >> s) //sum the other trees
    {
      tree* aux = convert (s);
      reduce (aux);
      
      sum = sumTrees (sum, aux);
    }
//     printLevel (sum);
    
    printMosaic (sum);
  }
  
}