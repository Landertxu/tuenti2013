#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

string s;


//code decompiled by hand :)
bool funcion (int p1, int p2, char p3[])
{
    if (p1 != 2)
      return false;
    int i = 0;
    unsigned int f = 1337;
    while (p3[i] != 0)
    {
      f = (f * 16807) % ((1<<27)-1);
      if ((i > 59) || (((f&0xff) xor p3[i]) != s[i]))
      {
        return false;
      }
      i++;
    }
}

int main()
{
  
  ofstream fout;
  fout.open("binary64");
  string s;
  while (cin >> s)
    fout << s;
  fout << endl;
  fout.close();
  
  system("base64 -d binary64 > binary");
  
  //to obtain the string from the code
  ifstream fin;
  fin.open("binary");
  fout.open("input");
  int c;
  for (int i = 0; i < 328; i++)
    fin.get();
  for (int i = 0; i < 60; i++)
  {
    c = fin.get();
    fout << char(c);
  }
  fin.close();
  fout.close();
  
  ifstream fin2;
  fin2.open("input");
  s = "";
  while ((c = fin2.get()) != EOF)
    s += char(c);
  unsigned int f = 0x539;
  for (int i = 0; i < s.size(); i++)
  {
    f = (f * 0x41a7) % (0x7ffffff);
    cout << char((f&0xff) xor s[i]);
  }
  cout << endl;
  fin2.close();
}