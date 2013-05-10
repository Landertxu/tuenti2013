#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include "md5.h"

using namespace std;

int main()
{
  string s;
  while (getline(cin,s))
  {
    //for each bracket [] the content must be replied
    //as many times as the number before
    
    //since resulting string can be very long, we
    //process the md5 value in sequences of 64 chars
    
    //preprocess s so that we know for each bracket []
    //the number of times it must be repeated
    int n = s.size();
    vector<int> initialBrackets (n,0); //in positions with [, brackets
    //will contain the remaining loops; in positions with ],
    //brackets will contain a pointer to its corresponding [
    
    stack<int> unclosedBrackets; //pointers to unclosed brackets
    int value = 0; //number of iterations
    for (int i = 0; i < n; i++)
    {
      if (s[i] >= '0' and s[i] <= '9') //new digit
      {
        value *= 10;
        value += s[i] - '0';
      }
      if (s[i] == '[')
      {
        initialBrackets[i] = value;
        value = 0;
        unclosedBrackets.push(i);
      }
      if (s[i] == ']')
      {
        initialBrackets[i] = unclosedBrackets.top();
        unclosedBrackets.pop();
      }
    }
    
    //ans will be updated with groups of 64 chars  
    MD5 ans;
    ans.init();
    char buffer[64];
    int current = 0; //number of already read chars
    int pointer = 0; //pointer to positions in s
    vector<int> brackets = initialBrackets;
    while (pointer < s.size())
    {
      if (s[pointer] >= 'a' and s[pointer] <= 'z')
      {
        buffer[current] = s[pointer];
        current ++;
        if (current >= 64)
        {
          current = 0;
          ans.update (buffer, 64);
        }
      }
      
      if (s[pointer] == '[') //next iteration
      {
        if (brackets[pointer] == 0) //new external iteration
          brackets[pointer] = initialBrackets[pointer];
        brackets[pointer] --;
      }
      
      if (s[pointer] == ']')
      {
        if (brackets[brackets[pointer]] > 0) //at least one more iteration
        {
          pointer = brackets[pointer] - 1; //compensate the final pointer++
        }
      }
      
      pointer ++;
    }
    
    //update the last chars
    ans.update (buffer, current);
    
    ans.finalize();
    cout << ans.hexdigest() << endl;
  }
}