#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;


long long factorial (long long a)
{
  if (a == 0) return 1;
  return a * factorial (a-1);
}

long long sumDigits (long long a)
{
  if (a < 10) return a;
  return a%10 + sumDigits (a/10);
}

int main(int argc, char** argv)
{
  
  //to obtain the images from the video:
//   system("ffmpeg -i video.avi -r 10 -f image2 images/%05d.png");
  
  //to find the first difference between both images
//   ifstream fin1, fin2;
//   fin1.open("images/00001.png");
//   fin2.open("images/00002.png");
//   unsigned char c, d;
//   int i = 0;
//   while (true)
//   {
//     c = fin1.get();
//     d = fin2.get();
//     if (c != d)
//     {
//       break;
//     }
//     i++;
//   }
//   cout << i << " " << c << " " << d << endl;
  
  //to find the message
//   int bits = 3424;
//   for (int i = 1; i <= bits; i++)
//   {
//     stringstream ss;
//     ss << i;
//     string s;
//     ss >> s;
//     while (s.size() < 5) s = '0' + s;
//     s = "images/"+s+".png";
//     ifstream fin(s.c_str());
//     unsigned char c;
//     for (int j = 0; j < 44; j++)
//       c = fin.get();
//     if (c == 'd') cout << 0;
//     else cout << 1;
//   }
//   cout << endl;
  
  //to decode the message
//   string s;
//   cin >> s;
//   for (int i = 0; i < s.size(); i++)
//   {
//     char c = 0;
//     for (int j = 0; j < 8; j++)
//     {
//       c *= 2;
//       c += s[i+j]-'0';
//     }
//     cout << c;
//     i+=7;
//   }
//   cout << endl;
  
  //after acceding silence.contest.tuenti.net with cookie adminsession=true, the problem is:
  //For each input N return the sum of digits of N!
  //and there we go
  
  system("java p17"); //not bigintegers in c++ :(
  
  
}