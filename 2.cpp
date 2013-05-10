#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

#define mod 1000007

//obtain the hash of a given string
//pre: s only contains lowercase letters
int hash (string s)
{
  vector<int> letters (26);
  for (int i = 0; i < s.size(); i++) letters[s[i]-'a']++;
  long long ans = 4321;
  for (int i = 0; i < letters.size(); i++)
  {
    ans *= 1234567;
    ans += letters[i];    
    ans %= mod;
  }
  return int(ans);
}

int main()
{
  string comment;
  getline (cin, comment);
  string nameDictionary;
  cin >> nameDictionary;
  fstream fin;
  fin.open (nameDictionary.c_str());
  
  //the dictionary is saved in a vector of strings
  vector <string> dictionary;
  string word;
  while (fin >> word)
  {
    dictionary.push_back(word);
  }
  
  sort (dictionary.begin(), dictionary.end());
  
  /*
   * The preprocess of the dictionary consist of a hash table, where the key
   * of each word is a simple hash function (modulo 10^6+7) of the sorted
   * sequence of the letters of the word.
   */
  
  int N = dictionary.size(); //number of words
  vector<int> first (mod, -1); // first[i] is a pointer to the first word
                               // in the dictionary with hash i, or -1 if
                               // such a word does not exist
  vector<int> last (mod, -1); // pointer to the last word
  vector<int> next (N, -1); // pointer to the next word with the same hash
  
  
  for (int i = 0; i < N; i++)
  {
    word = dictionary[i];
    int h = hash (word);
    
    if (first[h] == -1) //first word with hash h
      first[h] = i;
    else
      next[last[h]] = i;
    
    last[h] = i; //the last word with hash h is the current word
  }
  
  getline(cin,comment); //avoid endline
  getline(cin,comment); //#Suggestion numbers
  int n; //number of suggestions
  cin >> n;
  
  getline(cin,comment); //avoid endline
  getline(cin,comment); //#Find the suggestions
  for (int i = 0; i < n; i++)
  {
    cin >> word;
    int h = hash (word); //obtain the hash of the given word
    // the suggestions must have the same hash
    int index = first[h]; //first word with hash h
    
    cout << word << " ->";
    
    string sortedWord = word;
    sort(sortedWord.begin(), sortedWord.end());
    
    while (index != -1)
    {
      string candidate = dictionary[index];
      index = next[index];
      string sortedCandidate = candidate;
      sort (sortedCandidate.begin(), sortedCandidate.end());
      // test for collisions
      if (sortedCandidate != sortedWord) continue;
      // do not offer the same word
      if (word == candidate) continue;
      
      cout << " " << candidate;
    }
    
    cout << endl;
  }
  
}