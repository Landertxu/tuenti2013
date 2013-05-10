#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <set>

using namespace std;

int main()
{
  string key;
  cin >> key;
  
  cout << "afc73f8eef1ef8787ee1a70cc8cab5732071c868" << endl;
  //with this code I obtained that the secret is IETN
//   string s = "Tzo0OiJnYW1lIjozOntzOjExOiIAZ2FtZQBib2FyZCI7Tzo1OiJib2FyZCI6Mzp7czoxMjoiAGJvYXJkAGJvYXJkIjthOjM6e2k6MDthOjM6e2k6MDtiOjA7aToxO3M6MToiWCI7aToyO3M6MToiWCI7fWk6MTthOjM6e2k6MDtzOjE6Ik8iO2k6MTtzOjE6Ik8iO2k6MjtzOjE6Ik8iO31pOjI7YTozOntpOjA7YjowO2k6MTtiOjA7aToyO2I6MDt9fXM6MTM6IgBib2FyZAB3aW5uZXIiO3M6MToiTyI7czoxNDoiAGJvYXJkAHdpbkxpbmUiO3M6MjoiLTEiO31zOjE1OiIAZ2FtZQBuZXh0UGllY2UiO3M6MToiWCI7czoxMToidmVyc2lvbkZpbGUiO3M6MzU6Ii9ob21lL3R0dC9kYXRhL21lc3NhZ2VzL3ZlcnNpb24udHh0Ijt9";
//   string t = "TUENTI";
//   sort(t.begin(),t.end());
//   do
//   {
//     ofstream fout;
//     fout.open("file");
//     fout << s + t.substr(0,4);
//     fout.close();
//     cout << t.substr(0,4) << endl;
//     system ("md5sum file");
//   }while (next_permutation(t.begin(),t.end()));
  
  //the key was obtined by obtaining a cookie (firefox), decode in base64,
  //modify the version path to the key path, encode in base64, append IETN,
  //get the md5 of the result, and append it after a | to the base64 encoding,
  //obtaining:
  //Tzo0OiJnYW1lIjozOntzOjExOiIAZ2FtZQBib2FyZCI7Tzo1OiJib2FyZCI6Mzp7czoxMjoiAGJvYXJkAGJvYXJkIjthOjM6e2k6MDthOjM6e2k6MDtiOjA7aToxO2I6MDtpOjI7YjowO31pOjE7YTozOntpOjA7YjowO2k6MTtiOjA7aToyO2I6MDt9aToyO2E6Mzp7aTowO2I6MDtpOjE7YjowO2k6MjtiOjA7fX1zOjEzOiIAYm9hcmQAd2lubmVyIjtiOjA7czoxNDoiAGJvYXJkAHdpbkxpbmUiO3M6MDoiIjt9czoxNToiAGdhbWUAbmV4dFBpZWNlIjtzOjE6Ik4iO3M6MTE6InZlcnNpb25GaWxlIjtzOjYwOiIvaG9tZS90dHQvZGF0YS9rZXlzLzllOWM0N2RlZDQ5MWQ3ZWUwZWUyYjhkNzZmYmE4NDU1YzdhZGI2N2UiO30=|e13f70df47928c056852ced67e77c311
  //Since the cookie only lives until 1970 I had to change my system date, and execute
  //wget to obtain the final key
  
}