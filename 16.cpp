#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <set>

using namespace std;

typedef pair<char,char> PC; //new char and direction
typedef pair<PC,int> PT; //PC and new state

int char2int (char c)
{
  if (c == '0') return 0;
  if (c == '1') return 1;
  if (c == '#') return 2;
  if (c == '$') return 3;
  if (c == '%') return 4;
  return 5;
}

int int2char[6] = {'0','1','#','$','%','_'};

int readState (string& s, int& index)
{
  if (s[3] == 'r') //start
  {
    index = 6;
    return 0;
  }
  if (s[6] == ',') //one digit state
  {
    index = 7;
    return s[5]-'0'+1;
  }
  //two digit state
  index = 8;
  return (s[5]-'0')*10 + s[6]-'0'+1;
}

//sum of strings, assuming no overflow
string computeSum (string a, string b)
{
  int carry = 0;
  int bits = a.size();
  string ans;
  for (int i = bits-1; i >= 0; i--)
  {
    int result = carry + a[i]-'0' + b[i]-'0';
    ans = char(result%2 + '0') + ans;
    carry = result / 2;
  }
  return ans;
}

//product of strings, assuming no overflow
string product (string a, string b)
{
  int bits = a.size();
  string ans (bits, '0');
  for (int i = 0; i < bits; i++)
  {
    if (b[bits-i-1] == '1')
      ans = computeSum (ans, a.substr(i)+string(i,'0'));
  }
  return ans;
}

int main()
{
  
  //code that simulates a turing machine. After some tests
  //I conjecture that the result is the first times the
  //sum of the others
  
  /*
  ifstream fin;
  fin.open ("machine"); //read the turing machine
  int states = 34;
  int symbols = 6;
  vector<vector<PT> > transitions (states, vector<PT> (symbols, PT(PC('_','S'),-1)));
  string s;
  while (fin >> s) //for each transition
  {
    int index = 0;
    int state = readState (s, index);
    char oldChar = s[index];
    index += 2;
    char newChar = s[index];
    index += 2;
    char movement = s[index];
    index += 2;
    int newState = states; //end by default
    if (s[index] == 's')
    {
      string newStateString = s.substr(index);
      if (newStateString.size() == 6) //one digit state
        newState = newStateString[5]-'0'+1;
      else //two digit state
        newState = (newStateString[5]-'0') * 10 + newStateString[6]-'0' + 1;
    }
    transitions[state][char2int(oldChar)] = PT(PC(newChar, movement), newState);
  }
  
  string input;
  while (cin >> input)
  {
  
    string output = input;
    int head = 0;
    int state = 0;
    while (state != states and state != -1)
    {
      while (head >= output.size()) output += '_';
      char tapeChar = output[head];
      PT nextState = transitions[state][char2int(tapeChar)];
      state = nextState.second;
      output[head] = nextState.first.first;
      int newDirection = 0; //stay
      if (nextState.first.second == 'L') //left
        newDirection = -1;
      if (nextState.first.second == 'R') //right
        newDirection = 1;
      head += newDirection;
    }
    if (state == -1)
    {
      cout << "Rejected input" << endl;
      continue;
    }
    int lastPosition = output.size()-1;
    while (lastPosition >= 0 and output[lastPosition] == '_')
      lastPosition --;
    cout << output.substr(0,lastPosition+1) << endl;
  }
  */
  
  string s;
  while (cin >> s)
  {
    int bits = 0;//number of bits
    for (int i = 1; s[i] != '#'; i++) bits = i;
    string factor = s.substr(1, bits);
    //working with arbitrary precision to avoid overflow
    string sum (bits, '0');
    int index = bits + 2;
    string addend = "";
    while (index < s.size())
    {
      if (s[index] == '#') //new addend
      {
        //normalize to n bits
        while (addend.size() < bits) addend = '0' + addend;
        //if the size is bigger we can assume that it has leading 0,
        //because otherwise the sum would overflow
        addend = addend.substr(addend.size()-bits);
        sum = computeSum (sum, addend);
      }
      else
        addend += s[index];
      index ++ ;
      
    }
    cout << "#" << product (factor, sum) << "#" << endl;
    
  }
}