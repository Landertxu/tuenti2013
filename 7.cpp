#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;

int directioni[8] = {-1,-1,-1,0,0,1,1,1};
int directionj[8] = {-1,0,1,-1,1,-1,0,1};


int n, m; //board size
vector<string> board;
vector<vector<int> > characterMultiplier, wordMultiplier;
map<char,int> points;
map<string,int> maxPoints;

struct trie
{
  bool finish; //existing word
  map<char,trie*> next; //pointers to other words
};

void add (trie* dictionary, string& word, int index)
{
  if (index == word.size()) //end of the word
  {
    dictionary->finish = true;
    return;
  }
  char current = word[index];
  if (dictionary->next.find(current) == dictionary->next.end()) //non existing prefix
  {
    dictionary->next[current] = new trie;
    dictionary->next[current]->finish = false;
  }
  
  add (dictionary->next[current], word, index+1);
}

void dfs (int row, int column, trie* dictionary, int currentPoints, int multiplier, string word)
{
  //check if the position is valid
  if (row < 0 or row >= n or column < 0 or column >= m) return;
  
  //check if we can use the current letter
  char c = board[row][column];
  if (dictionary->next.find(c) == dictionary->next.end()) return;
  
  dictionary = dictionary->next[c];
  word += c;
  currentPoints += points[c] * characterMultiplier[row][column];
  multiplier = max (multiplier, wordMultiplier[row][column]);
  //check if the word is final
  if (dictionary->finish)
  {
    maxPoints[word] = max (maxPoints[word], currentPoints * multiplier + int(word.size()));
  }
  
  //avoid using the same letter
  board[row][column] = '.';
  //find more words
  for (int direction = 0; direction < 8; direction ++)
  {
    dfs (row+directioni[direction], column+directionj[direction], dictionary, currentPoints, multiplier, word);
  }
  board[row][column] = c;
}

int main()
{
  //read the dictionary
  ifstream fin;
  fin.open("boozzle-dict.txt");
  
  //the data structure will be a trie, so that we can know
  //in constant time whether a word exists, and whether 
  //a word is a prefix of an existing word
  trie* dictionary = new trie;
  dictionary->finish = false;
  string word;
  while (fin >> word)
    add (dictionary, word, 0); // add to the dictionary the word beginning at position 0
  fin.close();
    
  int N;
  cin >> N;
  for (int caseNumber = 0; caseNumber < N; caseNumber ++)
  {
    string s;
    getline (cin,s); //ignore the endline
    getline (cin,s);
    
    points = map <char,int> (); //points for each letter
    for (int i = 2; i < s.size(); i += 8)
    {
      char c = s[i];
      points[c] = int(s[i+4]-'0');
      while (s[i+5] >= '0' and s[i+5] <= '9') //values with more than one digit
      {
        points[c] *= 10;
        points[c] += int(s[i+5]-'0');
        i++;
      }
    }
    
    int W; //duration of the game
    cin >> W;
    
    cin >> n >> m; //board size
    
    board = vector<string> (n, string(m,'.')); //letters on the board
    characterMultiplier = wordMultiplier = vector<vector<int> > (n, vector<int> (m, 1));
    
    //read the board
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        cin >> s;
        board[i][j] = s[0];
        int multiplierType = int(s[1]-'0');
        int multiplierValue = int(s[2]-'0');
        if (multiplierType == 1)
          characterMultiplier[i][j] = multiplierValue;
        else
          wordMultiplier[i][j] = multiplierValue;
      }
    }
    
    //in the next step we compute all the word that can be obtained,
    //and the maximum number points we can obtain
    maxPoints = map<string,int> ();
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        //begin in position (i,j)
        dfs (i, j, dictionary, 0, 1, "");
      }
    }
    
    //finally, once we have the list of possible words, we solve the
    //knapsack problem using dinamic programming
    
    vector<int> dinamic (W+1, 0); //dinamic[i] = max points in at most i seconds
    
    for (map<string,int>::iterator it = maxPoints.begin(); it != maxPoints.end(); it++)
    {
      int time = it->first.size() + 1; //time to submit a word
      for (int i = W; i >= time; i--) //improve the points in i seconds
        dinamic[i] = max (dinamic[i], dinamic[i-time] + it->second);
    }
    
    //the answer is the maximum points we can obtain in W seconds
    cout << dinamic[W] << endl;
  }
}