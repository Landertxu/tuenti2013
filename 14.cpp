#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <set>

using namespace std;

int hex2dec (char c)
{
  if (c >= '0' and c <= '9') return c - '0';
  return c - 'a' + 10;
}

int main()
{
  //the codification consist in doing an xor operation to each byte
  //I computed the first terms of the mask by hand, and then I found the quote in google.
  //I use the longest quote to compute the mask
  string textEncoded = "46fb200144df180dba5c8f52481c0ef515d9e963d0008b859c121b51ee8d0ca8e98b01d89a841257a1559174765d8ea95b9e69aaf014624eb5be51c415cfc5854aaa6c18b929b496e71a721303846856ae31c6d24529f4a9c19ef46a75819ea156598893e644f2c7f7ae39381b0184b5c937f8473a3800842e822014c4e8a94cc36373e81a6ee94632678625f2a5ff2eeb4eeae42d4190791cfd8fcc5f8dec2c2c5547fd63ebcb8a3c56303b4976dff9502d30e85955ed128114eb094b1667bb7da282be7ed7f1873d8e8c31d18ef24a48e990db46f5a591ecbc33704380a1b9b8babcdb4fe3";
  string textDecoded = "Some humans would do anything to see if it was possible to do it. If you put a large switch in some cave somewhere, with a sign on it saying 'End-of-the-World Switch. PLEASE DO NOT TOUCH', the paint wouldn't even have time to dry.";
  
  vector<char> mask (textDecoded.size()*2);
  for (int i = 0; i < textDecoded.size(); i++)
  {
    char encoded = 16*hex2dec(textEncoded[i*2]) + hex2dec(textEncoded[i*2+1]);
    char decoded = textDecoded[i];
    mask[i] = encoded xor decoded;
  }
  
  string message;
  while (cin >> message)
  {
    for (int i = 0; i*2 < message.size(); i++)
    {
      char byteValue = 16*hex2dec(message[i*2]) + hex2dec(message[i*2+1]);
      cout << char(byteValue xor mask[i]);
    }
    cout << endl;
  }
}