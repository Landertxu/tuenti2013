#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <fstream>

using namespace std;

int main()
{
  ofstream fout;
  fout.open ("message");
  string s;
  while (getline(cin,s))
    fout << s << endl;
  //first decode base64
  system ("base64 -d message > message.mp3");
  
  //the output is a mp3, containing a RTTY transmission
  //mp3 should be converted to .wav, I use the linux lame
  
  system ("lame message.mp3 message.wav");
  
  //in order to decode it, I use trueTTY, obtaining such a result:
  cout << "C0DE CAFE FACE BABE BEAF DEAD DEAD D00D" << endl;
}